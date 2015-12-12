CC = gcc

LDLIBS= -lpthread -lrt

CFLAGS = -g -Wall

all: proxy

proxy: abrirArchivo.o atenderHijo.o crearTarea.o escribirClientes.o leerArgumentos.o leerExtension.o main.o
	$(CC) -Wall -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~


