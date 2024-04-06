#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

triangle allouer_triangle(int ordre) {

    triangle tr = malloc(ordre * sizeof(int *));
    for (int i=0; i<ordre; i++)
        tr[i] = malloc((i+1) * sizeof(int));
    return tr;
}

void liberer_triangle(triangle tr, int ordre) {

    for (int i=0; i<ordre; i++)
        free(tr[i]);
    free (tr);
}

void afficher_triangle(triangle tr, int ordre) {

    for (int i=0; i<ordre; i++) {
        for (int j=0; j<=i; j++)
            printf("%d ", tr[i][j]);
        printf("\n");
    }
}

/*********************
 * FONCTIONS A FAIRE *
 *********************/

void construire_triangle_pascal(triangle tr, int ordre) {
  for (int i=0; i<ordre-1; i++){
    tr[i][0]=1;
    for (int j=1; j<ordre-1; j++){
      tr[i][j]=tr[i-1][j-1]+tr[i-1][j];

    }
  }
}

// ligne = indice de 0 à ordre-1
int somme_ligne(triangle tr, int ligne) {
    construire_triangle_pascal(tr, ligne+1);
    int som=2^ligne;

    
    return som;
}

// col = indice de 0 à ordre-1
int somme_colonne(triangle tr, int ordre, int col) {
    int som=0;
    int ligne=0;
    construire_triangle_pascal(tr, ordre);
    while(ligne<=ordre){
      som=som+tr[ligne][col];
      ligne++;
    }
    return 0;
}

// ligne = indice départ diago (de 0 à ordre-1)
int somme_diago_ascendante(triangle tr, int ligne) {

    return 0;
}

int max_nb_pair_ligne(triangle tr, int ordre) {
    
    return 0;
}
