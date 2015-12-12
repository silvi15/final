#include "proxy.h"

int leerExtension(int sdtc , char* extension){

	if((strncmp("html",extension,4))==0 ){
		
		write (sdtc, "HTTP/1.1 200 OK\r\n" , 17);
		write(sdtc,"Content-Type: text/html; charset=UTF-8\r\n", 39);
		return 0;      
	}

	else{
		perror("error en la funcion \n\n\n");
		write(sdtc,"HTTP/1.1 404 Not Found\r\n", 24);

		return -1;
	}

}

