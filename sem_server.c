#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>
#include "sem_name.h"

static int running = 1;

static void shutdown(int signo) {
	running = 0;
}

int main(void) {
	int free_resources;
	sem_t *semaphore;
	
	signal(SIGTERM, shutdown);
	signal(SIGINT, shutdown);
	
	/* Anlegen des Semaphors mit Startwert 1*/
	semaphore = sem_open(SEM_NAME, O_CREAT, 0666, 1);

	/* Beginn Serverschleife */
	while(running) {
		/* Abfragen wieviel Ressourcen frei sind und ausgeben */
		sem_getvalue(semaphore, &free_resources);

		printf("free_resources: %d\n", free_resources);

		/* eine Sekunde warten */
		sleep(1);

	/* Ende Serverschleife */
	}
		
	/* Semaphor schließen und löschen */
	sem_close(semaphore);
	sem_unlink(SEM_NAME);
	
	exit(EXIT_SUCCESS);
}
