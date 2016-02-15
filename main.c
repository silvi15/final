#include "proxy.h"

int main (int argc, char *const argv[]){

	/*socket descriptor*/
	int sd;
	int longmax = 10;	
	int puerto = 5000;
	int reuse;
	/* sdtc: socket descriptor totalmente conectado */
	int sdtc;
	socklen_t longitud_cliente;
	/* Definimos la estructura vacia con {}*/
	struct sockaddr_in mi_direccion;
	/* estructura para definir las ip externas q se conectan*/
	struct sockaddr_in dir_cliente;
		
	/* Creamos un extremo de comunicacion asociado a un descriptor */
	sd = socket (PF_INET, SOCK_STREAM, 0);
		
	void *ptr1 = NULL;
	
	char *mem_buff;

	sem_t *semaforo1;
	/* al puntero le asignamos la memoria compartida*/
	ptr1 = mmap (NULL, SENSIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	if (*(char *) ptr1  == -1){
		perror ("Error en mmap ptr1\n");
		return -1;
	}

	mem_buff = (char *)(ptr1 + sizeof(sem_t));
	
	semaforo1 = (sem_t *)ptr1;
//0 para sem en hilos, sem inicializado en 1
	if (sem_init(semaforo1, 0 , 1) < 0){
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
            break;

            case 0: // proceso Hijo
            	atenderHijo(mem_buff,semaforo1,sdtc,dir_cliente);

            return 0;
            break;            
            
      } // fin switch    

      close (sdtc);
      
	}//while

	return 0;
}
