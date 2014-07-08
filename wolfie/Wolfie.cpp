#include "Wolfie.h"

using namespace std;

Wolfie::Wolfie(){}

Wolfie::~Wolfie(){}

Wolfie::Wolfie(const aed2::Conj<aed2::Cliente>& clientes)
{
	_cantidadDeClientes = clientes.Cardinal();
	_clientes = new DiccionarioClientes<infoCliente>(_cantidadDeClientes);
	
	infoCliente infoClienteInicial;
	infoClienteInicial.titulos = DiccionarioTitulos<infoTituloCliente>();
	infoClienteInicial.cantidadTotalDeAcciones = 0;
		
	aed2::Conj<aed2::Cliente>::const_Iterador itClientes = clientes.CrearIt();
	while (itClientes.HaySiguiente()) {
		_clientes->Definir(itClientes.Siguiente(), infoClienteInicial);
		itClientes.Avanzar();
	}
}

aed2::Nat Wolfie::CantidadDeClientes() const
{
	return _cantidadDeClientes;
}

aed2::Cliente Wolfie::IesimoCliente(aed2::Nat i) const
{
	return _clientes->Iesimo(i);
}
