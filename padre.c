#include "proxy.h"

int padre(){

	int archivo;
	int escribir;
	int escribir2;
	printf("llego al padre\n");

	if((archivo = open("clientesConectados.txt",O_RDWR | O_APPEND ,0))<0){
		perror("Error al abrir el archivo");
		return -1;
	}
	
	
	escribir=write(archivo,"padre fin",9);
	if(escribir == -1)
	{
        			perror("error al escribir el archivo padre\n");    // strictly not an error, it is allowable for fewer characters than requested to be written.
        			return -1;
        		}
        		escribir2=write(archivo,"\n",1);
        		if(escribir2 == -1)
        		{
        			perror("error al escribir el archivo padre2\n");    // strictly not an error, it is allowable for fewer characters than requested to be written.
        			return -1;
        		}
        		
        		
        		return 0;
        	}
