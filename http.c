#include "proxy.h"

int http(int sdtc, char *dirraiz, char *extension){

	int N;
	int txt;
	char bufaux[512];
	bzero(bufaux,512);
	int leido;
         
	if((txt = open (dirraiz, O_RDWR , S_IRWXU))<0){
		perror("Error en open: ");
		write(STDOUT_FILENO,"Error al abrir ruta\n",20); 

		return -1;
	}
	
	N=extencion(sdtc,extension);  // escri el tipo de archivo que le voya pasar 
	write (sdtc, "\r\n" , 2);
		
		if(N>=0){
				while ((leido = read (txt, bufaux,512))>0) {
				write(sdtc,bufaux, sizeof (bufaux));
				bzero(bufaux,512);
				}
				return 0;                     
			}
	close(sdtc);
	close(txt);

	
return 0;
}