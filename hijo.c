
#include "proxy.h"

int hijo (char *mem_buff,void *semaforo,int sdtc, struct sockaddr_in dir_cliente){

	
	char buffer[4096]; /*almacena la comunicacion*/
	int leido; /*almacena lo q se lee desde el port 5000 al 8080*/
	int sdmotion; /*descriptor q inicia el socket de comunicacion */	
	int leidomotion;
	char buffermotion[4096];
	struct sockaddr_in Direccion; //Estructura necesaria para la funcion bind()
	//crear fecha y hora
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128], cadena[128];
    
	pthread_t tid; //declaro la declaracion del hilo
		
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
	Direccion.sin_addr.s_addr = INADDR_ANY;
	
	leido=read(sdtc,buffer, sizeof(buffer));
	if(leido== -1){
		printf("error en leido \n");
		return -1;
	}

	strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
   	sprintf(cadena, "%s: fecha y hora:%s\n",inet_ntoa(dir_cliente.sin_addr),output);
	
	if (connect (sdmotion, (struct sockaddr *)&Direccion, sizeof Direccion) == -1){
		perror("error en el connect");
		return -1;	
		}

		int hilo;	
		hilo = pthread_create (&tid, NULL, clientes, (void *)cadena);
	
		if(hilo !=0){
			perror("error al crear un hilo\n");
			return -1;
		}

	int escribir;
	
	escribir=write(sdmotion, buffer, leido);
	
	if(escribir== -1){
		printf("error en el write\n");
		return -1;
	}

	int verificar;

	verificar=parsear(buffer,sdmotion, sdtc);
	
	if(verificar == -1){
		printf("error verificar\n");
	}
	while ((leidomotion=read(sdmotion,buffermotion, sizeof buffermotion)) > 0){
		
		int escribir2;

		escribir2=write(sdtc,buffermotion,leidomotion);
		if (escribir2 == -1)
		{
			printf("error escribir2 hijo\n");
			return -1;
		}

		 }
	
	close(sdmotion);

	sem_post(semaforo);

	
return 0;

}

