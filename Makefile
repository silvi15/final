CC = gcc

LDLIBS= -lpthread -lrt

CFLAGS = -g -Wall

all: proxy

proxy: main.o hijo.o parsear.o http.o extension.o funcion.o crearTarea.o clientes.o padre.o
	$(CC) -Wall -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~


