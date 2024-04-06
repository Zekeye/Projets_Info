
#include "matrice.h"
#include "traiterLigne.h"

/* retourne 0: aucun trouve, 1: V1 trouve, 2: v2 trouve et 3: v1 et v2 trouve */
unsigned int traiterLigne(  int uneLigne[NB_COLONNES_MAX], unsigned nbC, unsigned v1, unsigned v2){
  unsigned int v1_trouve=0;
  unsigned int v2_trouve=0;
  unsigned int i;
  int res;

  while (i < nbC ){
    int v = uneLigne[i++];
    
    if (v==v1){
      v1_trouve=1;
    }

    else if (v==v2){
      v2_trouve=2;
    }
  }

  res=v1_trouve+v2_trouve;
  return (res);
  
}
