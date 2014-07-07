#include "Wolfie.h"

using namespace std;

Wolfie::Wolfie(const aed2::Conj<aed2::Cliente>& clientes)
{
	_cantidadDeClientes = clientes.Cardinal();
	_clientes = new DiccionarioClientes<infoCliente>(_cantidadDeClientes);
	infoCliente infoClienteInicial();
		
	aed2::Conj::Iterador itClientes = clientes.CrearIt();	
	while (itClientes.HaySiguiente()) {
		_clientes->Definir(itClientes.Siguiente(), infoClienteInicial);
		itClientes.Avanzar();
	}
}

int Wolfie::CantidadDeClientes()
{
	return _cantidadDeClientes;
}
