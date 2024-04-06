/*************************************************************
* proto_tdd_v3 -  émetteur                                   *
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
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg; /* taille du message */
    int fenetre=7, numerotation=16;    
    int evt, borne_inf=0, curseur=0;    
    
    paquet_t paquet[numerotation]; /* paquet utilisé par le protocole */
    paquet_t pack; /* paquet recu par le recepteur */


       
    init_reseau(EMISSION);


    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");
    
    de_application_mode_c((int*)11, message, &taille_msg);   
    
    /* lecture de donnees provenant de la couche application */
    de_application_mode_c((int*)14, message, &taille_msg);   

    /* tant que l'émetteur a des données à envoyer */
    while ( taille_msg != 0 ) {
	if (dans_fenetre(borne_inf,curseur,fenetre)){
	    /* construction paquet */
	    for (int i=0; i<taille_msg; i++) {
	    	paquet[curseur].info[i] = message[i];
	    }
	    paquet[curseur].lg_info = taille_msg;
	    paquet[curseur].type = DATA;
	    paquet[curseur].num_seq = curseur;
	    paquet[curseur].somme_ctrl=generer_controle(paquet[curseur]);	    
	    /* remise à la couche reseau */
	    vers_reseau(&paquet[curseur]);   
	    de_application_mode_c((int*)15, message, &taille_msg);     

	    if (curseur==borne_inf){
	    	depart_temporisateur(200);
	    }
    	    curseur=(curseur+1)%numerotation;
	/* lecture des donnees suivantes de la couche application */
	    de_application_mode_c((int*)11, message, &taille_msg);
	    de_application_mode_c((int*)14, message, &taille_msg);
	}	
	 		
	else{        	    
	    evt=attendre();
	    if (evt == -1){
	        de_reseau(&pack);
	    	if ((verifier_controle(pack)) && (dans_fenetre(borne_inf, pack.num_seq, fenetre))){
		    borne_inf=(pack.num_seq+1)%numerotation;
    		    arret_temporisateur();
		    if (borne_inf!=curseur){
			depart_temporisateur(200);
		    }
		}
	    }	
	    
	    else{ /* TIME OUT : retransmission */
		int i=borne_inf;
		depart_temporisateur(200);
		while (i != curseur){
		    vers_reseau(&paquet[i]);
		    i=(i+1)%numerotation;
		}
	    }
	}
    }
    int cpt=100;
    while(curseur != borne_inf){
	cpt-=1;
	if (cpt==0){
	    return 1;
	}
	evt=attendre();
	if (evt==-1){
	    de_reseau(&pack);
   	    if (verifier_controle(pack) && dans_fenetre(borne_inf,pack.num_seq,fenetre)){
	        borne_inf=(pack.num_seq+1)%numerotation;
	        arret_temporisateur();
	    	if (borne_inf!=curseur){
		    depart_temporisateur(200);
	        }
	    }
    	}
      	else{ /* TIME OUT : retransmission */
	    int i=borne_inf;
	    depart_temporisateur(200);
	    while (i!=curseur){
	    	vers_reseau(&paquet[i]);
	    	i=(i+1)%numerotation;
	    }
	}
    }				    	      	        	    
	printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
	return 0;
}
