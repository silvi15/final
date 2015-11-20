#include "proxy.h"

void funcionArgumentos(char * path,int sdtc){

	char *p;
	char *minutos,*hora,*dia,*mes,*semana,*tarea;  
	char *min2;

	p = strtok (path,"?");

	printf("\n");
	p = strtok (NULL, "Minutos="); //printf("\n1)p= minutos:%s\n",p);
	minutos=p;// printf("minutos: %s\n", minutos);
	
	p = strtok (NULL, "&Hora="); //printf("\n 2)p= hora : %s\n",p);
hora = p; printf("hora: %s\n",hora);

	p = strtok (NULL, "&dia="); //printf("\n 3)p= dia: %s\n",p);
dia = p; printf("dia: %s\n",dia); 

	p = strtok (NULL, "&Mes=");// printf("\n4)p= mes: %s\n",p);
mes=p; printf("mes:%s\n",mes);		

	p = strtok (NULL, "&semana="); //printf("\n 5) p=semana:%s\n",p);
semana=p; printf("semana:%s\n",semana);

	p = strtok (NULL, "tarea="); //printf("\n 5) p=semana:%s\n",p);
tarea=p; printf("tarea:%s\n",tarea);


min2 = strtok(minutos , "&H");
printf("minutos:%s\n",min2);

crearTarea(min2,hora,dia,mes,semana,tarea,sdtc);

}
