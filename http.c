#include "proxy.h"

int abrirArchivo(int sdtc, char *dirraiz, char *extension){

	int N;
	int txt;
	char bufaux[512];
	bzero(bufaux,512);
	int leido;
	int escribir;
	int escribir2;
         
	if((txt = open (dirraiz, O_RDWR , S_IRWXU))<0){
		perror("Error en open: ");
		return -1;
	}

	
	N=funcionExtension(sdtc,extension);  // escri el tipo de archivo que le voya pasar 
	
	escribir=write (sdtc, "\r\n" , 2);

	if(escribir == -1){
		printf("error write abrirArchivo 1\n");
		return -1;
	}	
		if(N>=0){
				while ((leido = read (txt, bufaux,512))>0) {

						if(leido== -1){
							printf("error read abrirArchivo 1\n");
							return -1;
						}	

						escribir2=write(sdtc,bufaux, sizeof (bufaux));
						
						if(escribir2 == -1){
							printf("error escribir2 abrirArchivo\n");
							return -1;
						}

						bzero(bufaux,512);
				
				}
				return 0;                     
			}
	close(sdtc);
	close(txt);

	
return 0;
}