#include "proxy.h"

void *clientes(void * output){

	int archivo;

	if((archivo = open("clientesConectados.txt",O_RDWR | O_APPEND ,0))<0){
			printf("Error al abrir el archivo");
			
			}
	
    
   			write(archivo,"cliente:",8);
   			if(write(archivo,output,17) != 17)
    			{
        			printf("erro al escribir el archivo\n");    // strictly not an error, it is allowable for fewer characters than requested to be written.
        	
    			}
    		write(archivo,"\n",1);

    		return 0;
}