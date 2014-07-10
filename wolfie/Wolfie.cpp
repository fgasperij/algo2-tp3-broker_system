#include "Wolfie.h"

using namespace aed2;

Wolfie::Wolfie(){}

Wolfie::~Wolfie()
{
	delete _clientes;
	delete _titulos;
}

Wolfie::Wolfie(const Conj<Cliente>& clientes)
{
	_cantidadDeClientes = clientes.Cardinal();
	_clientes = new DiccionarioClientes<infoCliente>(_cantidadDeClientes);	
	Conj<Cliente>::const_Iterador itClientes = clientes.CrearIt();
	while (itClientes.HaySiguiente()) {
		_clientes->Definir(itClientes.Siguiente(), infoCliente());
		itClientes.Avanzar();
	}

	_titulos = new DiccionarioTitulos<infoTitulo>();
}

Nat Wolfie::CantidadDeClientes() const
{
	return _cantidadDeClientes;
}

Cliente Wolfie::IesimoCliente(Nat i) const
{
	return _clientes->Iesimo(i);
}

void Wolfie::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	infoTitulo titulo(max_acciones, cotizacion);
	_titulos->definir(nombre, titulo);
}

Nat Wolfie::CantidadDeTitulos() const
{
	int cantidadDeTitulos = 0;
	DiccionarioTitulos<infoTitulo>::const_Iterador itTitulos = _titulos->CrearIt();

	while(itTitulos.HaySiguiente()) {
		cantidadDeTitulos++;
		itTitulos.Avanzar();
	}

	return cantidadDeTitulos;
}

// PRE: 0 <= i < CantidadDeTitulos()
NombreTitulo Wolfie::IesimoTitulo(Nat i) const
{
	Nat iesimo = 1;
	String nombreIesimo;
	DiccionarioTitulos<infoTitulo>::const_Iterador itTitulos = _titulos->CrearIt();

	while(itTitulos.HaySiguiente()) {
		if (iesimo == i) return itTitulos.SiguienteClave();
		iesimo++;
		itTitulos.Avanzar();
	}
}

Nat Wolfie::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).cantidadMaximaDeAcciones;
}

Dinero Wolfie::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).cotizacion;	
}

bool Wolfie::EnAlza(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).enAlza;		
}

// PRE: no PrometeComprar(cliente)
void Wolfie::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	infoCliente infoClienteActual(_clientes->Obtener(cliente));	

	if (infoClienteActual.titulos.definido(titulo)) {
		infoTituloCliente infoTituloClienteActual(infoClienteActual.titulos.obtener(titulo));
		infoTituloClienteActual.promesas.compra = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	} else {
		infoTituloCliente infoTituloClienteActual;
		infoTituloClienteActual.promesas.compra = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	}
}

bool Wolfie::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	
	if (!infoClienteActual.titulos.definido(titulo)) return false;
	
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.compra.pendiente;
}

// PRE: c \in Clientes(), PrometeComprar(c, titulo)
Nat Wolfie::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.compra.cantidad;
}

// PRE: c \in Clientes(), PrometeComprar(c, titulo)
Dinero Wolfie::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.compra.umbral;
}

// PRE: no PrometeVender(cliente) y cantidad < AccionesPorCliente(cliente, titulo)
void Wolfie::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	infoCliente infoClienteActual(_clientes->Obtener(cliente));	

	if (infoClienteActual.titulos.definido(titulo)) {
		infoTituloCliente infoTituloClienteActual(infoClienteActual.titulos.obtener(titulo));
		infoTituloClienteActual.promesas.venta = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	} else {
		infoTituloCliente infoTituloClienteActual;
		infoTituloClienteActual.promesas.venta = promesa(true, limite, cantidad);
		
		infoClienteActual.titulos.definir(titulo, infoTituloClienteActual);
		_clientes->Definir(cliente, infoClienteActual);
	}	
}

bool Wolfie::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	
	if (!infoClienteActual.titulos.definido(titulo)) return false;
	
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.venta.pendiente;
}

// PRE: c \in Clientes(), PrometeVender(c, titulo)
Nat Wolfie::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.venta.cantidad;
}
// PRE: c \in Clientes(), PrometeVender(c, titulo)
Dinero Wolfie::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);
	infoTituloCliente infoTituloClienteActual = infoClienteActual.titulos.obtener(titulo);

	return infoTituloClienteActual.promesas.venta.umbral;
}

// PRE: c \in Clientes()
Nat Wolfie::AccionesTotalesDe(const Cliente& cliente) const
{
	infoCliente infoClienteActual = _clientes->Obtener(cliente);

	return infoClienteActual.cantidadTotalDeAcciones;
}

