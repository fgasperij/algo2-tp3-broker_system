#include "Driver.h"

using namespace aed2;

Driver::Driver(const Conj<Cliente>& clientes)
{
	_wolfie = new Wolfie(clientes);
}

Driver::~Driver()
{	
	delete _wolfie;
}

void Driver::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
	_wolfie->AgregarTitulo(nombre, cotizacion, max_acciones);
}

void Driver::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
	_wolfie->ActualizarCotizacion(nombre, cotizacion)
}

void Driver::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	_wolfie->AgregarPromesaDeCompra(cliente, titulo, limite, cantidad);
}

void Driver::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
	_wolfie->AgregarPromesaDeVenta(cliente, titulo, limite, cantidad);
}

Nat Driver::CantidadDeClientes() const
{
	return _wolfie->CantidadDeClientes();	
}

Cliente Driver::IesimoCliente(Nat i) const
{
	return _wolfie->IesimoCliente(i);
}

Nat Driver::CantidadDeTitulos() const
{
	return _wolfie->CantidadDeTitulos();
}

NombreTitulo Driver::IesimoTitulo(Nat i) const
{
	return _wolfie->IesimoTitulo(i);
}

Nat Driver::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
	return _wolfie->MaxAccionesDe(nombre_titulo);
}

Dinero Driver::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
	return _wolfie->CotizacionDe(nombre_titulo);
}

bool Driver::EnAlza(const NombreTitulo& nombre_titulo) const
{
	return _wolfie->EnAlza(nombre_titulo);
}

Nat Driver::AccionesTotalesDe(const Cliente& cliente) const
{
	return _wolfie->AccionesTotalesDe(cliente);
}

Nat Driver::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
	return _wolfie->AccionesPorCliente(cliente, nombre_titulo);
}

Nat Driver::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
	return _wolfie->AccionesDisponibles(nombre_titulo);
}

bool Driver::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->PrometeComprar(cliente, titulo);
}

Nat Driver::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->CantidadAComprar(cliente, titulo);
}

Dinero Driver::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->ValorEsperadoParaComprar(cliente, titulo);
}

bool Driver::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->PrometeVender(cliente, titulo);
}

Nat Driver::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->CantidadAVender(cliente, titulo);
}

Dinero Driver::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) const
{
	return _wolfie->ValorEsperadoParaVender(cliente, titulo);
}
