/*************************************************************
* proto_tdd_v3 -  récepteur                                  *
* TRANSFERT DE DONNEES  v3                                   *
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
    paquet_t pack;
    int numerotation=16;
    int fin = 0; /* condition d'arrêt */    
    int paquet_attendu = 0;
    pack.type=ACK;
    pack.num_seq=0;
    pack.lg_info=0;
    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while ( !fin ) {

        // attendre(); /* optionnel ici car de_reseau() fct bloquante */
        de_reseau(&paquet);
        
        if (verifier_controle(paquet)){
            /* extraction des donnees du paquet recu */
	    for (int i=0; i<paquet.lg_info; i++) {
	    	message[i] = paquet.info[i];   
	    }     
            if (paquet.num_seq == paquet_attendu){
		/* remise des données à la couche application */
	        fin = vers_application(message, paquet.lg_info);
	        pack.type=ACK;
	   	pack.num_seq=paquet.num_seq;
		pack.somme_ctrl=generer_controle(pack);
	        paquet_attendu=(paquet_attendu+1)%numerotation;
	        
	    }
	    vers_reseau(&pack);	
	}

    }
    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
