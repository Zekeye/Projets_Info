#include "polonaise.h"
#include <string.h>

/* Test et notation (ne pas toucher cette fonction)*/

int main(){
  int note = 0;
  int res;
  char e[256] ;
  char s[256] ;

  shunting_yard(e);
  printf("\n=e=> |%s|\n",e);
  scanf("%c", s);
  scanf("%[^\n]",s);
  printf("=s=> |%s|\n",s);

  res = (strncmp(e, s, strlen(s)) || (strlen(s) != strlen(e)));

  printf("%d", res==0);
  if (res == 0){
    note ++;
  }
  fprintf(stderr,"%d", note);
  return 0;
}
