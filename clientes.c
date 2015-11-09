#include "proxy.h"

void *clientes(void * output){

	int archivo;

	if((archivo = open("clientesConectados.txt",O_RDWR | O_APPEND ,0))<0){
			printf("Error al abrir el archivo");
			return -1;
			}
	
    
   			write(archivo,"cliente:",8);
   			if(write(archivo,output, strlen((char *)output)) != strlen((char *)output))
    			{
        			printf("erro al escribir el archivo\n");    // strictly not an error, it is allowable for fewer characters than requested to be written.
        	
    			}
        
    		write(archivo,"\n",1);

    		return 0;
}