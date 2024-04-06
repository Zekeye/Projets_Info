#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int Affichage(char repertoire[]){
	struct dirent *e;
	struct stat infos;
	char DesE[512];
	DIR *rep = opendir(repertoire);
	long taille=0, taille_t;

	if(rep==NULL){
		perror("echec ouveture repertoire");
		return -1;
	}
	strcpy(DesE,repertoire);
	strcat(DesE,"/");

	while ((e=readdir(rep))!=NULL){
		if(strcmp(e->d_name,".") && strcmp(e->d_name,"..")){
			strcat(DesE, e->d_name);
			if (stat(DesE,&infos)!=-1){
				if(S_ISDIR(infos.st_mode)){
					taille_t=Affichage(DesE);
					printf("	Total %-30s : %8ld octets\n", 						DesE,taille_t);
				}
				else{
					taille_t=infos.st_size;
					printf("  %-40s : %8ld octets\n", DesE,taille_t);
				}
				taille+=taille_t;
				strcpy(DesE,repertoire);
				strcat(DesE,"/");
			}
			else{
				perror(DesE);
			}
		}
	}
	closedir(rep);
	return taille;		

}

int main(int argc, char *argv[]){
	struct stat infos;

	if(argc!=2){
		fprintf(stderr,"Usage : %s repertoire\n", argv[0]);
		return 1;
	}

	if (stat(argv[1], &infos)==-1){
		perror(argv[1]);
		return 2;
	}

	if (!S_ISDIR(infos.st_mode)){
		fprintf(stderr, "%s: no such directory\n", argv[1]);
		return 2;
	}

	printf("\n    TOTAL %-26s : %81d octets\n", argv[1], Affichage(argv[1]));

	return 0;
}
