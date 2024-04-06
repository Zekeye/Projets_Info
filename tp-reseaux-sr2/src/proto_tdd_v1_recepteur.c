/*************************************************************
* proto_tdd_v1 -  récepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet; /* paquet utilisé par le protocole */
    paquet_t pack; /* paquet utilisé par le récepteur */
    int fin = 0; /* condition d'arrêt */

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
     while ( !fin ) {
    

        // attendre(); /* optionnel ici car de_reseau() fct bloquante */
        de_reseau(&paquet);
        

        /* extraction des donnees du paquet recu */
        if (verifier_controle(paquet)){ /* vérification de la somme de contrôle */ 
        
        	for (int i=0; i<paquet.lg_info; i++) {
            		message[i] = paquet.info[i];
            		
        	}
        	
        /* remise des données à la couche application */
        	pack.type=ACK;
        	fin = vers_application(message, paquet.lg_info);
        	
    	}
    	else{
		pack.type=NACK; /* Si le contrôle est invalide, envoi d'un acquittement négatif à 					l'émetteur */
		
	}
	
	vers_reseau(&pack);
	
	
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
