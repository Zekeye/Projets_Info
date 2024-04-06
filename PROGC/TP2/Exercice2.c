#include<stdio.h>

int main(void){
    int cpt_l=0;
    int cpt_v=0;
    char a;
    bool erreur;
    scanf("%c",&a);
    while (a!='#' && erreur==False){
        if (a>='a' && a<='z'){
            cpt_l=cpt_l+1;
        }
        if (a=='a'||a=='e'||a=='i'||a=='o'||a=='u'||a=='y'){
            cpt_v=cpt_v+1;
        q}
        if (a!='' && a>='a' && a<='z' ){
            print
            erreur==True
        }
        scanf("%c",&a);
    }
    printf("\nOn compte %d lettres et %d voyelles.\n",cpt_l,cpt_v);
    
    return 0;
}
