#include <stdio.h>
#include "solutions.h"
#include "triangle.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

int verif_triangle(int pascal[], triangle tr, int ordre) {
    int k=0;
    for (int i=0; i<ordre; i++)
        for (int j=0; j<=i; j++)
            if (tr[i][j] != pascal[k++])
                return 0;
    return 1;
}

void verif_max_ligne(int ordre, int sol) {
    triangle tr_tmp = allouer_triangle(ordre);
    construire_triangle_pascal(tr_tmp, ordre);
    int max = max_nb_pair_ligne(tr_tmp, ordre);
    liberer_triangle(tr_tmp, ordre);
    printf("Résultat : %d, Solution : %d. ", max, sol);
    if (max == sol)
        printf(GREEN " [OK] " RESET);
    else
        printf(RED " [KO] " RESET);
    printf("\n");
}

int main(void) {

    triangle tr;
    int ordre = 10;

    // Allocation triangle
    tr = allouer_triangle(ordre);

    // Test triangle Pascal
    printf("-----------------------------\n");
    printf("Triangle de Pascal d'ordre %d\n", ordre);
    printf("-----------------------------\n");
    construire_triangle_pascal(tr, ordre);
    afficher_triangle(tr, ordre);
    if (verif_triangle(tr10_pascal, tr, ordre))
        printf("Triange de Pascal" GREEN " [OK] " RESET);
    else
        printf("Triangle de Pascal" RED " [KO] " RESET);
    printf("\n\n");

    // Tests somme ligne
    printf("----------------------------------\n");
    printf("Somme des lignes (puissances de 2)\n");
    printf("----------------------------------\n");
    for (int i=0; i<ordre; i++) {
        int s = somme_ligne(tr, i);
        if (s == tr10_somlig[i])
            printf("%d" GREEN " [OK] " RESET, s);
        else
            printf("%d" RED " [KO] " RESET, s);
    }
    printf("\n\n");

    // Tests somme colonne
    printf("------------------\n");
    printf("Somme des colonnes\n");
    printf("------------------\n");
    for (int i=0; i<ordre; i++) {
        int s = somme_colonne(tr, ordre, i);
        if (s == tr10_somcol[i])
            printf("%d" GREEN " [OK] " RESET, s);
        else
            printf("%d" RED " [KO] " RESET, s);
    }
    printf("\n\n");

    // Tests somme diago
    printf("-----------------------------------------\n");
    printf("Somme des diagonales (suite de Fibonacci)\n");
    printf("-----------------------------------------\n");
    printf("0 ");
    for (int i=0; i<ordre; i++) {
        int f = somme_diago_ascendante(tr, i);
        if (f == tr10_fibo[i+1])
            printf("%d" GREEN " [OK] " RESET, f);
        else
            printf("%d" RED " [KO] " RESET, f);
    }
    printf("\n\n");

    // Liberation triangle
    liberer_triangle(tr, ordre);

    // Tests max nb pairs par ligne
    printf("-------------------------------\n");
    printf("Max des nombres pairs par ligne\n");
    printf("-------------------------------\n");
    printf("Test sur un triangle d'ordre 6 :\n");
    verif_max_ligne(6, max_pair_lig_tr6);
    printf("Test sur un triangle d'ordre 10 :\n");
    verif_max_ligne(10, max_pair_lig_tr10);
    printf("Test sur un triangle d'ordre 20 :\n");
    verif_max_ligne(20, max_pair_lig_tr20);

    return 0;
}
