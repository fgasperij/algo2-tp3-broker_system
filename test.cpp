// g++ test.cpp wolfie/Wolfie.cpp Driver.cpp -o test
// valgrind --leak-check=full ./test

#include "Driver.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace aed2;

/** 
 * Imprime un elemento a un string, en vez de a una pantalla, 
 * a través del operador << 
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan 
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename T::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
  it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

  while( it1.HaySiguiente() )
  {
    bool esta = false;

    while( it2.HaySiguiente() ) {
      if ( it1.Siguiente() == it2.Siguiente() ) {
        esta = true;
				break;
      }
      it2.Avanzar();
    }

    if ( !esta ) {
			return false;
		}
		
		it1.Avanzar();
  }
  
  return true;
}

// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
void test_driver_y_wolfie_conectados()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);	
}

void test_wolfie_cantidadDeClientes()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);

	ASSERT_EQ(2, wolfie.CantidadDeClientes());	
}

void test_wolfie_iesimoCliente()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(73);
	clientes.Agregar(35);
	clientes.Agregar(25);

	Driver wolfie(clientes);

	ASSERT_EQ(1, wolfie.IesimoCliente(1));		
	ASSERT_EQ(5, wolfie.IesimoCliente(2));		
	ASSERT_EQ(25, wolfie.IesimoCliente(3));		
	ASSERT_EQ(35, wolfie.IesimoCliente(4));		
	ASSERT_EQ(73, wolfie.IesimoCliente(5));		
}

void test_wolfie_setup()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);	

	ASSERT(wolfie.CantidadDeClientes() == clientes.Cardinal());

	for(Nat i=0; i<wolfie.CantidadDeClientes(); i++) {
		ASSERT( clientes.Pertenece( wolfie.IesimoCliente(i) ) );
	}

	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);	
}

int main(int argc, char **argv)
{
	RUN_TEST(test_driver_y_wolfie_conectados);
	RUN_TEST(test_wolfie_cantidadDeClientes);
	RUN_TEST(test_wolfie_iesimoCliente);
	// RUN_TEST(test_wolfie_setup);
	
	return 0;
}
