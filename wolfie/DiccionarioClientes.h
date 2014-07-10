#ifndef DICCIONARIO_CLIENTES_H
#define DICCIONARIO_CLIENTES_H

#include "../Tipos.h"

using namespace aed2;

template <typename T>
class DiccionarioClientes
{
	struct resultadoBusqueda;

	public:
		class const_Iterador;
		struct const_Elem;

		DiccionarioClientes(Nat cardinalClientes);
		~DiccionarioClientes();

		// @pre no se pueden definir más claves que el cardinalClientes inicial
		void Definir(const Nat clientes, const T& infoCliente);
		bool Definido(const Nat cliente) const;
		// @pre el cliente está definido
		const T& Obtener(const Nat cliente) const;
		Cliente Iesimo(Nat i) const;		

		Nat capacidad();

		const_Iterador CrearIt() const;

	class const_Iterador
	{
		public:
			const_Iterador();
			const_Iterador(const typename DiccionarioClientes<T>::const_Iterador& otro);
			const_Iterador& operator = (const typename DiccionarioClientes<T>::const_Iterador& otro);

			bool operator==(const typename DiccionarioClientes<T>::const_Iterador&) const;

			bool HaySiguiente() const;
			bool HayAnterior() const;
			const aed2::Nat SiguienteClave() const;
			const T& SiguienteSignificado() const;
			const aed2::Nat AnteriorClave() const;
			const T& AnteriorSignificado() const;
			const_Elem Siguiente() const;
			const_Elem Anterior() const;
			void Avanzar();
			void Retroceder();

		private:
			aed2::Nat *it_claves_;
			T *it_significados_;
			aed2::Nat posicion;
			aed2::Nat limite;

			const_Iterador(const DiccionarioClientes<T>* d);

			friend typename DiccionarioClientes<T>::const_Iterador DiccionarioClientes<T>::CrearIt() const;
	};

	struct const_Elem
	{
		const aed2::Nat clave;
		const T& significado;

		const_Elem(const aed2::Nat c, const T& s) : clave(c), significado(s) {}

		friend std::ostream& operator << (std::ostream& os, const DiccionarioClientes<T>::const_Elem& e) {
			return os << e.clave << ":" << e.significado;
		}		
	};

	private:
		struct resultadoBusqueda {
			resultadoBusqueda(bool esta, int pos) : esta(esta), posicion(pos){};
			bool esta;
			int posicion;
		};
		// @pre el cliente está definido
		resultadoBusqueda BuscarCliente(const Nat cliente) const;
		
		Nat *_clientes;
		T *_infoClientes;

		Nat _capacidad;
		Nat _cantidad;
};

template <typename T>
DiccionarioClientes<T>::DiccionarioClientes(Nat cardinalCliente)
{
	// cout << "Called: DiccionarioClientes(int)" << endl;
	_cantidad = 0;
	_capacidad = cardinalCliente;
	_clientes = new Nat[cardinalCliente];
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
Nat DiccionarioClientes<T>::capacidad()
{
	return _capacidad;
}

template <typename T>
void DiccionarioClientes<T>::Definir(const Nat cliente, const T& infoCliente)
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
bool DiccionarioClientes<T>::Definido(const Nat clienteBuscado) const 
{	
	return BuscarCliente(clienteBuscado).esta;
}

template <typename T>
const T& DiccionarioClientes<T>::Obtener(const Nat cliente) const
{
	resultadoBusqueda clienteBuscado = BuscarCliente(cliente);
	return _infoClientes[clienteBuscado.posicion];
}

template <typename T>
typename DiccionarioClientes<T>::resultadoBusqueda DiccionarioClientes<T>::BuscarCliente(const Nat clienteBuscado) const
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
Cliente DiccionarioClientes<T>::Iesimo(Nat i) const
{
	return _clientes[(i-1)];
}

// Crear Iteradores!
template <typename T>
typename DiccionarioClientes<T>::const_Iterador DiccionarioClientes<T>::CrearIt() const
{
  return const_Iterador(this);
}

/*---------------------------------------------------------------
 * Implementacion del Iterador Constante
 *---------------------------------------------------------------
 */
template<typename T>
DiccionarioClientes<T>::const_Iterador::const_Iterador()
{}

template<typename T>
DiccionarioClientes<T>::const_Iterador::const_Iterador(const typename DiccionarioClientes<T>::const_Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_), posicion(otro.posicion), limite(otro.limite)
{}

template<typename T>
typename DiccionarioClientes<T>::const_Iterador& DiccionarioClientes<T>::const_Iterador::operator=(const typename DiccionarioClientes<T>::const_Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;
  posicion = otro.posicion;
  limite = otro.limite;

  return *this;
}

template<typename T>
bool DiccionarioClientes<T>::const_Iterador::HaySiguiente() const
{
  return (posicion < limite);
}

template<typename T>
bool DiccionarioClientes<T>::const_Iterador::HayAnterior() const
{
  return (posicion > 0);
}

template<typename T>
const aed2::Nat DiccionarioClientes<T>::const_Iterador::SiguienteClave() const
{
  return it_claves_[posicion];
}

template<typename T>
const T& DiccionarioClientes<T>::const_Iterador::SiguienteSignificado() const
{
  return it_significados_[posicion];  
}

template<typename T>
typename DiccionarioClientes<T>::const_Elem DiccionarioClientes<T>::const_Iterador::Siguiente() const
{
  return const_Elem(SiguienteClave(), SiguienteSignificado());
}

template<typename T>
const aed2::Nat DiccionarioClientes<T>::const_Iterador::AnteriorClave() const
{
  return it_claves_[posicion-1];
}

template<typename T>
const T& DiccionarioClientes<T>::const_Iterador::AnteriorSignificado() const
{
  return it_significados_[posicion-1];
}

template<typename T>
typename DiccionarioClientes<T>::const_Elem DiccionarioClientes<T>::const_Iterador::Anterior() const
{
  return const_Elem(AnteriorClave(), AnteriorSignificado());
}

template<typename T>
void DiccionarioClientes<T>::const_Iterador::Avanzar()
{
	posicion++;
}

template<typename T>
void DiccionarioClientes<T>::const_Iterador::Retroceder()
{
	posicion--;
}

template<typename T>
DiccionarioClientes<T>::const_Iterador::const_Iterador(const DiccionarioClientes<T>* d)
  : it_claves_(d->_clientes), it_significados_(d->_infoClientes), posicion(0), limite(d->_capacidad)
{}

template<typename T>
bool DiccionarioClientes<T>::const_Iterador::operator == (const typename DiccionarioClientes<T>::const_Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_ && posicion == otro.posicion && limite == otro.limite;
}


#endif // DICCIONARIO_CLIENTES_H
