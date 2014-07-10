# Compilador que será utilizado
CC=g++

# flags de compilación
# -O2 -g -Wall -fmessage-length=0
CFLAGS=-O2 -c -g -Wall -fmessage-length=0
# -c

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=aed2/ConjAcotado.cpp wolfie/Wolfie.cpp Driver.cpp test.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

valgrind: all
	valgrind --leak-check=full ./$(EXECUTABLE)