/*
 * Trabajo Práctico 3
 * 		Wolfie - Broker System
 * -----------------------------------------------------
 * Grupo :    20
 *
 * Modulo:    Diccionario Titulos sobre Trie
 * Autor:     LeaT
 * Estado:    Funcionabilidad Basica + Iterador --> OK
 *							Hay que testear mas
 *	
 * Ultima modificacion: 9/7/2014 - 12:24 am
 *
 * Revision:  
 *
 * ----------------------------------------------------- 
 */

#ifndef DICCTITULOS_H_
#define DICCTITULOS_H_

#include <ostream>
#include <string>
#include "../aed2/Lista.h"
#define LETRAS 256

using namespace aed2;

template <typename T>
class DiccionarioTitulos
{
  public:

	//para iterar las tuplas
	struct const_Elem;

  //Forward Declaration del iterador constante
  class const_Iterador;

  /// Crea un Diccionario Trie. (Operación Vacia())
  DiccionarioTitulos();

  /// Crea por copia un Diccionario Trie (operación Copiar())
  DiccionarioTitulos(const DiccionarioTitulos& otra);

  /// Destruye el Diccionario Trie, incluyendo los T alojados
  ~DiccionarioTitulos();
  
  /// Operacion de asignacion
  DiccionarioTitulos<T>& operator=(const DiccionarioTitulos<T>& otra);

  /// Operaciones básicas
  void definir(const String &clave, const T& significado);
  bool definido(const String &clave);
  void borrar(const String &clave);
  const T& obtener(const String &clave);
  
  // DEBUG - Obtener Claves
  // Implementada con propositos de debuggear. Obsoleta
  void claves();
  
  //Display
  // TODO
  std::ostream& mostrar(std::ostream&) const;
  

  /// Creación del const_Iterador
  const_Iterador CrearIt() const;
  const_Iterador CrearItUlt() const;

	class const_Iterador
	{
      public:

        const_Iterador();
        //const_Iterador(const typename DiccionarioTitulos<T>::Iterador& otro);
        const_Iterador(const typename DiccionarioTitulos<T>::const_Iterador& otro);
        const_Iterador& operator = (const typename DiccionarioTitulos<T>::const_Iterador& otro);

        bool operator==(const typename DiccionarioTitulos<T>::const_Iterador&) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;
        const aed2::String& SiguienteClave() const;
        const T& SiguienteSignificado() const;
        const aed2::String& AnteriorClave() const;
        const T& AnteriorSignificado() const;
        const_Elem Siguiente() const;
        const_Elem Anterior() const;
        void Avanzar();
        void Retroceder();

    private:

        aed2::Lista<aed2::String>::const_Iterador it_claves_;
        typename aed2::Lista<T*>::const_Iterador it_significados_;

        const_Iterador(const DiccionarioTitulos<T>* d);

        friend typename DiccionarioTitulos<T>::const_Iterador DiccionarioTitulos<T>::CrearIt() const;
    };

		struct const_Elem
    {
      public:

        const aed2::String& clave;
        const T& significado;

        const_Elem(const aed2::String& c, const T& s) : clave(c), significado(s) {}

        friend std::ostream& operator << (std::ostream& os, const DiccionarioTitulos<T>::const_Elem& e) {
          return os << e.clave << ":" << e.significado;
				}
		};

//Parte privada clase DiccionarioTitulos
private:

  struct Nodo
  {
    T significado;
    char caracter;              // Valor del caracter
    bool esPalabra;                   // Flag para indicar si es palabra
    Nodo * hijos[LETRAS];       // Letras del alfabeto
    

    //Constructor del nodo. Pasamos por referencia el T
    Nodo(const T& d, char c, bool esPalabra) : significado(d), caracter(c), esPalabra(esPalabra) 
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    };


    //Constructor del nodo. Pasamos por referencia el T
    Nodo(const T& d, char c) : significado(d), caracter(c), esPalabra(false) 
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    };   
    
    // Constructor del nodo sin parametros. Necesario para nodo raiz
    // Sobrecarga
    Nodo() : esPalabra(false)
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    }; 
    
    // Constructor del nodo definiciendo el caracter nomas. Necesario para nodos intermedios
    // Sobrecarga
    Nodo(char c): caracter(c), esPalabra(false)
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    }; 
    
    ~Nodo(){};
  };

  // Referencia del nodo raiz del diccionario
  Nodo * raiz;
  
  // Lista soporte para iteradores
  Lista<String> claves_;
  Lista<T*> significados_;
  
  // Funciones Auxiliares Privadas
  // ------------------------------------------
  // Debug - Recorrer Claves
  void RecorrerClaves(DiccionarioTitulos<T>::Nodo* n, String prefijo);
  // Borrar nodos
  void destruir(DiccionarioTitulos<T>::Nodo* n);
};

