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
	//int nroproc;
	int longmax = 10;	
	int puerto = 5000;
	int reuse;
	//int estado_hijo;
	

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
    
	void *ptr1 = NULL;
    
    char *mem_buff;

    sem_t *semaforo1;
    
    
    int memsize = (sizeof(char *) * 1024) + sizeof(sem_t);

    ptr1 = mmap (NULL, memsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //ptr1 = (char *) mmap (NULL, memsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        
    //printf("posicion de memoria ptr1: %p \n", ptr1);
   
    if (*(char *) ptr1  == -1){
        perror ("Error en mmap ptr1\n");
        return -1;
    }

    mem_buff = (char *)(ptr1 + sizeof(sem_t));
    
    semaforo1 = (sem_t *)ptr1;

    //printf("semaforo 1: %p \n", (sem_t *) semaforo1);

    if (sem_init(semaforo1, 1 , 0) < 0){
        perror ("semaforo 1");
        return -1;
    };	

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
		
	
	switch(fork()){
            case -1: // error fork
                perror("Error en la creacion de fork(hijo)");
                return -1;

            case 0: // proceso hijo
                
                   
                printf("mem_buff Hijo %s\n",mem_buff);
            
                hijo(mem_buff,semaforo1,sdtc,dir_cliente);
               // sem_post(semaforo1);
                return 1;
               
         
            default: // proceso padre
            	sem_wait(semaforo1);
                padre(mem_buff,semaforo1);
                
      
      } // fin switch    


	//sem_destroy(&semaforo1);
	close (sdtc);
	 	
	}//while

	return 0;
}

/*

	nroproc = fork ();

		//codigo del hijo
		if (nroproc == 0){
			
			int valor;

			sem_getvalue(&semaforo1,&valor);

			printf("valor del sem antes del wait:%d\n",valor );

			sem_wait(&semaforo1);

			int valor2;

			sem_getvalue(&semaforo1,&valor2);


			printf("valor del sem despues del wait:%d\n",valor2 );

					 	
			estado_hijo = hijo (sdtc,semaforo1,dir_cliente); // funcion crear hijo

			if (estado_hijo != 0){
				perror ("Error en hijo");
				return -1;
			}
		

		
			//hago un return 0 para que tenga vida mientras viva el cliente, dps muere
			return 0;

		}
*/


