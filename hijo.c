
#include "proxy.h"

int hijo (int sdtc, sem_t * sem){

	
	char buffer[4096]; /*almacena la comunicacion*/
	int leido; /*almacena lo q se lee desde el port 5000 al 8080*/

	int sdmotion; /*descriptor q inicia el socket de comunicacion */	
	int leidomotion;
	char buffermotion[4096];
	
	struct hostent *Host; //IP del servidor
	struct sockaddr_in Direccion; //Estructura necesaria para la funcion bind()

	//crear fecha y hora
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    
	pthread_t tid; //declaro la declaracion del hilo
	//printf ("hijo = %d\n", getpid());

	/* Obtengo la ip a la cual conectarme */
	if ((Host = gethostbyname ("localhost")) == NULL)
		printf ("Error en gethostbyname()\n");
	//else
	//	printf ("IP: %s\n", Host->h_name);

	/* Abrimos el socket */
	/* AF_INET porque el cliente puede estar en una PC distinta al servidor */
	/* SOCK_STREAM porque se utilizara el protocolo TCP */
	if ((sdmotion = socket (AF_INET, SOCK_STREAM, 0)) == -1)
		printf ("Error en socket()\n");

	/* Vamos a atender el servicio */
	Direccion.sin_family = AF_INET; // Mismo que para la fucion Socket()
	Direccion.sin_port = htons(8080); //Puerto del servicio
	Direccion.sin_addr.s_addr = htonl (0x7f000001); //Direccion del servidor

	leido=read(sdtc,buffer, sizeof(buffer));
	//printf("buffer del navegador \n%s",buffer);
	
	strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
   	printf("fecha y hora:%s\n",output);
	
	if (connect (sdmotion, (struct sockaddr *)&Direccion, sizeof Direccion) == -1)
		perror ("connect");	

		int hilo;	
		hilo = pthread_create (&tid, NULL, clientes, (void *)output);
	
		if(hilo !=0){
			printf("error al crear un hilo\n");
			return -1;
		}
//		pthread_exit(NULL);

			

	write(sdmotion, buffer, leido);
	parsear(buffer,sdmotion, sdtc,sem);

	while ((leidomotion=read(sdmotion,buffermotion, sizeof buffermotion)) > 0){
		
			
		write(sdtc,buffermotion,leidomotion);
		
		 }
	
	close(sdmotion);	

	
return 0;

}
