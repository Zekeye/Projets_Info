#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "liste_td.h"


int main(){

	List* l = list();

	int i;

	//l'indice démarre à 0 !
	for(i=0;i<10;i++) l = insert_back(l,i);

	printf("###########################\n");
    printf("###########################\n");
    printf("taille  %d \n",l->taille);
    printf("###########################\n");

	printf("cas 1 : ajoute en fin de liste\n");
	l =  insert_back(l,100);	
	for(i=0;i<l->size;i++) printf("at %d\n",l[i] );


	printf("###########################\n");

	printf("cas 2 :ajout liste vide (création nouvelle liste) \n");
	List* l2 = list();
	l2 =  insert_at(l2,100);	
	printf("at %d\n",l2[i] );

	printf("###########################\n");


	printf("cas 2.2 :ajout début de liste \n");
	l =  insert_front(l,200);	
	for(i=0;i<l->size;i++) printf("at %d\n",l[i] );


	printf("###########################\n");



	printf("###########################\n");	
	printf("###########################\n");
    printf("suppression \n");

    printf("###########################\n");
    printf("Suppression 1er élément \n");
    l =  supp_front(l);
    for(i=0;i<l->size;i++) printf("at %d\n", l[i] );
    printf("###########################\n");
    printf("taille  %d \n",l->taille);
    printf("###########################\n");
    printf("Suppression dernier élément \n");
    l =  supp_back(l);
    for(i=0;i<l->size;i++) printf("at %d\n",l[i] );

return(0);
}
