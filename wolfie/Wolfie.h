#ifndef WOLFIE_H_
#define WOLFIE_H_

#include "../Tipos.h"
#include "../aed2/Conj.h"
#include "DiccionarioTitulos.h"
#include "DiccionarioClientes.h"

using namespace aed2;

class Wolfie 
{
	// struct infoTituloCliente;
	// struct infoCliente;
	// struct infoTitulo;

	public:
		Wolfie();
		Wolfie(const Conj<Cliente>& clientes);
		~Wolfie();
		Nat CantidadDeClientes() const;
		Cliente IesimoCliente(Nat i) const;

		void AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones);
		Nat CantidadDeTitulos() const;
		// PRE: 0 <= i < CantidadDeTitulos()
		NombreTitulo IesimoTitulo(Nat i) const;
		
	private:
		struct promesa {
			bool pendiente;
			Nat umbral;
			Nat cantidad;
		};
		struct promesaCompraYVenta {
			promesa compra;
			promesa venta;
		};
		struct infoTituloCliente {
			Nat cantidadDeAcciones;
			promesaCompraYVenta promesas;
		};
		struct infoCliente {
			infoCliente() : cantidadTotalDeAcciones(0), titulos(DiccionarioTitulos<infoTituloCliente>()) {};
			
			DiccionarioTitulos<infoTituloCliente> titulos;
			Nat cantidadTotalDeAcciones;
		};
		struct infoTitulo {
			infoTitulo() : cantidadMaximaDeAcciones(0), cantidadDeAccionesDisponibles(0),
				cotizacion(0), enAlza(true) {};

			infoTitulo(Nat maxAcciones, Nat cotizacion) : cantidadMaximaDeAcciones(maxAcciones), 
				cotizacion(cotizacion), cantidadDeAccionesDisponibles(maxAcciones), enAlza(true) {};

			Nat cantidadMaximaDeAcciones;
			Nat cantidadDeAccionesDisponibles;
			Nat cotizacion;
			bool enAlza;
		};
		
		Nat _cantidadDeClientes;
		DiccionarioClientes<infoCliente> *_clientes;
		DiccionarioTitulos<infoTitulo> *_titulos;
};

#endif // WOLFIE_H_
