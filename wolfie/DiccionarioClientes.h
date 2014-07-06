#ifndef DICCIONARIO_CLIENTES_H
#define DICCIONARIO_CLIENTES_H

#include "../Tipos.h"

template <typename T>
class DiccionarioClientes
{
	public:
		DiccionarioClientes(aed2::Nat cardinalClientes);
		~DiccionarioClientes();

		// @pre no se pueden definir más claves que el cardinalClientes inicial
		void Definir(const aed2::Nat clave, const T& significado);
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
	delete _significados;
}

template <typename T>
aed2::Nat DiccionarioClientes<T>::capacidad()
{
	return _capacidad;
}

template <typename T>
void DiccionarioClientes<T>::Definir(const aed2::Nat clave, const T& significado)
{
	// el primer elemento va a la primer posición
	if (_cantidad == 0) {
		_clientes[_cantidad] = clave;
		_significados[_cantidad] = significado;
		_cantidad++;
		return;
	}
	// TODO: chequear que no me estoy yendo más allá de la capacidad de clientes inicial
	// si hay más de un elemento tengo que insertarlo ordenado
	int actual = _cantidad;	
	while(actual > 0 && clave < _clientes[actual-1]) {
		_clientes[actual] = _clientes[actual-1];
		_significados[actual] = _significados[actual-1];
		actual--;
	}
	//inserto el elemento
	_clientes[actual] = clave;
	_significados[actual] = clave;

	_cantidad++;
}

#endif // DICCIONARIO_CLIENTES_H
