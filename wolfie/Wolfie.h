#ifndef WOLFIE_H_
#define WOLFIE_H_

#include "../Tipos.h"
#include "../aed2/Conj.h"
#include "DiccionarioTitulos.h"
#include "DiccionarioClientes.h"

namespace aed2 {

class Wolfie 
{
	public:
		Wolfie(const Conj<Cliente>& clientes);
		int CantidadDeClientes();
	private:
		int cantidadClientes;
};

}

#endif // WOLFIE_H_