/*---------------------------------------------------------------
 * Sobrecarga de operadores
 *---------------------------------------------------------------
 * <<
 * ==
 */
template<class T>
std::ostream& operator << (std::ostream& os, const DiccionarioTitulos<T>& l);

template<class T>
bool operator == (const DiccionarioTitulos<T>& l1, const DiccionarioTitulos<T>& k2);


/*---------------------------------------------------------------
 * Implementacion de Diccionario Trie
 *---------------------------------------------------------------
 * Constructor
 * Creamos un Diccionario vacio
 */
template <typename T>
//DiccionarioTitulos<T>::DiccionarioTitulos(): raiz(NULL) {};
//Usamos el constructor de nodo sin parametros
DiccionarioTitulos<T>::DiccionarioTitulos()
{
  this->raiz = new Nodo();
  this->raiz->esPalabra = false;
}


/*
 * Destructor DiccionarioTitulos
 * --> Auxiliar: destruir(nodo)
 */
template <typename T>
DiccionarioTitulos<T>::~DiccionarioTitulos()
{
  destruir(this->raiz);
}

/*
 * Destruir(nodo)
 * Destructor Auxiliar
 * --> Recorre recursivamente y va borrando todo
 */
template <typename T>
void DiccionarioTitulos<T>::destruir(DiccionarioTitulos<T>::Nodo* n)
{
  if(n != NULL) // Evitar Segmentation fault
  {
    for( int i= 0; i< LETRAS; ++i)
    {
      if(n-> hijos[i] != NULL)
        destruir((DiccionarioTitulos<T>::Nodo*)n->hijos[i]);
    }  
    delete n;
  }
}

/* Operador = 
 * Copia 2 diccionarios usando el iterador del source
 * Previamente elimino toda la informacion que contiene
 * el diccionario target
 */

template<typename T>
DiccionarioTitulos<T>& DiccionarioTitulos<T>::operator = (const DiccionarioTitulos<T>& otro)
{
	Nodo* n = this->raiz;
	// Limpio el diccionario actual, solo dejo la raiz
	// con todos sus punteros apuntando a NULL
	for( int i= 0; i< LETRAS; ++i)
  {
  	if(n-> hijos[i] != NULL)
  	{
  		// Mando a destruir todo lo que tenga recursivamente para abajo
  		destruir((DiccionarioTitulos<T>::Nodo*)n->hijos[i]);
  		// Luego redefino a NULL el puntero 
  		n->hijos[i] = NULL;
  	}
  } 

	// Limpiamos las listas que guardan la info de los iteradores
  while( !(this->claves_.EsVacia()) ) {
    claves_.Fin();
    significados_.Fin();
  }

	// Creo un iterador del diccionario que me estan pasando
	DiccionarioTitulos<T>::const_Iterador it_otro = otro.CrearIt();
  // Lo recorro y voy definiendo
  
	while(it_otro.HaySiguiente())
  {
  	this->definir(it_otro.SiguienteClave(),it_otro.SiguienteSignificado());
  	it_otro.Avanzar();
  }
  

  return *this;
}


/*
 * Definir
 * Pasamos la clave y el significado
 * Ambos son constantes x referencia
 * Permite reDefinir claves para cambiar significados
 * Solo agrega a las listas de iteradores si es una nueva clave.
 * Esto lo sabemos verificando el flag Nodo->esPalabra
 */
