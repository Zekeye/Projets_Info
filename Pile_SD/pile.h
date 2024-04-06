#ifndef __PILE_H__
#define __PILE_H__

#define PILE_TAILLE 20

#include <stdbool.h>

typedef struct {
  int pile[PILE_TAILLE];
  int top;
} Pile;


// création de la pile
void creer_pile(Pile *p);


// vérifie si pile vide
bool isEmpty(Pile *p);

// rajoute un élément dans la pile par le sommet
void push(Pile *p,int elem);

// Enlève le sommet de  la pile
void pop(Pile *p);

// Retourne le sommet de la pile
int top(Pile *p);

#endif
