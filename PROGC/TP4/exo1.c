#include<stdio.h>

int main(void){
    char signature[3];
    int nombre_colonnes;
    int nombre_lignes;
    unsigned char niveau_gris;
    char image[i][j];
    printf("\nSignature:\n");
    scanf("%s",signature);
    printf("\nNombre de colonnes:\n");
    scanf("%d",&nombre_colonnes);
    printf("\nNombre de lignes:\n");
    scanf("%d",&nombre_lignes);
    printf("\nPlus grand niveau de gris:\n");
    scanf("%s", niveau_gris);
    printf("\nNiveau de gris de chaque pixel:\n");
    for(i=0; i<=nombre_lignes; i++){
        for(j=0; j<=nombre_colonnes; j++){
            scanf("%hhu",&image[i][j]);
        }
    }
    return 0;
}
    
