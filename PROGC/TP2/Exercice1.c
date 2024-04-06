#include<stdio.h>
#include<math.h>
#include<stdbool.h>

int main(void){
    int a;
    printf("Entrez une annee :");
    scanf("%d",&a);
    bool bis=(a%4==0 && a%100!=0)||(a%400==0);
    if (bis){
        printf("L'annee est bissextile");
    }
    else{
        printf("L'annee n'est pas bissextile");
    }
        
    return 0;
}
