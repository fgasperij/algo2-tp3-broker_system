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

void test_max_acciones_de_cotizacion_en_alza()
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
	w.AgregarTitulo(nombre3, 175, 90);

	ASSERT_EQ(2, w.MaxAccionesDe(nombre1));
	ASSERT_EQ(14, w.MaxAccionesDe(nombre2));
	ASSERT_EQ(90, w.MaxAccionesDe(nombre3));

	ASSERT_EQ(32, w.CotizacionDe(nombre1));
	ASSERT_EQ(145, w.CotizacionDe(nombre2));
	ASSERT_EQ(175, w.CotizacionDe(nombre3));

	ASSERT_EQ(true, w.EnAlza(nombre1));
	ASSERT_EQ(true, w.EnAlza(nombre2));
	ASSERT_EQ(true, w.EnAlza(nombre3));
}

void test_agregar_promesa_de_compra()
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
	w.AgregarTitulo(nombre3, 175, 90);

	w.AgregarPromesaDeCompra(3, nombre1, 10, 20);
	ASSERT_EQ(true, w.PrometeComprar(3, nombre1));
	ASSERT_EQ(false, w.PrometeComprar(3, nombre2));
	ASSERT_EQ(false, w.PrometeComprar(5, nombre1));
	ASSERT_EQ(false, w.PrometeComprar(5, nombre2));

	w.AgregarPromesaDeCompra(5, nombre3, 10, 20);
	ASSERT_EQ(true, w.PrometeComprar(5, nombre3));
	ASSERT_EQ(false, w.PrometeComprar(5, nombre2));
	ASSERT_EQ(false, w.PrometeComprar(5, nombre1));
}

void test_agregar_promesa_de_venta()
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
	w.AgregarTitulo(nombre3, 175, 90);

	w.AgregarPromesaDeVenta(3, nombre1, 10, 20);
	ASSERT_EQ(true, w.PrometeVender(3, nombre1));
	ASSERT_EQ(false, w.PrometeVender(3, nombre2));
	ASSERT_EQ(false, w.PrometeVender(5, nombre1));
	ASSERT_EQ(false, w.PrometeVender(5, nombre2));

	w.AgregarPromesaDeVenta(5, nombre3, 10, 20);
	ASSERT_EQ(true, w.PrometeVender(5, nombre3));
	ASSERT_EQ(false, w.PrometeVender(5, nombre2));
	ASSERT_EQ(false, w.PrometeVender(5, nombre1));
}

void test_cantidad_y_valor_esperado()
{
	Conj<Cliente> clientes;
	clientes.Agregar(3);
	clientes.Agregar(5);
	clientes.Agregar(9);

	Wolfie w(clientes);

	String nombre1("YPF");
	String nombre2("93hkj97}}++");
	String nombre3("kjhkj383737{'¿");
	// nombre cot maxAcciones
	w.AgregarTitulo(nombre1, 32, 2);		
	w.AgregarTitulo(nombre2, 145, 14);		
	w.AgregarTitulo(nombre3, 175, 90);

	// cliente titulo umbral cantidad
	w.AgregarPromesaDeVenta(3, nombre1, 10, 20);
	ASSERT_EQ(10, w.ValorEsperadoParaVender(3, nombre1));
	ASSERT_EQ(20, w.CantidadAVender(3, nombre1));

	w.AgregarPromesaDeVenta(5, nombre3, 34, 45);
	ASSERT_EQ(34, w.ValorEsperadoParaVender(5, nombre3));
	ASSERT_EQ(45, w.CantidadAVender(5, nombre3));
}

void test_actualizar_cotizacion()
{
	Conj<Cliente> clientes;
	Nat cliente1 = 3;
	Nat cliente2 = 5;
	Nat cliente3 = 9;
	clientes.Agregar(cliente1);
	clientes.Agregar(cliente2);
	clientes.Agregar(cliente3);

	Wolfie w(clientes);

	String nombre1("a");
	String nombre3("b");
	String nombre2("c");
	// nombre cot maxAcciones
	w.AgregarTitulo(nombre1, 10, 100);		
	w.AgregarTitulo(nombre2, 20, 100);		
	w.AgregarTitulo(nombre3, 30, 100);

	// cliente titulo umbral cantidad
	ASSERT_EQ(false, w.PrometeComprar(cliente1, nombre1));
	w.AgregarPromesaDeCompra(cliente1, nombre1, 20, 5);	
	
	ASSERT_EQ(true, w.PrometeComprar(cliente1, nombre1));
	w.ActualizarCotizacion(nombre1, 30);
	ASSERT_EQ(w.PrometeComprar(cliente1, nombre1), false);

	ASSERT_EQ(5, w.AccionesTotalesDe(cliente1));
	ASSERT_EQ(95, w.AccionesDisponibles(nombre1));
	ASSERT_EQ(5, w.AccionesPorCliente(cliente1, nombre1));
}

int main() 
{
	RUN_TEST(test_crear_wolfie_sin_perder_memoria);
	RUN_TEST(test_agregar_titulos);
	RUN_TEST(test_cantidad_de_titulos);
	RUN_TEST(test_iesimo_titulo);
	RUN_TEST(test_max_acciones_de_cotizacion_en_alza);
	RUN_TEST(test_agregar_promesa_de_compra);
	RUN_TEST(test_agregar_promesa_de_venta);
	RUN_TEST(test_cantidad_y_valor_esperado);
	RUN_TEST(test_actualizar_cotizacion);

	return 0;
}
