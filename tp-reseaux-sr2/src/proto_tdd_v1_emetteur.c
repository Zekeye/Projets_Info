/*************************************************************
* proto_tdd_v1 -  émetteur                                   *
* TRANSFERT DE DONNEES  v1                                   *
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
        
        
        paquet.num_seq=0;
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        paquet.somme_ctrl=generer_controle(paquet); : /* génération de la somme de contrôle */

        /* remise à la couche reseau */
        vers_reseau(&paquet); /* envoi du paquet  au récepteur */
        de_reseau(&pack); /* réception du paquet d'acquittement */
        
        while(pack.type==NACK){       
        	vers_reseau(&paquet);
        	de_reseau(&pack); /* Si l'acquittement est néagtif, renvoi du paquet à la couche 					  réseau */
        
        }
        
    
        
        /* lecture des donnees suivantes de la couche application */
        de_application(message, &taille_msg);
        printf("OK8\n");
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
