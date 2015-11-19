#include "proxy.h"


int padre(){

	int archivo;
	printf("llego al padre\n");

		if((archivo = open("clientesConectados.txt",O_RDWR | O_APPEND ,0))<0){
			printf("Error al abrir el archivo");
			return -1;
			}
	
    
   			write(archivo,"padre fin",9);
   			        
    		write(archivo,"\n",1);

    		
	
	return 0;
}
