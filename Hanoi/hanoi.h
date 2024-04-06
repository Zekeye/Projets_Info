#ifndef HANOI_H
#define HANOI_H

#include <stdbool.h>

#define PILE_TAILLE	N


typedef struct Pile {
    int elts[PILE_TAILLE];
    int som;
} Pile;

typedef struct Pile Jeu[3] {
    int tours[NUMERO_TOUR];
    int tour_suiv=tours[(NUMERO_TOUR+1)%3]
} Jeu;


void initialiserJeu(int N, Jeu tours);
	


void deplacerAnneau(Jeu tours, int depart, int arrivee);



bool deplacementPossible(Jeu tours, int depart, int arrivee);



void afficherJeu(Jeu tours);
