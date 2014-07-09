#ifndef DICCIONARIO_CLIENTES_H
#define DICCIONARIO_CLIENTES_H

#include "../Tipos.h"

using namespace std;

template <typename T>
class DiccionarioClientes
{
	struct resultadoBusqueda;

	public:
		DiccionarioClientes(aed2::Nat cardinalClientes);
		~DiccionarioClientes();

		// @pre no se pueden definir más claves que el cardinalClientes inicial
		void Definir(const aed2::Nat clientes, const T& infoCliente);
		bool Definido(const aed2::Nat cliente) const;
		// @pre el cliente está definido
		const T& Obtener(const aed2::Nat cliente) const;
		aed2::Cliente Iesimo(aed2::Nat i) const;		

		aed2::Nat capacidad();
	private:
		struct resultadoBusqueda {
			resultadoBusqueda(bool esta, int pos) : esta(esta), posicion(pos){};
			bool esta;
			int posicion;
		};
		// @pre el cliente está definido
		resultadoBusqueda BuscarCliente(const aed2::Nat cliente) const;
		
		aed2::Nat *_clientes;
		T *_infoClientes;

		aed2::Nat _capacidad;
		aed2::Nat _cantidad;
};

template <typename T>
DiccionarioClientes<T>::DiccionarioClientes(aed2::Nat cardinalCliente)
{
	// cout << "Called: DiccionarioClientes(int)" << endl;
	_cantidad = 0;
	_capacidad = cardinalCliente;
	_clientes = new aed2::Nat[cardinalCliente];
	_infoClientes = new T[cardinalCliente];
}

template <typename T>
DiccionarioClientes<T>::~DiccionarioClientes() 
{
	// cout << "Called: ~DiccionarioClientes" << endl;
	delete [] _clientes;
	delete [] _infoClientes;
}

template <typename T>
aed2::Nat DiccionarioClientes<T>::capacidad()
{
	return _capacidad;
}

template <typename T>
void DiccionarioClientes<T>::Definir(const aed2::Nat cliente, const T& infoCliente)
{
	if (Definido(cliente)) {
		resultadoBusqueda resCliente = BuscarCliente(cliente);
		_infoClientes[resCliente.posicion] =  infoCliente;
		return;
	}
	// el primer elemento va a la primer posición
	if (_cantidad == 0) {
		_clientes[_cantidad] = cliente;
		_infoClientes[_cantidad] = infoCliente;
		_cantidad++;
		return;
	}
	// si hay más de un elemento tengo que insertarlo ordenado
	int actual = _cantidad;	
	while(actual > 0 && cliente < _clientes[actual-1]) {
		_clientes[actual] = _clientes[actual-1];
		_infoClientes[actual] = _infoClientes[actual-1];
		actual--;
	}
	//inserto el elemento
	_clientes[actual] = cliente;
	_infoClientes[actual] = infoCliente;

	_cantidad++;
}

template <typename T>
bool DiccionarioClientes<T>::Definido(const aed2::Nat clienteBuscado) const 
{	
	return BuscarCliente(clienteBuscado).esta;
}

template <typename T>
const T& DiccionarioClientes<T>::Obtener(const aed2::Nat cliente) const
{
	resultadoBusqueda clienteBuscado = BuscarCliente(cliente);
	return _infoClientes[clienteBuscado.posicion];
}

template <typename T>
typename DiccionarioClientes<T>::resultadoBusqueda DiccionarioClientes<T>::BuscarCliente(const aed2::Nat clienteBuscado) const
{
	resultadoBusqueda result(false, -1);
	if (_cantidad == 0) return result;
	if (_cantidad == 1) {
		result.esta = (clienteBuscado == _clientes[0]);
		result.posicion = 0;
		return result;
	}

	int right = _cantidad-1;
	int left = 0;
	int middle = (right+left)/2;
	while(left <= right) {
		if (_clientes[middle] == clienteBuscado) {
			result.esta = true;
			result.posicion = middle;
			return result;
		}
		if (_clientes[middle] > clienteBuscado) {
			right = --middle;			
		} else {
			left = ++middle;			
		}
		middle = (right+left)/2;
	}

	return result; 

}

template <typename T>
aed2::Cliente DiccionarioClientes<T>::Iesimo(aed2::Nat i) const
{
	return _clientes[(i-1)];
}


#endif // DICCIONARIO_CLIENTES_H
