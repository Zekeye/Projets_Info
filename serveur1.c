/* =================================================================== */
// Progrmame Serveur qui calcule le résultat d'un coup joué à partir
// des coordonnées reçues de la part d'un client "joueur".
// Version ITERATIVE : 1 seul client/joueur à la fois
/* =================================================================== */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define N 10

/* =================================================================== */
/* FONCTION PRINCIPALE : SERVEUR ITERATIF                              */
/* =================================================================== */
int main(int argc, char **argv) {
 //Init nPort
    const int PORT_NUMBER=9000;
 //Creation socket
    int creat_sock = socket (AF_INET, SOCK_STREAM, 0);
    if (creat_sock==-1){
        perror("Erreur création du socket");
        return EXIT_FAILURE;
    }
 //Bind
    struct sockaddr_in sk_addr;
    memset(&sk_addr, 0, sizeof(sk_addr));
    sk_addr.sin_family = AF_INET;
    sk_addr.sin_port = htons(PORT_NUMBER); /* host to net byte order (short) */
    sk_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* any interface */
    if (bind(creat_sock, (struct sockaddr*) &sk_addr, sizeof(sk_addr)) == -1) {
        perror("Bind error");
        close(creat_sock);
        return EXIT_FAILURE;
    }
 //Listen
    if (listen(creat_sock, 1) == -1) {
        perror("Listen error");
        close(creat_sock);
        return EXIT_FAILURE;
    }
    printf("Attente de connexion\n");
 //Accept
    int newsock;
    while(1){
        struct sockaddr_in cli_adr;
        socklen_t cli_adr_len = sizeof(cli_adr);
        newsock = accept(creat_sock, (struct sockaddr *)&cli_adr, &cli_adr_len);
        if (newsock < 0) {
            perror("accept failed");
            close(creat_sock);
            exit(EXIT_FAILURE);
        }
        printf("connexion accept\n");
        int res=10;
        while(res){ //send et receve
            int lig;
            int col;
            char buffer_out[8];
            char buffer_in[8];
            sprintf(buffer_out,"%d", res);
            /* Calcul resultat de la tentative du joueur */
            /* Réception du resultat du coup (recv) */
            recv (newsock, buffer_in, sizeof(buffer_in), 0);
            sscanf(buffer_in,"%d%d",&lig,&col);
            res = recherche_tresor(N, 8, 8, lig, col);
            
            sprintf(buffer_out,"%d", res);
            /* Envoi de la requête au serveur (send) */
            send(newsock,buffer_out,sizeof(buffer_out),0);
        }
    }
    return 0;
} // end main
