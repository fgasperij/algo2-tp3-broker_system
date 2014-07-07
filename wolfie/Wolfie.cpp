#include "Wolfie.h"

using namespace std;

Wolfie::Wolfie(const aed2::Conj<aed2::Cliente>& clientes)
{
	_cantidadDeClientes = clientes.Cardinal();
	aed2::Conj::Iterador 
}

int Wolfie::CantidadDeClientes()
{
	return _cantidadDeClientes;
}