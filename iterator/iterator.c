#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "iterator.h"

#define FORWARD_ITERATION  1
#define BACWARD_ITERATION 0

typedef struct s_ListIterator ListIterator;
typedef struct _List List;
typedef struct _Maillon Maillon;

 struct _Maillon  {
	int value;
	struct _Maillon  *previous;
	struct _Maillon  *next;
};

//on ajoute une sentinel à la struct liste
struct _List {

	 Maillon *sentinel;
	 unsigned int size;

};




struct s_ListIterator {
	/*la collection associée à l'iterator*/
	List *collection;
	/*l'élément accutellement pointé par l'iterator*/
	Maillon *current;
	/*le premier élément de départ pointé part l'iterator, c'est lui qui donne la direction */
	Maillon *begin;
	/* fonction qui passe à l'élément suivant (en accord avec la direction de départ)*/
	Maillon * (*next)(Maillon *);
};


//le contructeur va exploiter la sentinelle 
List  *list(){
	List *l = malloc(sizeof(List));
	l->sentinel = malloc(sizeof(Maillon));
	l->sentinel->previous = l->sentinel->next = l->sentinel;
	l->size = 0;
	return l;
}


//Operateurs d’ajout et de suppression d’un élément à une liste doublement chaînée
List *push_back(List *l, int v){
	
	Maillon *new = malloc(sizeof(Maillon));
	new -> value = v;
	new -> previous = l -> sentinel;
	new -> next = l -> sentinel -> next;
	new -> next -> previous = new;
	l -> sentinel -> next = new;
	++(l->size);
	return(l);

}

//Opérateurs d'état du TAD Liste
bool list_empty (const List *l){
	return l->size == 0;
}


List *pop_front(List *l){
	assert(!list_empty(l));	
	Maillon *e;
	e = l->sentinel->next;
	l->sentinel->next = e->next;
	l->sentinel->next->previous = l->sentinel;
	--(l->size);
	free(e);
	return(l);
}



//affichage des éléments d'une liste
int print_i(int i){
	printf("%d\n", i);
	return i;
}



/*Constructeur*/
ListIterator *listIterator_create(List *collection, int direction){
	ListIterator *it = malloc(sizeof(ListIterator));

	it->collection = collection;

	if(direction == FORWARD_ITERATION ){
		it -> begin = collection->sentinel->next;
		it->next = goto_next;
	}else{
		it->begin = collection -> sentinel -> previous;
		it->next = goto_previous;
	}

	it->current = it -> begin;

	return it;
}


/*Fonction pour passer à l'élément suivant*/
Maillon *goto_next(Maillon *e){
	return e->next;
}

/*Fonction pour passer à l'élément précédent*/
Maillon *goto_previous(Maillon *e){
	return e->previous;
}

ListIterator *listIterator_begin(ListIterator *i){
	i->current = i->begin;
	return i;
}

bool listIterator_end(ListIterator *i){
	return i->current == i->collection->sentinel;
}

ListIterator *listIterator_next(ListIterator *i){
	i->current = i->next(i->current);
	return i;
}

int listIterator_value(ListIterator *i){
	return i->current->value;
}

/* Main */ 
int main(){

	List* l = list();
	int i;
	for(i=10;i>=1;i--){
			l = push_back(l,i);
			printf("Size %d\n",l->size );
			printf("Head %d\n" ,l->sentinel->previous->value);
			printf("Last %d\n" ,l->sentinel->next->value);
	}


	//on peut commencer par la première valeure (rappel : on a fait un push back)
	ListIterator* it = listIterator_create(l, 0);

	ListIterator* it2 = listIterator_create(l, 1);	

    printf("%d\n", listIterator_value(it));
    
    printf("%d\n", listIterator_value(it2));


    printf("C'est parti ! \n");


	for(it = listIterator_begin(it); !listIterator_end(it); it = listIterator_next(it))  printf("%d\n", listIterator_value(it));
	
	printf("dans l'autre sens \n");

	for(it2 = listIterator_begin(it2); !listIterator_end(it2); it = listIterator_next(it2))  printf("%d\n", listIterator_value(it2));

	return(0);
}