void Wolfie::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
	infoTitulo tituloActual = _titulos->obtener(nombre);
	if (tituloActual.cotizacion > cotizacion) {
		tituloActual.enAlza = false;
	} else {
		tituloActual.enAlza = true;
	}
	tituloActual.cotizacion = cotizacion;

	// // PROMESAS DE VENTA
	DiccionarioClientes<infoCliente>::const_Iterador itClientes = _clientes->CrearIt();
	while (itClientes.HaySiguiente()) {
		infoCliente clienteActual = itClientes.SiguienteSignificado();
		if (clienteActual.titulos.definido(nombre)) {
			infoTituloCliente infoTituloActual = clienteActual.titulos.obtener(nombre);
			// ejecutar venta
			if (infoTituloActual.promesas.venta.pendiente && 
				infoTituloActual.promesas.venta.umbral > cotizacion) {
				// marco la promesa como cumplida
				infoTituloActual.promesas.venta.pendiente = false;				
				
				int cantidadDeAccionesVendidas = infoTituloActual.promesas.venta.cantidad;
				// resto las promesas vendidas del título
				infoTituloActual.cantidadDeAcciones -= cantidadDeAccionesVendidas;
				// resto las promesas vendidas del total de acciones del cliente
				clienteActual.cantidadTotalDeAcciones -= cantidadDeAccionesVendidas;
				// sumo las promesas vendidas a la cantidad de acciones disponibles del título
				tituloActual.cantidadDeAccionesDisponibles += cantidadDeAccionesVendidas;

				clienteActual.titulos.definir(nombre, infoTituloActual);
				_clientes->Definir(itClientes.SiguienteClave(), clienteActual);
			}
		}
		itClientes.Avanzar();
	}

	// ARREGLO DE CLIENTE ORDENADO POR TOTAL ACCIONES
	DiccionarioClientes<infoCliente>::const_Iterador itClientes2 = _clientes->CrearIt();
	clienteTotalAcciones *clientesOrdenadosPorTotalDeAcciones = new clienteTotalAcciones[CantidadDeClientes()];
	int i = 0;
	while (itClientes2.HaySiguiente()) {
		infoCliente clienteActual = itClientes2.SiguienteSignificado();
		clientesOrdenadosPorTotalDeAcciones[i] = clienteTotalAcciones(itClientes2.SiguienteClave(), clienteActual.cantidadTotalDeAcciones);		
		itClientes2.Avanzar();
		i++;
	}
	MergeSort(clientesOrdenadosPorTotalDeAcciones, CantidadDeClientes());

	// PROMESAS DE COMPRA
	for(unsigned i = 0; i < CantidadDeClientes(); ++i) {
		infoCliente clienteActual = _clientes->Obtener(clientesOrdenadosPorTotalDeAcciones[i].cliente);
		if (clienteActual.titulos.definido(nombre)) {
			infoTituloCliente infoTituloActual = clienteActual.titulos.obtener(nombre);
			// ejecutar compra
			if (infoTituloActual.promesas.compra.pendiente && 
				infoTituloActual.promesas.compra.umbral < cotizacion &&
				infoTituloActual.promesas.compra.cantidad <= tituloActual.cantidadDeAccionesDisponibles) {
				// marco la promesa como cumplida
				infoTituloActual.promesas.compra.pendiente = false;				
				
				int cantidadDeAccionesCompradas = infoTituloActual.promesas.compra.cantidad;
				// resto las promesas compradas del título
				infoTituloActual.cantidadDeAcciones += cantidadDeAccionesCompradas;
				// resto las promesas compradas del total de acciones del cliente
				clienteActual.cantidadTotalDeAcciones += cantidadDeAccionesCompradas;
				// resto las promesas compradas a la cantidad de acciones disponibles del título
				tituloActual.cantidadDeAccionesDisponibles -= cantidadDeAccionesCompradas;

				clienteActual.titulos.definir(nombre, infoTituloActual);
				_clientes->Definir(clientesOrdenadosPorTotalDeAcciones[i].cliente, clienteActual);
			}
		}
	}

	_titulos->definir(nombre, tituloActual);

	delete [] clientesOrdenadosPorTotalDeAcciones;
}

void Wolfie::MergeSort(clienteTotalAcciones *A, Nat tamanioA)
{
	if (tamanioA > 1) {
		Nat m = tamanioA/2;
		
		clienteTotalAcciones *B = new clienteTotalAcciones[m];
		for(unsigned i = 0; i < m; ++i) {
			B[i] = A[i];
		}
		clienteTotalAcciones *C = new clienteTotalAcciones[tamanioA-m];
		for(unsigned i = m; i < tamanioA; ++i) {
			C[i-m] = A[i];
		}

		MergeSort(B, m);
		MergeSort(C, tamanioA-m);

		Merge(A, tamanioA, B, m, C, tamanioA-m);

		delete [] B;
		delete [] C;
	} 
}

void Wolfie::Merge(clienteTotalAcciones *A, Nat tamanioA, 
	const clienteTotalAcciones *B, Nat tamanioB, 
	const clienteTotalAcciones *C, Nat tamanioC)
{
	Nat iB = 0;
	Nat iC = 0;

	for(unsigned i = 0; i < tamanioA; ++i) {
		if (iB < tamanioB && (iC >= tamanioC || 
			B[iB].cantidadTotalDeAcciones < C[iC].cantidadTotalDeAcciones)) {
			A[i] = B[iB];
			iB++;
		} else {
			A[i] = C[iC];
			iC++;
		}
	}
}

// PRE: nombre_titulo \in Titulos()
Nat Wolfie::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
	return _titulos->obtener(nombre_titulo).cantidadDeAccionesDisponibles;
}

// PRE: c \in Clientes(), nombre_titulo \in Titulos()
Nat Wolfie::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
	infoCliente clienteActual = _clientes->Obtener(cliente);
	if (clienteActual.titulos.definido(nombre_titulo)) 
		return clienteActual.titulos.obtener(nombre_titulo).cantidadDeAcciones;

	return 0;
}