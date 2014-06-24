#include "Wolfie.h"

using namespace aed2;

Wolfie::Wolfie(const Conj<Cliente>& clientes)
{
	cantidadClientes = clientes.Cardinal();
}

int Wolfie::CantidadDeClientes()
{
	return cantidadClientes;
}