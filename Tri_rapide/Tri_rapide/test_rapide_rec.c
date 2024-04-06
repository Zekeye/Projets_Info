#include "tri_rapide.h"
#include "tests.h"
#include "solutions.h"
#include <stdio.h>

int main(){

  int resultat = 0;
  
  for(int i = 0; i< N; i++){

    //Tri
    tri_rapide(tests[i], 0 , sizes[i]-1);

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
