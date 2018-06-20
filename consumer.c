#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>

#define SEM_NAME "/unique_id_here"

int main(int argc,char* argv[])
{
	int delta, free_resources, i = 0;
	sem_t *semaphore;

	/* Übergebene Argumente prüfen */
	if(argc!=2){
		fprintf(stderr,"usage: %s <Anzahl Ressourcen>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Übergebene Anzahl von Resourcen in int wandeln und auf >0 prüfen */
	delta = atoi(argv[1]);
	if(delta <= 0) {
		fprintf(stderr, "numbers of resources must be higher than 0");
		exit(EXIT_FAILURE);
	}

	/* Öffnen des Semaphors */
	semaphore = sem_open(SEM_NAME, O_CREAT);

	/* Freigeben der Ressourcen */
	for(; i < delta; i++) {
		sem_wait(semaphore);
	}

	/* Anzahl nun freier Ressourcen abfragen */
	if(sem_getvalue(semaphore, &free_resources) == -1) {
		fprintf(stderr, "sem_getvalue: %d", errno);
		exit(EXIT_FAILURE);
	}

	/* Anzahl der freigegebene und der insgesamt freien Ressourcen ausgeben */
	printf("free resources: %d\ntotal free resource: %d\n", delta, free_resources);

	exit(EXIT_SUCCESS);
}
