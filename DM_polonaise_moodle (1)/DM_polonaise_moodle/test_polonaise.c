#include "polonaise.h"


/* Test et notation (ne pas toucher cette fonction)*/

int main(){
  int note = 0;
  int val = calc();
  printf("Valeur calculée = %d\n",val);
  int res;
  scanf("%d", &res);

  if(val==res){
    note+=1;
  }

  printf("%d", note);
  fprintf(stderr,"%d", note);


  /* char e[256] = {'\0'};
  shunting_yard(e);

  printf("%s", e);
  */
return 0;
}
