// g++ -g tests.cpp -o tdc
// valgrind --leak-check=full ./tdc

#include "../mini_test.h"
#include "../wolfie/DiccionarioClientes.h"
#include "../Tipos.h"


void test_crear_diccionario_pocos_clientes() 
{
	DiccionarioClientes<aed2::Nat> dc(10);
	ASSERT_EQ(10, dc.capacidad());
}

int main() 
{
	RUN_TEST(test_crear_diccionario_pocos_clientes);
	
	return 0;
}
