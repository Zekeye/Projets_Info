#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef int ** triangle;

triangle allouer_triangle(int ordre);
void liberer_triangle(triangle tr, int ordre);
void afficher_triangle(triangle tr, int ordre);
void construire_triangle_pascal(triangle tr, int ordre);
int somme_ligne(triangle tr, int ligne);
int somme_colonne(triangle tr, int ordre, int col);
int somme_diago_ascendante(triangle tr, int ligne);
int max_nb_pair_ligne(triangle tr, int ordre);

#endif
