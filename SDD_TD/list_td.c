#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list_td.h"

Liste  *list(){
	List *l = malloc(sizeof(Liste));
	l->sentinelle= NULL;
	l->taille = 0;
	return l;
}


Liste insert_front(Liste *l, int v){
	Maillon *m=l->sentinelle;
	l->sentinelle=v;
	l->taille+=1;
	return l;
}

Liste insert_back(Liste *l, int v){
	Maillon *m=l->sentinelle->sentinelle;
	l->sentinelle->sentinelle=v;
	l->taille+=1;
	return l;
}


bool liste_empty(Liste *l){
	return l->taille=0;
}

Liste supp_front(Liste *l){
	assert(!(list_empty(l));
	Maillon *m=l->sentinelle;
	free(m);
	l->taille-=1;
	return l;
}


Liste supp_back(Liste *l, int v){
	assert(!(list_empty(l));
	Maillon *m=l->sentinelle->sentinelle;
	free(m);
	l->taille-=1;
	return l;
}
	
	
	
	
