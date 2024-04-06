#include<stdio.h>

int main(void)
    {
    double matrice[10][10];
    int ordre;
    printf("Taper l'ordre (<=10)");
    scanf("%d",&ordre);
    for(int i=0; i<ordre; i++)
        {
        for (int j=0; j<ordre; j++)
            {
            printf("valeur[%d][%d]",i,j);
            scanf("%lf",&matrice[i][j]);
            }
        }   
    int sym=1;
    for(int i=0;i<ordre;i++)
        {
        for(int j=0;j<i;j++)
            {
            if(m[i][j]!=m[j][i]
                {
                sym=0;
                printf("\nElle n'est pas symetrique.\n");
                }
            else
            {
            printf("\nElle est symetrique.\n");
            }
            }
        }
    
    return 0;
    }
            
