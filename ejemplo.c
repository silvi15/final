#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    	char *protocolo; //localhost
	char *puerto; //5000    
	char *archivo; //index.html
    	char *extension;
   } URL;


void parse_url(char *url, URL *ret) {
    char *tmp = (char *) strdup(url);
    int len = 0;

    ret->protocolo = (char *) strtok(tmp, ":");
    len = strlen(ret->protocolo);

    ret->puerto = (char *) strtok(NULL, "/");
    len += strlen(ret->puerto);

    ret->archivo = (char *) strtok(NULL, ".");
    len += strlen(ret->archivo);

    ret->extension = (char *) strtok(NULL, " ");
    len += strlen(ret->extension);

}

void free_url(URL *url) {
   
    free(url->protocolo);
}

int main(int argc, char** argv) {
    URL url;
    parse_url("localhost:5000/index.html", &url);
	//
	//http://example.com:3000/Teste/asdf#coisa 
   printf("protocolo: %s\n puerto: %s\n archivo: %s\n extension: %s\n", url.protocolo, url.puerto, url.archivo, url.extension);
    free_url(&url);

    return (EXIT_SUCCESS);
}
