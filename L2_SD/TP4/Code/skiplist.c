#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "skiplist.h"
#include "rng.h"

typedef struct s_LinkedElement {
	int value;
	int levels;
	struct s_LinkedElement **previous;
	struct s_LinkedElement **next;
} LinkedElement;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement * whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_SkipList {
	LinkedElement *sentinel;
	int nblevels;
	int size;
	RNG random;
};

SkipList skiplist_create(int nblevels) {
	SkipList d= malloc(sizeof(struct s_SkipList));
	d->size=0;
	d->nblevels=nblevels;
	d->sentinel = malloc(sizeof(struct s_LinkedElement));
	d->sentinel->levels=0;
	d->sentinel->previous = malloc((nblevels+1)*sizeof(struct s_LinkedElement *));
	d->sentinel->next = malloc((nblevels+1)*sizeof(struct s_LinkedElement *));
	d->random=rng_initialize(0);
	return d;
}

void skiplist_delete(SkipList d) {
	LinkedElement *n = d->sentinel->next[0];
	while(n!=(d->sentinel)){
		LinkedElement *temp=n;	
		n=n->next[0];
		free(temp->next);
		free(temp->previous);	
		free(temp);
	}
	free(d->sentinel->next);
	free(d->sentinel->previous);
	free(d->sentinel);
	free(d);
}

unsigned int skiplist_size(SkipList d){
	return (d->size);
}

int skiplist_at(SkipList d, unsigned int i){
	LinkedElement *n = d->sentinel->next[0];
	unsigned int temp=0;
	while (temp<i){
		n=n->next[0];
		temp++;
	}
	return (n->value);
}

void skiplist_map(SkipList d, ScanOperator f, void *user_data){
	LinkedElement *n = d->sentinel->next[0];
	while(n!=(d->sentinel)){
		f(n->value, user_data);
		n=n->next[0];
	}
	
}

SkipList skiplist_insert(SkipList d, int value) {
	int levels=rng_get_value(&(d->random), d->nblevels);
	if (value==levels){
		return d;
	}	
	else{
		d->sentinel->levels=value;
		d->size+=1;
		return d;
	}
}
