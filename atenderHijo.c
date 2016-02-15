
#include "proxy.h"

int atenderHijo (char *mem_buff,void *semaforo,int sdtc, struct sockaddr_in dir_cliente){

	
	char buffer[4096]; /*almacena la comunicacion*/
	int leido; /*almacena lo q se lee desde el port 5000 al 8080*/
	int sdmotion; /*descriptor q inicia el socket de comunicacion */	
	int leidomotion;
	char buffermotion[4096];
	struct sockaddr_in Direccion; //Estructura necesaria para la funcion bind()

	char *path  = NULL; // lee la ruta
	int archivo; //archivo de configuracion
	char *ipserver; // guarda ip
	int abrir; //  leer el archivo
	char * dirraiz; // ruta
	char *puertostring;//Para luego convertirlo a int
	char bufferArchivo[256]; // guardar el archivo


	//crear fecha y hora
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128], cadena[128];

	pthread_t tid; //declaracion del hilo

	/* Abrimos el socket */
	/* AF_INET porque el cliente puede estar en una PC distinta al servidor */
	/* SOCK_STREAM porque se utilizara el protocolo TCP */
	if ((sdmotion = socket (AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Error en socket()\n");
		return -1;
	}

	/* Vamos a atender el servicio */
	Direccion.sin_family = AF_INET; // Mismo que para la fucion Socket()
	Direccion.sin_port = htons(8080); //Puerto del servicio
	Direccion.sin_addr.s_addr = INADDR_ANY;//direccion
	
	leido=read(sdtc,buffer, sizeof(buffer));
	
	if(leido== -1){
		perror("error en leido \n");
		return -1;
	}

	//parsear(buffer,sdmotion, sdtc);
	//probar, no necesito ni conectarme a motion, ni bajar el sem, 
	// si es index, mando el form, y retorno,  
	// si es action , hago el cron, retorno
	// en el else bajar el sem

	// parseo el buffer
	if(strtok(buffer, " "))
	{
		path = strtok(NULL, " ");
		if(path)
			path=strdup(path);
	}

	printf("path:%s\n",path);// resultado de la ruta parseada

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

	}//while

	strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
	sprintf(cadena, "%s: fecha y hora:%s\n",inet_ntoa(dir_cliente.sin_addr),output);

	int hilo;	
	hilo = pthread_create (&tid, NULL, escribirClientes, (void *)cadena);
	
	if(hilo !=0){
		perror("error al crear un hilo\n");
		return -1;
	}

	if(strncmp(path,"/index.html",11)==0){
	
		char * extension="html"; //guardar html
					
		strncat(dirraiz,path,11);
		printf("entrar al if\n");					
		abrirArchivo(sdtc,dirraiz,extension);
		close(sdtc);
		return 0;
	}
	if(strncmp(path,"/accion.html",12)==0){
	
		printf("funcion cron\n" );
		leerArgumentos(path,sdtc);
		close(sdtc);
		return 0;
	}

	if(strncmp(path,"/snapshot",9)==0){
		sem_wait(semaforo);


		if (connect (sdmotion, (struct sockaddr *)&Direccion, sizeof Direccion) == -1){
			perror("error en el connect");
			sem_post(semaforo);
			return -1;	
		}

		int escribir;
		
		escribir=write(sdmotion, buffer, leido);
		
		if(escribir== -1){
			perror("error en el write\n");
			sem_post(semaforo);
			return -1;
		}


		while ((leidomotion=read(sdmotion,buffermotion, sizeof buffermotion)) > 0){
			
			int escribir2;

			escribir2=write(sdtc,buffermotion,leidomotion);
			if (escribir2 == -1)
			{
				printf("error escribir2 hijo\n");
				sem_post(semaforo);
				return -1;
			}

		}
		
		sem_post(semaforo);
		close(sdmotion);
	}

	// Cualquier otro caso, por ejemplo /favicon.ico
	close(sdtc);
	
	return 0;

}

