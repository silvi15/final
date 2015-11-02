#include "proxy.h"

#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

int main (int argc, char *const argv[]){

	/*socket descriptor*/
	int sd;
	int nroproc;
	int longmax = 10;	
	int puerto = 5000;
	int reuse;
	int estado_hijo;
	

	/* sdtc: socket descriptor totalmente conectado */
	int sdtc;
	socklen_t longitud_cliente;
	/* Definimos la estructura vacia con {}*/
	struct sockaddr_in mi_direccion;
	//struct sockaddr_in dir_cliente = {};
	struct sockaddr_in dir_cliente;
	/* estructura para definir las ip externas q se conectan*/
	//struct sockaddr cliente;
			
	/* Creamos un extremo de comunicacion asociado a un descriptor */
	sd = socket (PF_INET, SOCK_STREAM, 0);
    
	sem_t *sem; // creamos el semaforo en 1 = verde
	
	sem_unlink ("/sem");
	sem = sem_open ("/sem", O_CREAT | O_RDWR, 0666, 1);//sem init
	//sem_post(sem);

	if (sem == SEM_FAILED)
		perror ("sem_open()");


	if (sd < 0){
		perror ("error en el socket: ");
		return -1;
	}
	
	if (setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1){
 		perror ("Error reutilizando puerto");
 		return -1;
	}

	mi_direccion.sin_family = AF_INET;
	mi_direccion.sin_port = htons(puerto);
	mi_direccion.sin_addr.s_addr = INADDR_ANY;

	if ((bind (sd, (struct sockaddr*) &mi_direccion, sizeof (mi_direccion))) < 0){
		perror ("error en bind: ");
		return -1;
	}
	
	if ((listen(sd,longmax))<0){
		perror ("error en listen");
		return -1;
	}

	longitud_cliente=sizeof(dir_cliente);
	                     
	while ((sdtc = accept (sd, (struct sockaddr*) &dir_cliente, &longitud_cliente)) > 0){	
			//while ((sdtc = accept (sd, &cliente, &longitud_cliente)) > 0){ 	

		int valor;
		sem_getvalue(sem,&valor);
		printf("valor del sem:%d\n",valor );
		sem_wait(sem);

		printf("valor del sem:%d\n",valor );

		nroproc = fork ();

		/*codigo del hijo*/
		if (nroproc == 0){
		//	sem_post(sem);
			
			estado_hijo = hijo (sdtc,sem,dir_cliente); // funcion crear hijo

			if (estado_hijo != 0){
				perror ("Error en hijo");
				return -1;
			}
		

		
			/*hago un return 0 para que tenga vida mientras viva el cliente, dps muere*/
			return 0;

		}

	close (sdtc);
	 	
	}

	return 0;
}



