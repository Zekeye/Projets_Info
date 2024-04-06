#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Maillons Maillon;
typedef struct list_db Liste;

struct Maillons{
	int v;
	struct Maillons *next;
	struct Maillons *previous;
};
	


struct list_db{
	unsigned int taille;
	Maillon *sentinelle
};

Liste  *list();

Liste insert_front(Liste *l, int v);

Liste insert_back(Liste *l, int v);

Liste insert_at(Liste *l, int p, int v);

bool list_empty(Liste *l);

Liste supp_front(Liste *l);

Liste supp_back(Liste *l);

Liste supp_at(Liste *l, int p);
