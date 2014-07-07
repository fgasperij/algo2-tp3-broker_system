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
		Wolfie(const Conj<Cliente>& clientes);
		int CantidadDeClientes();
	private:
		struct infoTituloCliente {
			aed2::Nat cantidadDeAcciones;
			promesas 
		};

		struct infoCliente {
			DiccionarioTitulos<string, infoTituloCliente> titulos;
			aed2::Nat cantidadTotalDeAcciones;
		};
		int _cantidadDeClientes;
		DiccionarioClientes<infoCliente> _clientes;
};

#endif // WOLFIE_H_