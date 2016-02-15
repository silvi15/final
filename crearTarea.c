#include "proxy.h"

void escaparAsteriscos(char *texto){
	char textoNuevo[400] = "";
	int i = 0;
	int j = 0;
	printf("texto: %s\n",texto);
	//Recorre el texto copiando caracter por caracter a una nueva cadena, cuando hay un asteriscos, en la nueva cadena agrega una \ antes para escaparlo
	while(texto[i] != '\0'){
		if(texto[i] == '*'){
			textoNuevo[j] = '\\';
			j++;
			textoNuevo[j] = texto[i];
		} else {
			textoNuevo[j] = texto[i];
		}
		i++;
		j++;
	}
	//Cerramos el string nuevo
	textoNuevo[j] = '\0';
	//copia el resultado de la nueva cadena a la vieja (con los asteriscos escapados)
	strcpy(texto, textoNuevo);
}

void crearTarea(char *min2,char *hora,char *dia,char *mes,char *semana,char *tarea, int sdtc)
{
	int status;
	char comandoSistema[500] = ""; //Comando a ejecutar por el sistema, 500 caracteres como máximo
	char entradaCron[400] = ""; //Tarea que quedará escrita en el archivo de cron
	char entradaCronEscapada[400] = ""; //Tarea de cron con caracteres escapados para poder utilizar el comanod grep -v
	char *user="root";
	char* rutaAlEjecutable = RUTA_EJECUTABLE;
	
	strcat(entradaCron, min2);
	strcat(entradaCron, " ");
	strcat(entradaCron, hora);
	strcat(entradaCron, " ");
	strcat(entradaCron, dia);
	strcat(entradaCron, " ");
	strcat(entradaCron, mes);
	strcat(entradaCron, " ");
	strcat(entradaCron, semana);
	strcat(entradaCron, " ");
	strcat(entradaCron, user);
	strcat(entradaCron, " ");
	strcat(entradaCron, rutaAlEjecutable);

	strcpy(entradaCronEscapada, entradaCron);
	escaparAsteriscos(entradaCronEscapada);

	
	strcat(comandoSistema, "(crontab -l ; echo \"");
	strcat(comandoSistema, entradaCron);
	strcat(comandoSistema, "\") | crontab -");

	status = system(comandoSistema);

	if(status != 0){
		fprintf(stderr, "ERROR AL INTENTAR AGREGAR TAREA A CRON (%d)\n", status);
		return;
	}
	if(strcmp(tarea,"fo")==0){
		printf("crear una foto\n");
		int prueba;
		prueba=write(sdtc,"GET /0/action/snapshot HTTP/1.1\r\n\r\n",35); // crea la foto y la manda por el descriptor
		if(prueba == -1){
			perror("error en el write de crearTarea");
		}
		close(sdtc);		
}
	
printf("TAREA PROGRAMADA\n");
/*	
verificar la tarea creada:
/var/spool/cron/crontabs. 
*/
}
