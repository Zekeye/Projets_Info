#include<stdio.h>

int main(void){
    char texte;
    int cpt_min=0;
    int cpt_maj=0;
    int cpt_reste=0;
    printf("\nTapez votre texte :\n");
    scanf("%c",&texte);
        while (texte!='.'){
            if (texte>='a' && texte<='z'){
                cpt_min=cpt_min+1;
            }
            if (texte>='A' && texte<='Z'){
                cpt_maj=cpt_maj+1;
            }
            else{
                cpt_reste=cpt_reste+1;
            }
        }
    printf("\nVotre texte contient %d minuscules, %d majuscules et % d'autres caractères (espace, ponctuation...).\n",cpt_min,cpt_maj,cpt_reste);
    return 0;
}
    
