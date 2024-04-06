#include "tri_rapide.h"
#include <stdio.h>
#include "pile.c"

void echanger(int* x, int* y){
  int t = *x;
  *x=*y;
  *y=t;
}

int partitionner(int* T, int ind_premier, int ind_dernier){
  int ind_pivot = ind_premier;
  int valPivot = T [ ind_pivot ];
  int j = ind_dernier;
  // La zone T [ ind_pivot +1 , j ] est inconnue

  while (ind_pivot<j) {
    if (valPivot==T[ind_pivot+1]){
      echanger(&T[ind_pivot], &T[ind_pivot+1]);
      ind_pivot++;
     }
    else if (valPivot>T[ind_pivot+1]){
      echanger(&T[ind_pivot], &T[ind_pivot+1]);
      ind_pivot++;
     }
    else if (valPivot<T[ind_pivot+1]){
      echanger(&T[ind_pivot+1], &T[j]);
      j--;
     }
    }
  return ind_pivot ;
}


void tri_rapide(int* T, int ind_premier, int ind_dernier){
  int ind_pivot;
  if(ind_premier < ind_dernier){
    ind_pivot = partitionner(T, ind_premier, ind_dernier);
    tri_rapide(T, ind_premier, ind_pivot-1);
    tri_rapide(T, ind_pivot+1, ind_dernier);
  }
}

void tri_rapide_iteratif(int* T, int taille){
  int ind_pivot, ideb, ifin;
  pile_t pile;
  init_pile(&pile);

  empiler(&pile, 0);
  empiler(&pile, taille-1);

  while (!pile_vide(&pile)){
    ifin=sommet(&pile);
    depiler(&pile);
    ideb=sommet(&pile);
    depiler(&pile);
    ind_pivot = partitionner(T, ideb, ifin);

    if (ideb!=ind_pivot-1){
      empiler(&pile, ideb);
      empiler(&pile, ind_pivot-1);
    }

    if (ifin!=ind_pivot+1){
      empiler(&pile, ind_pivot+1);
      empiler(&pile, ifin);
    }
  }
}



int __attribute__((weak)) main(){
  int T[15]={1, -9, 5, 4, 3, 2, -1, 1, 6, 3, -6, -4, 3, 2, 0};
  int t[15]={1, -9, 5, 4, 3, 2, -1, 1, 6, 3, -6, -4, 3, 2, 0};
  int taille=15;
  int ip=0;
  int id=14;

  tri_rapide(T, ip, id);
  for(int i=0;i<15;i++){
		printf("%d\n",T[i]);
	}

  printf("\n-----------------\n");

  tri_rapide_iteratif(t, taille);
  for(int j=0;j<15;j++){
		printf("%d\n",t[j]);
	}

  return 0;
}
