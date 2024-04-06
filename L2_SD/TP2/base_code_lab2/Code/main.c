#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"


/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */

bool isSymbol(const char c){

  if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='(' || c==')')
    return true;
  else 
    return false;
}

Queue *stringToTokenQueue(const char *expression) {

  Queue *q = createQueue();
  const char *curpos = expression;
  int nb_carac=0;
  Token *t=NULL;


  while (*curpos!='\0'){
    while (*curpos==' ' || *curpos=='\n'){
      curpos++;
    }
    if (isSymbol(*curpos)){
      t=createTokenFromString( curpos, 1 );
      q=queuePush(q, t);
    }
    curpos++;
  }
  return q;
} 

void printToken(FILE *f, void *e){
  Token *t = (Token *)e;
 
  tokenDump(f, t);

 }



void computeExpressions(FILE *input){
  char * linep=NULL;
  size_t linecap=0;
  Queue *q=NULL;


  while (getline(&linep, &linecap, input)!= -1){
    printf("Input : %s\n", linep);
    printf("Infix :");

    q = stringToTokenQueue(linep);
    queueDump(stdout, q, printToken);
    printf("\n");
  
  } 

  
}




int main(int argc, char **argv){
	FILE *input;
	
	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}
	
	input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
 
 

