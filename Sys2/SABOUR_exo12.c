#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

void Affichage(char infos[]){
	struct stat stats;

	if (stat(infos,&stats)==-1){
		perror(infos);
		return;

	}

	printf("%-20s : ", infos);

	if(S_ISDIR(stats.st_mode)){
		printf("repertoire ");
	}

	else{
		printf("fichier ");
	}

	printf("%8ld octets ", stats.st_size);
	printf("%s", ctime(&stats.st_mtime));
}

int main(int argc, char *argv[]){
	int i;
	DIR *rep;
	struct dirent *e;

	if (argc==1){
		rep=opendir(".");
		if(rep==NULL){
			perror("echec ouveture repertoire");
			return 1;
		}

		while ((e=readdir(rep))!=NULL){
			Affichage(e->d_name);
		}
		closedir(rep);
	}

	else{
		for(i=1; i<argc; i++){
			Affichage(argv[i]);
		}
	}

	return 0;
}
