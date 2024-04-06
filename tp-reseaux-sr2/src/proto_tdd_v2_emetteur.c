/*************************************************************
* proto_tdd_v2 -  émetteur                                   *
* TRANSFERT DE DONNEES  v2                                   *
*                                                            *
* Protocole sans contrôle de flux, sans reprise sur erreurs  *
*                                                            *
* E. Lavinal - Univ. de Toulouse III - Paul Sabatier         *
**************************************************************/

#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg; /* taille du message */
    paquet_t paquet; /* paquet utilisé par le protocole */
    paquet_t pack; /* paquet utilisé par le récepteur */
    int prochain_paquet=0; /* paquet attendu par le récepteur */
    int evt;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);

    /* tant que l'émetteur a des données à envoyer */
    while ( taille_msg != 0 ) {
        /* construction paquet */
        for (int i=0; i<taille_msg; i++) {
            paquet.info[i] = message[i];
        }
        
        paquet.num_seq=prochain_paquet;
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        paquet.somme_ctrl=generer_controle(paquet); /* génération de la somme de contrôle */

        /* remise à la couche reseau */
        vers_reseau(&paquet);
        depart_temporisateur(300);
        evt=attendre();
        
        while(evt!=-1){ /* Tant qu'un acquittement n'a pas été reçu, retransmission en boucle du 				paquet de données */
        	vers_reseau(&paquet);
		depart_temporisateur(300);
		evt=attendre();
	}
	
	arret_temporisateur();
	de_reseau(&pack);
	prochain_paquet=(prochain_paquet+1)%2;
              
        /* lecture des donnees suivantes de la couche application */
        de_application(message, &taille_msg);
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
