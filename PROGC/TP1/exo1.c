#include<stdio.h>

int main(void){
    int nb_valeurs;
    int valeurs_saisies[100];
    int pair;
    int impair;
    int i=0;
    printf("\nCombien de valeurs souhaitez-vous saisir ?\n");
    scanf("%d",&nb_valeurs);
    printf("\nSaisissez les valeurs (séparées par un espace) :\n");
    
    for(i=0;i<nb_valeurs;i++){
        scanf("%d",&valeurs_saisies[i]);
        if (valeurs_saisies[i]%2==0){
            pair=pair+1;
        }
        else{
            impair=impair+1;
        }
    }
    printf("\nIl y a %d nombres pairs et %d nombres impairs.\n",pair,impair);
    return 0;
}
