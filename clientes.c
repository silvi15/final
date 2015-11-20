#include "proxy.h"

void *clientes(void * output){

	int archivo;
  int escribir;

	if((archivo = open("clientesConectados.txt",O_RDWR | O_APPEND ,0))<0){
			printf("Error al abrir el archivo");
			
			}
	
    
   			escribir=write(archivo,"cliente:",8);
        if(escribir == -1){
          printf("error write 1 cliente\n");

        }
   			if(write(archivo,output, strlen((char *)output)) != strlen((char *)output))
    			{
        			printf("error write 2 cliente\n");    // strictly not an error, it is allowable for fewer characters than requested to be written.
        	
    			}
        
    		write(archivo,"\n",1);

    		
}