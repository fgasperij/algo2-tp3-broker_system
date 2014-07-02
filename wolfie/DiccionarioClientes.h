#ifndef DICCIONARIO_CLIENTES_H
#define DICCIONARIO_CLIENTES_H

#include "../Tipos.h"

template <typename T>
class DiccionarioClientes
{
	public:
		DiccionarioClientes(aed2::Nat cardinalClientes);
		~DiccionarioClientes();
		aed2::Nat capacidad();
	private:
		aed2::Nat *_clientes;
		aed2::Nat _capacidad;
};

template <typename T>
DiccionarioClientes<T>::DiccionarioClientes(aed2::Nat cardinalCliente)
{
	_capacidad = cardinalCliente;
	_clientes = new aed2::Nat[cardinalCliente];
}

template <typename T>
DiccionarioClientes<T>::~DiccionarioClientes() 
{
	delete _clientes;
}

template <typename T>
aed2::Nat DiccionarioClientes<T>::capacidad()
{
	return _capacidad;
}


#endif // DICCIONARIO_CLIENTES_H
