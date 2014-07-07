#ifndef WOLFIE_H_
#define WOLFIE_H_

#include "../Tipos.h"
#include "../aed2/Conj.h"
#include "DiccionarioTitulos.h"
#include "DiccionarioClientes.h"

using namespace std;

class Wolfie 
{
	struct infoTituloCliente;
	struct infoCliente;

	public:
		Wolfie(const aed2::Conj<aed2::Cliente>& clientes);
		int CantidadDeClientes();
	private:
		struct promesa {
			bool pendiente;
			aed2::Nat umbral;
			aed2::Nat cantidad;
		};
		struct promesaCompraYVenta {
			promesa compra;
			promesa venta;
		};
		struct infoTituloCliente {
			aed2::Nat cantidadDeAcciones;
			promesaCompraYVenta promesas;
		};
		struct infoCliente {
			infoCliente() : cantidadTotalDeAcciones(0), titulos(DiccionarioTitulos<string, infoTituloCliente>()) {};
			
			DiccionarioTitulos<string, infoTituloCliente> titulos;
			aed2::Nat cantidadTotalDeAcciones;
		};
		
		int _cantidadDeClientes;
		DiccionarioClientes<infoCliente> *_clientes;
};

#endif // WOLFIE_H_
