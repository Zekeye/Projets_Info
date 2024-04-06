/* =================================================================== */
// Progrmame Serveur qui calcule le résultat d'un coup joué à partir
// des coordonnées reçues de la part d'un client "joueur".
// Version ITERATIVE : 1 seul client/joueur à la fois
/* =================================================================== */

#include "tresor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <time.h>

/* =================================================================== */
/* FONCTION PRINCIPALE : SERVEUR ITERATIF                              */
/* =================================================================== */
int main(int argc, char** argv) {

    // Création des variables

    /* variable sid où l'on crée le socket, resultat où l'on stocke le résultat reenvoyer par la fonction recherche trésor
     point_x et point_y recupèrent les coordonnées envoyés par le joueur

    Création des structures qui serviront pour le binding et l'acceptation
    Création de la socket pour la connexion
    Création des buffer d'envoi et de réception ainsi que des variables pour stocker les coordonnées
    */

    int sid, resultat_joueur, point_x, point_y;
    struct sockaddr_in sk_addr;
    int newsock;
    struct sockaddr_in cli_adr;
    socklen_t cli_adr_len = sizeof(cli_adr);
    char chaine_reception[10], chaine_envoi[10];
    int point_aleatoire_x, point_aleatoire_y;
    int idfork;

    // Sert à mettre l'intervalle sur les valeurs qu'on veut ainsi qu'a initialiser le générateur de nombre aléatoire
    const int min = 1, max = 10;


    // Création d'un socket d'écoute

    sid = socket(AF_INET, SOCK_STREAM, 0);
    if (sid == -1) {
        perror("La création du socket à échoué");
        return EXIT_FAILURE;
    }

    // On associe une adresse socket au service
    memset(&sk_addr, 0, sizeof(sk_addr));
    sk_addr.sin_family = AF_INET;
    sk_addr.sin_port = htons(3000);
    sk_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sid, (struct sockaddr*)&sk_addr, sizeof(sk_addr)) == -1) {
        perror("Bind error");
        close(sid);
        return EXIT_FAILURE;
    }

    // On mets la socket à l'écoute de demandes d'établissement de connexion TCP entrantes

    if (listen(sid, 1) == -1) {
        perror("Listen error");
        close(sid);
        return EXIT_FAILURE;
    }

    // On mets un while qui ne s'arrêtera jamais afin que le serveur soit toujours actif
    while (1) {

        printf("En attente de connection de la part d'un joueur\n");
        // On accepte une connexion TCP entrante et on crée une nouvelle socket dédiée à cette connexion.


        newsock = accept(sid, (struct sockaddr*)&cli_adr, &cli_adr_len);
        if (newsock < 0) {
            perror("accept failed");
            close(sid);
            exit(EXIT_FAILURE);
        }

        idfork = fork();

        if (idfork == 0) {

            close(sid);

            printf("Serveur connecté à un client\n");

            // On génère aléatoirement les coordonnées du trésor.
            srand(time(NULL));
            point_aleatoire_x = (rand() % (max - min + 1)) + min;
            point_aleatoire_y = (rand() % (max - min + 1)) + min;



            printf(" Le point x est %d et le point y est %d\n", point_aleatoire_x, point_aleatoire_y);


            /* Lorsque l'on à les coordonnées du trésor on commence l'envoi et la reception des message du client
            La boucle s'arrêtera quand le joueur aura trouvé le trésor
            */
            do {

                // On récupère le message et on le mets dans chaine_reception
                if (recv(newsock, chaine_reception, 10, 0) == -1) {
                    perror("Problème au niveau du recv du serveur");
                    return EXIT_FAILURE;
                }

                // On transforme les coordonnées de type char en type int et on les mets dans les 2 variables appropriée
                sscanf(chaine_reception, "%d %d", &point_x, &point_y);


                // On appelle la fonction qui renvoie le résultat de recherche trésor et on la mets dans la variable
                resultat_joueur = recherche_tresor(10, point_aleatoire_x, point_aleatoire_y, point_x, point_y);

                // Ecriture dans le buffer d'envoi
                snprintf(chaine_envoi, 4, "%d", resultat_joueur);

                // Envoi du message
                if (send(newsock, chaine_envoi, 4, 0) == -1) {
                    perror("Problème au niveau du send serveur1");
                    return EXIT_FAILURE;
                }


            } while (resultat_joueur != 0);

            // Lorsque la partie est terminée, on l'affiche sur stdin et on ferme la socket
            printf("Fin de la partie pour le joueur \n \n");
            printf("Fermeture de la socket pour ce joueur\n \n");
            close(newsock);
            exit(0);
        }

        else {
            close(newsock);
        }

    }

        //Fin de la connection
    // Fermeture de la socket d'écoute
    close(sid);
    printf("Fin du programme");

    return 0;
} // end main
