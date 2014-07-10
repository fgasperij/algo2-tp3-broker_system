// g++ -g testsDiccionarioClientes.cpp -o tdc
// valgrind --leak-check=full ./tdc

#include "../mini_test.h"
#include "../wolfie/DiccionarioClientes.h"
#include "../Tipos.h"

using namespace std;

void test_crear_diccionario_pocos_clientes() 
{
	DiccionarioClientes<aed2::Nat> dc(10);
	ASSERT_EQ(10, dc.capacidad());
}

void test_definir_un_cliente() 
{
	DiccionarioClientes<string> dc(10);
	string nombre = "Lolita";
	ASSERT_EQ(false, dc.Definido(31));
	dc.Definir(31, nombre);
	ASSERT_EQ(true, dc.Definido(31));
}

void test_definir_dos_clientes() 
{
	DiccionarioClientes<string> dc(10);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	dc.Definir(32, nombre);
	ASSERT_EQ(true, dc.Definido(31));
	ASSERT_EQ(true, dc.Definido(32));
	ASSERT_EQ(false, dc.Definido(33));
}

void test_definir_todos_los_clientes() 
{
	DiccionarioClientes<string> dc(5);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	dc.Definir(32, nombre);
	dc.Definir(67, nombre);
	dc.Definir(9, nombre);
	dc.Definir(125, nombre);
	ASSERT_EQ(true, dc.Definido(31));
	ASSERT_EQ(true, dc.Definido(32));
	ASSERT_EQ(false, dc.Definido(33));
	ASSERT_EQ(true, dc.Definido(125));
	ASSERT_EQ(false, dc.Definido(76));
	ASSERT_EQ(false, dc.Definido(90));
	ASSERT_EQ(true, dc.Definido(67));
}

void test_definir_dos_veces_la_misma_clave()
{
	DiccionarioClientes<string> dc(5);
	string nombre1 = "Lolita1";
	string nombre2 = "Lolita2";
	string nombre3 = "Lolita3";
	dc.Definir(31, nombre1);
	dc.Definir(32, nombre2);
	dc.Definir(67, nombre3);
	string nombre4 = "REDEFINIDO";
	dc.Definir(67, nombre4);
	ASSERT_EQ(dc.Obtener(67), "REDEFINIDO");
}

void test_obtener_un_cliente()
{
	DiccionarioClientes<string> dc(5);
	string nombre = "Lolita";
	dc.Definir(31, nombre);
	ASSERT_EQ("Lolita", dc.Obtener(31));
}

void test_obtener_entre_varios_clientes()
{
	DiccionarioClientes<string> dc(5);
	string nombre1 = "Lolita1";
	string nombre2 = "Lolita2";
	string nombre3 = "Lolita3";
	string nombre4 = "Lolita4";
	string nombre5 = "Lolita5";
	dc.Definir(31, nombre1);
	dc.Definir(321, nombre2);
	dc.Definir(1, nombre3);
	dc.Definir(41, nombre4);
	dc.Definir(19, nombre5);
	ASSERT_EQ("Lolita1", dc.Obtener(31));
	ASSERT_EQ("Lolita2", dc.Obtener(321));
	ASSERT_EQ("Lolita3", dc.Obtener(1));
	ASSERT_EQ("Lolita4", dc.Obtener(41));
	ASSERT_EQ("Lolita5", dc.Obtener(19));
}

void test_usar_operador_new()
{
	DiccionarioClientes<string> *dc = new DiccionarioClientes<string>(5);
	string nombre = "Lola";
	dc->Definir(1, nombre);
	ASSERT_EQ(true, dc->Definido(1));
	delete dc;
}

void test_iterador()
{
	DiccionarioClientes<string> dc(3);
	
	string significados[3];
	significados[0] = "Pipita";
	significados[1] = "Rojo";
	significados[2]= "Messi";
	
	dc.Definir(11, significados[0]);
	dc.Definir(22, significados[1]);
	dc.Definir(33, significados[2]);

	DiccionarioClientes<string>::const_Iterador it = dc.CrearIt();
	
	ASSERT_EQ(true, it.HaySiguiente());
	ASSERT_EQ(11, it.SiguienteClave());
	ASSERT_EQ(significados[0], it.SiguienteSignificado());
	it.Avanzar();

	ASSERT_EQ(true, it.HaySiguiente());
	ASSERT_EQ(22, it.SiguienteClave());
	ASSERT_EQ(significados[1], it.SiguienteSignificado());
	it.Avanzar();

	ASSERT_EQ(true, it.HaySiguiente());
	ASSERT_EQ(33, it.SiguienteClave());
	ASSERT_EQ(significados[2], it.SiguienteSignificado());	
	it.Avanzar();

	ASSERT_EQ(false, it.HaySiguiente());	
}

int main() 
{
	RUN_TEST(test_crear_diccionario_pocos_clientes);
	RUN_TEST(test_definir_un_cliente);
	RUN_TEST(test_definir_dos_clientes);
	RUN_TEST(test_definir_todos_los_clientes);
	RUN_TEST(test_definir_dos_veces_la_misma_clave);
	RUN_TEST(test_obtener_un_cliente);
	RUN_TEST(test_obtener_entre_varios_clientes);
	RUN_TEST(test_usar_operador_new);
	RUN_TEST(test_iterador);	
	return 0;
}
