// g++ -g testsWolfie.cpp ../wolfie/Wolfie.cpp -o tw
// valgrind --leak-check=full ./tw

#include "../mini_test.h"
#include "../wolfie/Wolfie.h"
#include "../Tipos.h"

using namespace aed2;

void test_crear_wolfie_sin_perder_memoria() 
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	ASSERT_EQ(5, w.IesimoCliente(2));
	ASSERT_EQ(3, w.IesimoCliente(1));

	ASSERT_EQ(2, w.CantidadDeClientes());
}

void test_agregar_titulos()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	String nombre("Lola");
	w.AgregarTitulo(nombre, 12, 10);	
}

void test_cantidad_de_titulos()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	String nombre1("Lola1");
	String nombre2("Lola2");
	w.AgregarTitulo(nombre1, 12, 10);		
	w.AgregarTitulo(nombre2, 12, 10);		

	ASSERT_EQ(2, w.CantidadDeTitulos());

	String nombre3("Lola3");
	w.AgregarTitulo(nombre3, 12, 10);		

	ASSERT_EQ(3, w.CantidadDeTitulos());
}

void test_iesimo_titulo()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	String nombre1("Lola1");
	String nombre2("Lola2");
	String nombre3("Lola3");
	w.AgregarTitulo(nombre1, 12, 10);		
	w.AgregarTitulo(nombre2, 12, 10);		
	w.AgregarTitulo(nombre3, 12, 10);		

	ASSERT_EQ("Lola1", w.IesimoTitulo(1));
	ASSERT_EQ("Lola2", w.IesimoTitulo(2));
	ASSERT_EQ("Lola3", w.IesimoTitulo(3));
}

void test_max_acciones_de()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	String nombre1("Lola1");
	String nombre2("Lola2");
	String nombre3("Lola3");
	// nombre cot maxAcciones
	w.AgregarTitulo(nombre1, 12, 2);		
	w.AgregarTitulo(nombre2, 12, 14);		
	w.AgregarTitulo(nombre3, 12, 90);

	ASSERT_EQ(2, w.MaxAccionesDe(nombre1));
	ASSERT_EQ(14, w.MaxAccionesDe(nombre2));
	ASSERT_EQ(90, w.MaxAccionesDe(nombre3));
}

void test_cotizacion_de()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);

	Wolfie w(clientes);

	String nombre1("Lola1");
	String nombre2("Lola2");
	String nombre3("Lola3");
	// nombre cot maxAcciones
	w.AgregarTitulo(nombre1, 32, 2);		
	w.AgregarTitulo(nombre2, 145, 14);		
	w.AgregarTitulo(nombre3, 75, 90);

	ASSERT_EQ(32, w.CotizacionDe(nombre1));
	ASSERT_EQ(145, w.CotizacionDe(nombre2));
	ASSERT_EQ(75, w.CotizacionDe(nombre3));
}


int main() 
{
	RUN_TEST(test_crear_wolfie_sin_perder_memoria);
	RUN_TEST(test_agregar_titulos);
	RUN_TEST(test_cantidad_de_titulos);
	RUN_TEST(test_iesimo_titulo);
	RUN_TEST(test_max_acciones_de);
	RUN_TEST(test_cotizacion_de);

	return 0;
}
