#include <stdio.h>
#include <stdbool.h>


#include "pile.h"
#include "hanoi.h"

#define N 3

int main(void){
	Jeu tours;
	initialiserJeu(N, &tours);

	while (!pile_vide(tours[0]) || !pile_vide(tours[1])){
		deplacerAnneau(&tours, depart, arrivee);
		

