#include "proxy.h"

int parsear (char *buffer,int sdmotion,int sdtc){
 
	int archivo; //archivo de configuracion
	char *ipserver; // guarda ip
	int abrir; //  leer el archivo
	char * dirraiz; // ruta
	char *puertostring;//Para luego convertirlo a int
	char *path  = NULL; // lee la ruta
	char bufferArchivo[256]; // guardar el archivo
	
       	
if(strtok(buffer, " "))
{
	path = strtok(NULL, " ");
	if(path)
         	path=strdup(path);
}
		printf("path:%s\n",path);
		if((archivo = open("archivoConf.txt",O_RDONLY,0))<0){
			printf("Error al abrir el archivo");
			return 0;
			}
	
			abrir=read(archivo,bufferArchivo, sizeof bufferArchivo);
			bufferArchivo[abrir]='\0';
	
			ipserver=strtok(bufferArchivo,"=");
			ipserver=strtok(NULL,"\n");
			printf("ip server:%s\n",ipserver);
	
			puertostring=strtok(NULL,"=");
			puertostring=strtok(NULL,"\n");
			printf("puerto server:%s\n",puertostring);
	
			dirraiz = strtok (NULL, "=");
			dirraiz = strtok (NULL, "\n");
			printf ("Directorio Raiz: %s\n", dirraiz);


/*			int leido,abrirPagina; // descriptores
			char bufferPagina[4096]; //guardar descriptores
			bzero(bufferPagina,4096); 
*/
			if(strcmp(path,"/index.html")==0){
		
					char * extension="html"; //guardar html
					printf("extension : %s\n",extension );
					strcat(dirraiz,path);
   					printf("dirraiz final:%s\n",dirraiz);
 					http(sdtc,dirraiz,extension);

/*
   	   				if((abrirPagina = open (dirraiz,O_RDWR , S_IRWXU))<0){
							
							perror("Error en open: ");
							write(STDOUT_FILENO,"Error al abrir ruta\n",20); 
							
						}
							while ((leido=read(abrirPagina,bufferPagina, sizeof bufferPagina)) > 0){
										write(sdtc,bufferPagina,leido);
										bzero(bufferPagina,4096);
										return 0;
								}

*/		
					


  		 	}//index.html
  			else{
  				funcion(path,sdtc);

  			}

return 0;

}


