#ifndef WOLFIE_H_
#define WOLFIE_H_

#include "../Tipos.h"
#include "../aed2/Conj.h"
#include "DiccionarioTitulos.h"
#include "DiccionarioClientes.h"

using namespace aed2;

class Wolfie 
{
	public:
		Wolfie();
		Wolfie(const Conj<Cliente>& clientes);
		~Wolfie();
		
		Nat CantidadDeClientes() const;
		// PRE: 0 <= i < CantidadDeClientes()
		Cliente IesimoCliente(Nat i) const;

		void AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones);
		
		// PRE: nombre \in Titulos()
		void ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion);

		Nat CantidadDeTitulos() const;
		// PRE: 0 <= i < CantidadDeTitulos()
		NombreTitulo IesimoTitulo(Nat i) const;
		
		// PRE: nombre_titulo \in Titulos()
		Nat MaxAccionesDe(const NombreTitulo& nombre_titulo) const;
		// PRE: nombre_titulo \in Titulos()
		Dinero CotizacionDe(const NombreTitulo& nombre_titulo) const;
		// PRE: nombre_titulo \in Titulos()
		bool EnAlza(const NombreTitulo& nombre_titulo) const;

		// PRE: c \in Clientes()
		Nat AccionesTotalesDe(const Cliente& cliente) const;

		// PRE: no PrometeComprar(cliente)
		void AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad);
		// PRE: c \in Clientes()
		bool PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const;
		// PRE: c \in Clientes(), PrometeComprar(c, titulo)
		Nat CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) const;
		// PRE: c \in Clientes(), PrometeComprar(c, titulo)
		Dinero ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) const;

		// PRE: no PrometeVender(cliente) y cantidad < AccionesPorCliente(cliente, titulo)
		void AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad);
		// PRE: c \in Clientes()
		bool PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const;
		// PRE: c \in Clientes(), PrometeVender(c, titulo)
		Nat CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) const;
		// PRE: c \in Clientes(), PrometeVender(c, titulo)
		Dinero ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) const;

		// PRE: nombre_titulo \in Titulos()
		Nat AccionesDisponibles(const NombreTitulo& nombre_titulo) const;
		
	private:
		struct clienteTotalAcciones {
			clienteTotalAcciones() : cliente(0), cantidadTotalDeAcciones(0) {};
			clienteTotalAcciones(Cliente c, Nat cantidad) : cliente(c), cantidadTotalDeAcciones(cantidad) {};
			Cliente cliente;
			Nat cantidadTotalDeAcciones;
		};
		struct promesa {
			promesa() : pendiente(false), umbral(0), cantidad(0) {};

			promesa(bool pendiente, Nat umbral, Nat cantidad) : pendiente(pendiente),
				umbral(umbral), cantidad(cantidad) {};

			bool pendiente;
			Nat umbral;
			Nat cantidad;
		};
		struct promesaCompraYVenta {
			promesaCompraYVenta () : compra(promesa()), venta(promesa()) {};
			promesa compra;
			promesa venta;
		};
		struct infoTituloCliente {
			infoTituloCliente () : cantidadDeAcciones(0), promesas(promesaCompraYVenta()) {};
			Nat cantidadDeAcciones;
			promesaCompraYVenta promesas;
		};
		struct infoCliente {
			infoCliente() : cantidadTotalDeAcciones(0), titulos(DiccionarioTitulos<infoTituloCliente>()) {};
			
			infoCliente(const infoCliente &other) {
				titulos = other.titulos;
				cantidadTotalDeAcciones = other.cantidadTotalDeAcciones;
			};

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

		void MergeSort(clienteTotalAcciones *A, Nat tamanioA);
		void Merge(clienteTotalAcciones *A, Nat tamanioA, 
			const clienteTotalAcciones *B, Nat tamanioB, 
			const clienteTotalAcciones *C, Nat tamanioC);
};

#endif // WOLFIE_H_
