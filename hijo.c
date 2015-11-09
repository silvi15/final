
#include "proxy.h"

int hijo (int sdtc, struct sockaddr_in dir_cliente){

	
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
    char output[128], cadena[128];
    
	pthread_t tid; //declaro la declaracion del hilo
	//printf ("hijo = %d\n", getpid());

	/* Obtengo la ip a la cual conectarme */
	if ((Host = gethostbyname ("localhost")) == NULL){
		perror("Error en gethostbyname()\n");
		return -1;
	}
		
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
	//printf("buffer del navegador \n%s",buffer);
	
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
//		pthread_exit(NULL);

			

	write(sdmotion, buffer, leido);
	parsear(buffer,sdmotion, sdtc);

	while ((leidomotion=read(sdmotion,buffermotion, sizeof buffermotion)) > 0){
		
			
		write(sdtc,buffermotion,leidomotion);
		
		 }
	close(sdmotion);	 
	int valor;

	sem_getvalue(&sem,&valor);

	printf("valor del sem antes del post :%d\n",valor );
	
	sem_post(&sem);

	int valor2;

	sem_getvalue(&sem,&valor2);
	
	printf("valor del sem despues del post :%d\n",valor2 );

		
	

return 0;

}
