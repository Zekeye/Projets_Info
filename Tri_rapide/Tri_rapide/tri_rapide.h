#ifndef RAPIDE_H
#define RAPIDE_H

#include <stdio.h>
#include "pile.h"

void echanger(int* x, int* y);
int partitionner(int* T, int ind_premier, int ind_dernier);
void tri_rapide(int* T, int ind_premier, int ind_dernier);
void tri_rapide_iteratif(int* T, int taille);

#endif