template <typename T>
void DiccionarioTitulos<T>::definir(const String &clave, const T& significado)
{

		Nodo * NodoActual = raiz;
 
    for (unsigned int i = 0; i < clave.size(); ++i)
    {
        char actualChar = tolower(clave.at(i));
        // Si Restamos la 'a' y pedimos index > 0 podemos garantizar solo letras
        int index = actualChar ;//- 'a';
        #ifdef DEBUG
        	assert(index >= 0); 
        #endif    
        if (NodoActual->hijos[index] != NULL)
            NodoActual = NodoActual->hijos[index];
        else
        {		//Nodos intermedios de complemento C A* S* A que no existen
            Nodo * nuevoNodo = new Nodo(actualChar);	//new Nodo(significado,actualChar);
            NodoActual->hijos[index] = nuevoNodo;
            NodoActual = nuevoNodo;
        }
        // pregunto si llegamos al nodo donde debemos guardar el significado
        // C A S A*
        if (i == clave.size() - 1)
        {		
            NodoActual->significado = significado;	// Redefinir paso por copia....... revisar!
		        if (NodoActual->esPalabra == false) // Nueva definicion
		        {
				    	// Soporte Iterador, si la clave no estaba definida la agrego a la lista
				    	// Si estaba definida, no hacemos nada
							claves_.AgregarAtras(clave);										// Guardamos el string
				      significados_.AgregarAtras(& NodoActual->significado); // Guardamos la posicion de memoria
				      NodoActual->esPalabra = true;
				    }
        }
    }
}

//Definido???
// Utilizamos el flag Nodo->esPalabra para chequear si una clave esta definida o no
template <typename T>
bool DiccionarioTitulos<T>::definido(const aed2::String &clave)
{
  if (this->raiz == NULL) 
      return false;  
  else
  {
    Nodo * NodoActual = this->raiz;
    for (unsigned int i = 0; i < clave.size(); ++i)
    {
        char actualChar = tolower(clave.at(i));
        int index = actualChar;//- 'a';
        #ifdef DEBUG
        	assert(index >= 0);
        #endif
        if (NodoActual->hijos[index] != NULL)
            NodoActual = NodoActual->hijos[index];
        else
            return false;

				// Llego a destino pero no esta definido 
        if (i == clave.size() - 1 && !NodoActual->esPalabra)
            return false;
    }
    return true;
  }
}

//Obtener 
//PRE: assert(definido?)
template <typename T>
const T& DiccionarioTitulos<T>::obtener(const aed2::String &clave)
{
		#ifdef DEBUG
			assert(definido(clave));
		#endif
    Nodo * NodoActual = this->raiz;
    for (unsigned int i = 0; i < clave.size(); ++i)
    {
        char actualChar = tolower(clave.at(i));
        int index = actualChar;
        #ifdef DEBUG
        	assert(index >= 0);
        #endif
        if (NodoActual->hijos[index] != NULL)
            NodoActual = NodoActual->hijos[index];        
    }
    // Lo encuentra, entonces devuelvo el significado
    return NodoActual->significado;
}

// Borrar
// TODO 
// Falta terminar, borrar los nodos que no se usan mas
// aca simplemente lo busca y  desactiva el flag de significado
template <typename T>
void DiccionarioTitulos<T>::borrar(const aed2::String &clave)
{
    Nodo * NodoActual = this->raiz;
    for (unsigned int i = 0; i < clave.size(); ++i)
    { 
        char actualChar = tolower(clave.at(i));
        int index = actualChar ;//- 'a';
        #ifdef DEBUG
        	assert(index >= 0);
        #endif
        if (NodoActual->hijos[index] != NULL)
            NodoActual = NodoActual->hijos[index];
        else
            return;
        if (i == clave.size() - 1 && NodoActual->esPalabra)
            NodoActual->esPalabra = false;
    }
}

// Funcion para mostrar los significados
// TODO
// Mostrar Arbol Trie
template<class T>
  std::ostream& operator<<(std::ostream& out, const DiccionarioTitulos<T>& a) {
  return a.mostrar(out);
}

template <typename T>
std::ostream& DiccionarioTitulos<T>::mostrar(std::ostream& o) const{
  o << "[";
  o << "Falta terminar";
  return o << "] ";
}
// Debugging
// Recorremos recursivamente el DiccionarioTrie para mostrar las claves
template <typename T>
void DiccionarioTitulos<T>::RecorrerClaves(DiccionarioTitulos<T>::Nodo * Nodo, String prefijo = "")
{
	if (this->raiz != NULL) 
	{
		  // Si es nodo final -> tiene significado y lo mostramos
		  // Evitamos mostrar el nodo raiz, que es un nodo dummy
		  if (Nodo->esPalabra && Nodo != this->raiz)
		      std::cout << "        " << prefijo << " - " << Nodo->significado  << std::endl;

		  for (int i = 0; i < LETRAS; ++i)
		  {
		      if (Nodo->hijos[i] != NULL)
		      {
		          aed2::String actualString = prefijo + Nodo->hijos[i]->caracter;
		          RecorrerClaves(Nodo->hijos[i], actualString);
		      }
		  }
	}else{
    	std::cout << "Diccionario Vacio" << std::endl;
  }
}

