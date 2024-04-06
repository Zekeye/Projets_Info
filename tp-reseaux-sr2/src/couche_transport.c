#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"
#include "application.h"

/* ************************************************************************** */
/* *************** Fonctions utilitaires couche transport ******************* */
/* ************************************************************************** */

uint8_t generer_controle(paquet_t paquet){
	unsigned char somme=0;
	
	somme = paquet.type ^ paquet.num_seq ^ paquet.lg_info;
	for (int i=0; i < paquet.lg_info; i++) {
		somme=somme^paquet.info[i];
	}
	
	return somme;
}

int verifier_controle ( paquet_t paquet){
	return generer_controle (paquet) == paquet.somme_ctrl;
}

/* ===================== Fenêtre d'anticipation ============================= */

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);
}
