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
 * Ultima modificacion: 25/6/2014 - 20:29 pm
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

namespace aed2
{

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
  void definir(const String &clave, const T& dato);
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
        const String& SiguienteClave() const;
        const T& SiguienteSignificado() const;
        const String& AnteriorClave() const;
        const T& AnteriorSignificado() const;
        const_Elem Siguiente() const;
        const_Elem Anterior() const;
        void Avanzar();
        void Retroceder();

    private:

        typename Lista<String>::const_Iterador it_claves_;
        typename Lista<T*>::const_Iterador it_significados_;

        const_Iterador(const DiccionarioTitulos<T>* d);

        friend typename DiccionarioTitulos<T>::const_Iterador DiccionarioTitulos<T>::CrearIt() const;
    };

		struct const_Elem
    {
      public:

        const String& clave;
        const T& significado;

        const_Elem(const String& c, const T& s) : clave(c), significado(s) {}

        friend std::ostream& operator << (std::ostream& os, const DiccionarioTitulos<T>::const_Elem& e) {
          return os << e.clave << ":" << e.significado;
				}
		};

//Parte privada clase DiccionarioTitulos
private:

  struct Nodo
  {
    T dato;
    char caracter;              // Valor del caracter
    bool end;                   // Flag para indicar si es palabra
    Nodo * hijos[LETRAS];       // Letras del alfabeto
    
    //Constructor del nodo. Pasamos por referencia el T
    Nodo(const T& d, char c) : dato(d), caracter(c), end(false) 
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    };   
    
    // Constructor del nodo sin parametros. Necesario para nodo raiz
    // Sobrecarga
    Nodo() : end(false)
    { // Inicializamos los hijos del nodo con valor NULL
      for (int i = 0; i < LETRAS; ++i)
        this->hijos[i] = NULL;
    }; 
    
    // Constructor del nodo definiciendo el caracter nomas. Necesario para nodos intermedios
    // Sobrecarga
    Nodo(char c): caracter(c), end(false)
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
  void RecorrerClaves(aed2::DiccionarioTitulos<T>::Nodo* n, String prefijo);
  // Borrar nodos
  void destruir(aed2::DiccionarioTitulos<T>::Nodo* n);

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
  this->raiz->end = false;
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
void DiccionarioTitulos<T>::destruir(aed2::DiccionarioTitulos<T>::Nodo* n)
{
  if(n != NULL) // Evitar Segmentation fault
  {
    for( int i= 0; i< LETRAS; ++i)
    {
      if(n-> hijos[i] != NULL)
        destruir((aed2::DiccionarioTitulos<T>::Nodo*)n->hijos[i]);
    }  
    delete n;
  }
}

/*
 * Definir
 * Pasamos la clave y el significado
 * Ambos son constantes x referencia
 * Permite reDefinir claves para cambiar datos
 * Solo agrega a las listas de iteradores si es una nueva clave.
 * Esto lo sabemos verificando el flag Nodo->end
 */
template <typename T>
void DiccionarioTitulos<T>::definir(const String &clave, const T& dato)
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
            Nodo * nuevoNodo = new Nodo(actualChar);	//new Nodo(dato,actualChar);
            NodoActual->hijos[index] = nuevoNodo;
            NodoActual = nuevoNodo;
        }
        // pregunto si llegamos al nodo donde debemos guardar el dato
        // C A S A*
        if (i == clave.size() - 1)
        {		
            NodoActual->dato = dato;	// Redefinir paso por copia....... revisar!
		        if (NodoActual->end == false) // Nueva definicion
		        {
				    	// Soporte Iterador, si la clave no estaba definida la agrego a la lista
				    	// Si estaba definida, no hacemos nada
							claves_.AgregarAtras(clave);										// Guardamos el string
				      significados_.AgregarAtras(& NodoActual->dato); // Guardamos la posicion de memoria
				      NodoActual->end = true;
				    }
        }
    }
}

//Definido???
// Utilizamos el flag Nodo->end para chequear si una clave esta definida o no
template <typename T>
bool DiccionarioTitulos<T>::definido(const String &clave)
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
        if (i == clave.size() - 1 && !NodoActual->end)
            return false;
    }
    return true;
  }
}

//Obtener 
//PRE: assert(definido?)
template <typename T>
const T& DiccionarioTitulos<T>::obtener(const String &clave)
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
        /*else
          // Aca hay que ver bien el control de errores
          // Que pasa si no lo encuentra?
            return this->raiz->dato;

        if (i == clave.size() - 1 && !NodoActual->end)
          // No lo encuentra
            return this->raiz->dato;
         */
    }
    // Lo encuentra, entonces devuelvo el dato
    return NodoActual->dato;
}

// Borrar
// TODO 
// Falta terminar, borrar los nodos que no se usan mas
// aca simplemente lo busca y  desactiva el flag de significado
template <typename T>
void DiccionarioTitulos<T>::borrar(const String &clave)
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
        if (i == clave.size() - 1 && NodoActual->end)
            NodoActual->end = false;
    }
}

// Funcion para mostrar los datos
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
void DiccionarioTitulos<T>::RecorrerClaves(aed2::DiccionarioTitulos<T>::Nodo * Nodo, String prefijo = "")
{
	if (this->raiz != NULL) 
	{
		  // Si es nodo final -> tiene significado y lo mostramos
		  // Evitamos mostrar el nodo raiz, que es un nodo dummy
		  if (Nodo->end && Nodo != this->raiz)
		      std::cout << "        " << prefijo << " - " << Nodo->dato  << std::endl;

		  for (int i = 0; i < LETRAS; ++i)
		  {
		      if (Nodo->hijos[i] != NULL)
		      {
		          String actualString = prefijo + Nodo->hijos[i]->caracter;
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
const String& DiccionarioTitulos<T>::const_Iterador::SiguienteClave() const
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
const String& DiccionarioTitulos<T>::const_Iterador::AnteriorClave() const
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


}// Final del NameSpace aed2

#endif //DICCTITULOS_H_
