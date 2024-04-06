/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD List vu en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>

#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct s_LinkedElement {
	int value;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement * whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_List {
	LinkedElement *sentinel;
	int size;
};


/*-----------------------------------------------------------------*/

List *list_create() {
	List *l = malloc(sizeof(struct s_List));
	l->size=0;
	l->sentinel = malloc(sizeof(struct s_LinkedElement));
 	l->sentinel->previous=l->sentinel;
	l->sentinel->next=l->sentinel;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int v) {
	LinkedElement *s = malloc(sizeof(struct s_LinkedElement));
	s->value=v;
	s->next=l->sentinel;
	s->previous=s->next->previous;
	s->next->previous=s;
	s->previous->next=s;
	l->size+=1;
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
	LinkedElement *n = (*l)->sentinel->next;
	while(n!=((*l)->sentinel)){
		LinkedElement *temp=n;	
		n=n->next;	
		free(temp);
		
	}
	free(*l);	
	*l=NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int v) {
	LinkedElement *s = malloc(sizeof(struct s_LinkedElement));
	s->value=v;
	s->previous=l->sentinel;
	s->next=s->previous->next;
	s->next->previous=s;
	s->previous->next=s;
	l->size+=1;
	return l;
}

/*-----------------------------------------------------------------*/

int list_front(List *l) {
	LinkedElement *n = l->sentinel->next;
	return (n->value);
}

/*-----------------------------------------------------------------*/

int list_back(List *l) {
	LinkedElement *n = l->sentinel->previous;
	return (n->value);
}

/*-----------------------------------------------------------------*/

List *list_pop_front(List *l) {
	LinkedElement *n = l->sentinel->next;
	l->sentinel->next->next->previous=l->sentinel;
	l->sentinel->next=l->sentinel->next->next;
	free(n);
	l->size-=1;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_pop_back(List *l){
	LinkedElement *n = l->sentinel->previous;
	l->sentinel->previous->previous->next=l->sentinel;
	l->sentinel->previous=l->sentinel->previous->previous;
	free(n);
	l->size-=1;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_insert_at(List *l, int p, int v) {
	LinkedElement *n = l->p;
	l->p=v;
	return l;
}


/*-----------------------------------------------------------------*/

List *list_remove_at(List *l, int p) {
	LinkedElement *n = l->p;
	free(n);
	l->size-=1;
	return l;
}

/*-----------------------------------------------------------------*/

int list_at(List *l, int p) {
	LinkedElement *n = l->p;
	return (n->value);
}

/*-----------------------------------------------------------------*/

bool list_is_empty(List *l) {
	if(l->sentinel->next==l->sentinel && l->sentinel->previous==l->sentinel){
		return true;
	}
	else
		return false;
}

/*-----------------------------------------------------------------*/

int list_size(List *l) {
	return l->size;
}

/*-----------------------------------------------------------------*/

List * list_map(List *l, SimpleFunctor f) {
	LinkedElement *n = l->sentinel->next;
	while(n!=(l->sentinel)){
		n->value = f(n->value);
		n=n->next;
	}
	return l;
}


List *list_reduce(List *l, ReduceFunctor f, void *userData) {
	LinkedElement *n = l->sentinel->next;
	while(n!=(l->sentinel)){
		f(n->value, userData);
		n=n->next;
	}
	return l;
}

/*-----------------------------------------------------------------*/

List *list_sort(List *l, OrderFunctor f) {
	(void)f;
	return l;
}

