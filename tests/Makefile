CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

SOURCES = testsDiccTitulo.cpp
OBJS = $(SOURCES:.cpp=.o)

S_CLIENTES = testsDiccionarioClientes.cpp
OBJS_CLIENTES = $(S_CLIENTES:.cpp=.o)

LIBS =

TARGET_TIT =	testsDiccTitulo
TARGET_CLIE =	testsDiccionarioClientes

$(TARGET_TIT):	$(OBJS)
	$(CXX) -o $(TARGET_TIT) $(OBJS) $(LIBS)
	
$(TARGET_CLIE):	$(OBJS_CLIENTES)
	$(CXX) -o $(TARGET_CLIE) $(OBJS_CLIENTES) $(LIBS)
	
all:	$(TARGET_CLIE) $(TARGET_TIT)

clientes:	$(TARGET_CLIE)

titulos:	$(TARGET_TIT)

wolfie:	$(TARGET_WOLFIE)

clean:
	rm -f $(OBJS_CLIENTES) $(TARGET_CLIE)
	rm -f $(OBJS) $(TARGET_TIT)

.PHONY: run valgrind

run: all
	./$(TARGET_TIT)

valgrind_ti: all
	valgrind --leak-check=full ./$(TARGET_TIT)

valgrind_cl: all
	valgrind --leak-check=full ./$(TARGET_CLIE)

valgrind: all
	valgrind --leak-check=full ./$(TARGET_CLIE)
	valgrind --leak-check=full ./$(TARGET_TIT)
