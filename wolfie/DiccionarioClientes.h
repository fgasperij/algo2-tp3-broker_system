#ifndef DICCIONARIO_CLIENTES_H
#define DICCIONARIO_CLIENTES_H

#include "../Tipos.h"

template <typename T>
class DiccionarioClientes
{
	public:
		DiccionarioClientes(aed2::Nat cardinalClientes);
		~DiccionarioClientes();

		Definir(const aed2::Nat clave, const T& significado);
		aed2::Nat capacidad();
	private:
		aed2::Nat *_clientes;
		T *_significados;

		aed2::Nat _capacidad;
		aed2::Nat _cantidad;
};

template <typename T>
DiccionarioClientes<T>::DiccionarioClientes(aed2::Nat cardinalCliente)
{
	_cantidad = 0;
	_capacidad = cardinalCliente;
	_clientes = new aed2::Nat[cardinalCliente];
	_significados = new T[cardinalCliente];
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

template <typename T>
void DiccionarioClientes<T>::Definir(const aed2::Nat clave, const T& significado)
{
	if (_cantidad == 0) {
		_clientes[_cantidad] = 
		_cantidad++;
	}

	int actual = _cantidad;
	while(actual > 0 && clave < _clientes[actual]) {

	}
	_cantidad++;
}

#endif // DICCIONARIO_CLIENTES_H
