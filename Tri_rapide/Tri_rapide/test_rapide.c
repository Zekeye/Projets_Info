#include "tri_rapide.h"
#include "tests.h"
#include "solutions.h"
#include <stdio.h>

int main(){
  int M[1024];
  int resultat = 0;
  
  for(int i = 0; i< N; i++){

    //Tri
    tri_rapide_iteratif(tests[i], sizes[i]);

    //Verification
    char correct = 1;
    for(int j = 0; j < sizes[i]; j++){

      if(tests[i][j] != sols[i][j]){
	correct = 0;
	break;
      }
    }
    if(correct)
      resultat++;
    
  }
  fprintf(stderr,"%d", resultat);
  return 0;

}
