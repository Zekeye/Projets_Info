#include<stdio.h>

int main(void){
    int nb_valeurs;
    int i=0;
    int somme=0;
    int moyenne=0;
    int t[100];
    
    printf("Nombre de valeurs ? :");
    scanf("%d",&nb_valeurs);
    printf("Quels sont les valeurs demandees ? :");
    for(i=0;i<nb_valeurs;i++){
        scanf("%d",&t[i]);
        somme=t[i]+somme;
    }
    moyenne=somme/nb_valeurs;
    printf("\nLa moyenne est %d\n",moyenne);
    printf("\nLes valeurs supérieures à la moyenne sont :\n");
    
    for(i=0;i<nb_valeurs;i++){
        if(t[i]>moyenne){
            printf("\n%d\n",t[i]);
        }
      
    }
  return 0;
}

        
    
    
    