// Claves - Funcion Publica
template <typename T>
void DiccionarioTitulos<T>::claves()
{
  RecorrerClaves(this->raiz, "");
}

// Crear Iteradores!
template <typename T>
typename DiccionarioTitulos<T>::const_Iterador DiccionarioTitulos<T>::CrearIt() const
{
  return const_Iterador(this);
}

/*---------------------------------------------------------------
 * Implementacion del Iterador Constante
 *---------------------------------------------------------------
 */
template<typename T>
DiccionarioTitulos<T>::const_Iterador::const_Iterador()
{}

template<typename T>
DiccionarioTitulos<T>::const_Iterador::const_Iterador(const typename DiccionarioTitulos<T>::const_Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}

template<typename T>
typename DiccionarioTitulos<T>::const_Iterador& DiccionarioTitulos<T>::const_Iterador::operator=(const typename DiccionarioTitulos<T>::const_Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;

  return *this;
}

template<typename T>
bool DiccionarioTitulos<T>::const_Iterador::HaySiguiente() const
{
  return it_claves_.HaySiguiente();
}

template<typename T>
bool DiccionarioTitulos<T>::const_Iterador::HayAnterior() const
{
  return it_claves_.HayAnterior();
}

template<typename T>
const aed2::String& DiccionarioTitulos<T>::const_Iterador::SiguienteClave() const
{
  #ifdef DEBUG
  	assert(HaySiguiente());
  #endif

  return it_claves_.Siguiente();
}

template<typename T>
const T& DiccionarioTitulos<T>::const_Iterador::SiguienteSignificado() const
{
  #ifdef DEBUG
  	assert(HaySiguiente());
  #endif
	// Como guardamos punteros, aca necesitamos desreferenciar el objeto
  return *it_significados_.Siguiente();
}

template<typename T>
typename DiccionarioTitulos<T>::const_Elem DiccionarioTitulos<T>::const_Iterador::Siguiente() const
{
  #ifdef DEBUG
  	assert( HaySiguiente() );
  #endif

  return const_Elem(SiguienteClave(), SiguienteSignificado());
}

template<typename T>
const aed2::String& DiccionarioTitulos<T>::const_Iterador::AnteriorClave() const
{
  #ifdef DEBUG
  	assert( HayAnterior() );
  #endif

  return it_claves_.Anterior();
}

template<typename T>
const T& DiccionarioTitulos<T>::const_Iterador::AnteriorSignificado() const
{
  #ifdef DEBUG
  	assert(HayAnterior());
  #endif
	//Guardamos punteros, desreferenciamos para mandar el objeto
  return *it_significados_.Anterior();
}

template<typename T>
typename DiccionarioTitulos<T>::const_Elem DiccionarioTitulos<T>::const_Iterador::Anterior() const
{
  #ifdef DEBUG
  	assert( HayAnterior() );
  #endif

  return const_Elem(AnteriorClave(), AnteriorSignificado());
}

template<typename T>
void DiccionarioTitulos<T>::const_Iterador::Avanzar()
{
  #ifdef DEBUG
  	assert(HaySiguiente());
  #endif

  it_claves_.Avanzar();
  it_significados_.Avanzar();
}

template<typename T>
void DiccionarioTitulos<T>::const_Iterador::Retroceder()
{
  #ifdef DEBUG
  	assert(HayAnterior());
  #endif

  it_claves_.Retroceder();
  it_significados_.Retroceder();
}

template<typename T>
DiccionarioTitulos<T>::const_Iterador::const_Iterador(const DiccionarioTitulos<T>* d)
  : it_claves_(d->claves_.CrearIt()), it_significados_(d->significados_.CrearIt())
{}

template<typename T>
bool DiccionarioTitulos<T>::const_Iterador::operator == (const typename DiccionarioTitulos<T>::const_Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_;
}
#endif //DICCTITULOS_H_
