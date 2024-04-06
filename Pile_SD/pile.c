#include "pile.h"
#include <assert.h>
#include <stdio.h>

void creer_pile(Pile *p) {
  p->top=pile[0];
}

void push(Pile *p,int elem) {
  assert(p->top < PILE_TAILLE);
  p->pile[++(p->top)] = elem;
}


bool isEmpty(Pile *p) {
  return p->top == Pile[0];
}

void pop(Pile *p) {
  assert (!isEmpty(p));
  --(p->top);
}

int top(Pile *p) {
  assert (!isEmpty(p));
  return p->pile[p->top];
}

int main(){
  
  Pile pile;


  printf("message");
  
  creer_pile(&pile);

  push(&pile, 1);

  printf("Element en tete de pile : %d\n", top(&pile));

  push(&pile, 2);
  push(&pile, 3);
  push(&pile, 4);

  int sommet_sup=top(&pile);

  pop(&pile);

  printf("Element supprime qui etait en tete: %d\n", sommet_sup);

  return 0;
}
