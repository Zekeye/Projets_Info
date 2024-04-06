#include <stdio.h>
#include <stdbool.h>

#include "hanoi.h"



void initialiserJeu(int N, Jeu tours){
	for(i=0, i<=3, i++){
		tours->tours[i]=init_pile(i);
	tours->tours[0]=empiler(i, N);
	}
}


void deplacerAnneau(Jeu tours, int depart, int arrivee);
	if deplacementPossible(&tours, depart, arrivee){
		depiler(tours->tours[depart]);
		empiler(tours->tours[arrivee]);
		printf("L'anneau a été déplacé de la tour %d à la tour %d\n", depart, arrivee);
	else
		printf("Le deplacement n'est pas valide\n");
		deplacerAnneau(Jeu tours, depart, arrivee);
	}
}


bool deplacementPossible(Jeu tours, int depart, int arrivee){
	if (sommet(tours->tours[depart]) > (sommet(tours->tours[arrivee]){
		return true;
	else
		return false;
	}
}

void afficherJeu(Jeu tours){
	for(i=0, i<=3, i++){
		printf("%d\n", tours->tours[i]);
		print("-----------------------------\n");
}
	

