#include "proxy.h"

int parsear (char *buffer,int sdmotion,int sdtc){
	
	int archivo; //archivo de configuracion
	char *ipserver; // guarda ip
	int abrir; //  leer el archivo
	char * dirraiz; // ruta
	char *puertostring;//Para luego convertirlo a int
	char *path  = NULL; // lee la ruta
	char bufferArchivo[256]; // guardar el archivo
	
	
	/*if(strtok(buffer, " "))
	{
		path = strtok(NULL, " ");
		if(path)
			path=strdup(path);
	}
	printf("path:%s\n",path);
	*/
	if((archivo = open("archivoConf.txt",O_RDONLY,0))<0){
		perror("Error al abrir el archivo");
		return -1;
	}
	
	while((abrir=read(archivo,bufferArchivo, sizeof bufferArchivo)) > 0){		
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

		if(strncmp(path,"/index.html",11)==0){
			
					char * extension="html"; //guardar html
					
					strncat(dirraiz,path,11);
					
					abrirArchivo(sdtc,dirraiz,extension);

  		 	}//index.html
  		 	else{
  		 		funcionArgumentos(path,sdtc);

  		 	}
  		}//while

  		return 0;

  	}
	//parsear(buffer,sdmotion, sdtc);
	//probar, no necesito ni conectarme a motion, ni bajar el sem, 
	// si es index, mando el form, y retorno,  
	// si es action , hago el cron, retorno
	// en el else bajar el sem


