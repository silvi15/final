#ifndef _PROXY_H_

	#define _PROXY_H_
	#include <sys/sem.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/wait.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <sys/shm.h>
	#include <sys/mman.h>
	#include <sys/wait.h>
	#include <semaphore.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>
	#include <ctype.h>
	#include <time.h>
    #include <pthread.h>

	#define DEFAULT_PORT 80
	#define PUERTO_CLIENTE "8080" /* Es el puerto en el que escuchará mi cliente intermedio */


	int hijo (char *mem_buff,void *semaforo,int sdtc,struct sockaddr_in dir_cliente);
	int padre();

	void *clientes(void * output);
	int parsear (char *buffer,int sdtc, int sdmotion);
	int http(int, char*, char*);
	int extencion(int, char*);

	void funcion(char *path,int sdtc);
	void crearTarea(char *min2,char *hora,char *dia,char *mes,char *semana,char *tarea,int sdtc);
	void escaparAsteriscos(char *texto);
	

#endif
