// g++ -g testsDiccTitulo.cpp -o tdt
// valgrind --leak-check=full ./tdt

#include <ostream>
#include <string>
#include "../mini_test.h"
#include "../wolfie/DiccionarioTitulos.h"
 
using namespace std;
using namespace aed2;
typedef unsigned long Nat;

struct titulo
{	
	public:
	string nombre;
    int maximo;             		
    int umbral; 
    int cotizacion;            		   	
};

struct titulo_sin_string
{	
	public:
    int maximo;             		
    int umbral; 
    int cotizacion;            		   	
};


/*
 * Crea un Diccionario con 1 elemento, lo buscamos y lo obtenemos
 */
void test_crear_dicc_1_elem() {
	
	DiccionarioTitulos<int> t;
	
	string nombre = "Jose";
	int valor=5;
	
	t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), true);
	ASSERT_EQ(t.obtener(nombre), valor);
}

/*
 * Crea un Diccionario sin elementos
 */
void test_crear_dicc_0_elem() {
	
	DiccionarioTitulos<int> t;
	
	string nombre = "Jose";
	
	//t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), false);
}


/*
 * Auxiliar para definir y chequear
 */

template<typename T>
void definir_assert(DiccionarioTitulos<T>& t, const string& nombre, const T& valor)
{
	t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), true);
	ASSERT_EQ(t.obtener(nombre), valor)
}
/*
 * Crea un Diccionario con elementos parecidos
 */
void test_nombres_parecidos() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"Jose",40);
	definir_assert(t,"JoseLus",20);
	definir_assert(t,"JoseFina",30);
	definir_assert(t,"JoseLuis",50);
	definir_assert(t,"Joses",70);
	definir_assert(t,"Joseus",990);
	#ifdef DEBUG
		cout << endl;
		t.claves();
  #endif
	
}
/*
 * Pasamos una estructura
 * TODO: revisar .claves()
 * Obviamente cout << struct explota. Ver de sobrecargar un ostream
 */
void test_pasando_structs() {

	titulo t1;
	t1.maximo = 2;
	t1.cotizacion = 10;
	t1.umbral=22;
	t1.nombre="YPF";
	
	DiccionarioTitulos<titulo> t;
	
	t.definir(t1.nombre, t1);
	ASSERT_EQ(t.definido(t1.nombre), true);
	
	titulo t_leido = t.obtener(t1.nombre);
	ASSERT_EQ(t1.umbral, t_leido.umbral);
	ASSERT_EQ(t1.cotizacion, t_leido.cotizacion);
	ASSERT_EQ(t1.maximo, t_leido.maximo);
	
	#ifdef DEBUG
		cout << endl;
		cout << "	" 	<< t_leido.nombre			<<	endl;
		cout << "		Max:"<< t_leido.maximo		<<	endl;
		cout << "		Cot:"<< t_leido.cotizacion	<<	endl;
		cout << "		Umb:"<< t_leido.umbral		<<	endl;
	#endif
}
/*
 * Definir 2 veces la misma structura
 */
void test_definir_2veces_lomismo() {

	titulo t1;
	t1.maximo = 2;
	t1.cotizacion = 10;
	t1.umbral=22;
	t1.nombre="YPF";
	
	DiccionarioTitulos<titulo> t;
	
	t.definir(t1.nombre, t1);
	ASSERT_EQ(t.definido(t1.nombre), true);
	
	titulo t_leido = t.obtener(t1.nombre);
	ASSERT_EQ(t1.umbral, t_leido.umbral);
	ASSERT_EQ(t1.cotizacion, t_leido.cotizacion);
	ASSERT_EQ(t1.maximo, t_leido.maximo);
	
	//Ok ahora definimos de nuevo para cambiar la cotizacion
	t1.cotizacion=5678;
	t.definir(t1.nombre, t1);
	ASSERT_EQ(t.definido(t1.nombre), true);
	
	titulo t_leido2 = t.obtener(t1.nombre);
	ASSERT_EQ(t1.umbral, t_leido2.umbral);
	ASSERT_EQ(t1.cotizacion, t_leido2.cotizacion);
	ASSERT_EQ(t1.maximo, t_leido2.maximo);
	
	#ifdef DEBUG
		cout << endl;
		cout << "	" 	<< t_leido.nombre			<<	endl;
		cout << "		Max:"<< t_leido.maximo		<< " - " << t_leido2.maximo 	<<	endl;
		cout << "		Cot:"<< t_leido.cotizacion	<< " - " << t_leido2.cotizacion <<	endl;
		cout << "		Umb:"<< t_leido.umbral		<< " - " << t_leido2.umbral		<<	endl;
	#endif
}


/*
 * Titulos con nombres rockeros
 */
void test_nombres_raros() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	definir_assert(t,"_%$32e432",30);
	definir_assert(t,"PEEP",50);
	definir_assert(t,"!DSA",70);
	definir_assert(t,"Jose",990);
	#ifdef DEBUG
		cout << endl;
		t.claves();
	#endif
}

/*
 * Crear Iterador 
 */
void test_crear_iterador() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	#ifdef DEBUG
		cout << endl;
		t.claves();
	#endif
}
/*
 * Crear Iterador y ver si hay siguiente
 */
void test_crear_iterador_2next() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), false);
  #ifdef DEBUG
		cout << endl;
		t.claves();
	#endif
}

/*
 * It - Siguiente Clave
 */
void test_it_siguienteClave() {
	
	DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Maradona";
	claves[2]= "Messi";
	
	definir_assert(t,claves[1],10);
	definir_assert(t,claves[2],4);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
  ASSERT_EQ(it.HaySiguiente(), true);
  ASSERT_EQ(it.SiguienteClave(), claves[1]);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), false);
  #ifdef DEBUG
		cout << endl;
		t.claves();
	#endif
}

/*
 * It - iteramos y mostramos todas las claves
 */
void test_it_mostrarClaves() {
	
	DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Maradona";
	claves[2]= "Messi";
	claves[0] = "Pipita";
	
	definir_assert(t,claves[1],10);
	definir_assert(t,claves[2],4);
	definir_assert(t,claves[0],16);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente())
	{
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << endl;
		#endif
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos y vemos el significado
 */
void test_it_mostrarClavesAndSig() {
	
	DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Rojo";
	claves[2]= "Messi";
	claves[0] = "Pipita";
	
	definir_assert(t,claves[1],16);
	definir_assert(t,claves[2],10);
	definir_assert(t,claves[0],9);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente())
	{
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		#endif
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos y vemos el significado
 */
void test_it_redefinirSignificados() {
	
	DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Rojo";
	claves[2]= "Messi";
	claves[0] = "Pipita";
	
	int num[3];
	num[0]=9;
	num[1]=16;
	num[2]=10;
	
	definir_assert(t,claves[0],num[0]);
	definir_assert(t,claves[1],num[1]);
	definir_assert(t,claves[2],num[2]);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();

	definir_assert(t,claves[0],num[0]*10);
	definir_assert(t,claves[1],num[1]*10);
	definir_assert(t,claves[2],num[2]*10);
	
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente())
	{
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		#endif
		ASSERT_EQ(it.SiguienteSignificado(), num[i]*10);
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos pa delante y pa tras
 */
void test_it_idaVuelta() {
	
	DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[0] = "Pipita";
	claves[1] = "Rojo";
	claves[2]= "Messi";
	
	int num[3];
	num[0]=9;
	num[1]=16;
	num[2]=10;
	
	definir_assert(t,claves[0],num[0]);
	definir_assert(t,claves[1],num[1]);
	definir_assert(t,claves[2],num[2]);
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();

	definir_assert(t,claves[0],num[0]*10);
	definir_assert(t,claves[1],num[1]*10);
	definir_assert(t,claves[2],num[2]*10);
	
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente())
	{
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		#endif
		ASSERT_EQ(it.SiguienteSignificado(), num[i]*10);
		it.Avanzar();
		i++;
	}
	
	i=0;
	#ifdef DEBUG
		cout << endl << " ---- Para Atras " << endl;
	#endif
	while(it.HayAnterior())
	{
		#ifdef DEBUG
			cout << "	" << it.AnteriorClave() << " - " << it.AnteriorSignificado() << endl;
		#endif
		ASSERT_EQ(it.AnteriorSignificado(), num[2-i]*10);
		it.Retroceder();
		i++;
	}	
	ASSERT_EQ(i, 3);
}

/*
 * Test: It - iteramos pa delante y pa tras
 * 	Redefinir
 *	Tuplas
 *	Shake It
 */
void tests_it_redef_shakeit() {
	titulo_sin_string t1;
	t1.maximo = 1;
	t1.cotizacion = 10;
	t1.umbral=100;
	
	DiccionarioTitulos<titulo_sin_string> t;
	
	
	t.definir("ABCDEFGHIJK", t1);
	ASSERT_EQ(t.definido("ABCDEFGHIJK"), true);
	
	titulo_sin_string t_leido = t.obtener("ABCDEFGHIJK");
	ASSERT_EQ(t1.umbral, t_leido.umbral);
	ASSERT_EQ(t1.cotizacion, t_leido.cotizacion);
	ASSERT_EQ(t1.maximo, t_leido.maximo);
	//Nodo intermedio
	titulo_sin_string t2;
	t2.maximo = 2;
	t2.cotizacion = 20;
	t2.umbral=200;
	t.definir("ABCDE", t2);
	ASSERT_EQ(t.definido("ABCDE"), true);
	titulo_sin_string t_leido_2 = t.obtener("ABCDE");
	ASSERT_EQ(t2.umbral, t_leido_2.umbral);
	ASSERT_EQ(t2.cotizacion, t_leido_2.cotizacion);
	ASSERT_EQ(t2.maximo, t_leido_2.maximo);
	
	//Nodo mas largo
	titulo_sin_string t3;
	t3.maximo = 3;
	t3.cotizacion = 30;
	t3.umbral=300;
	t.definir("ABCDEFGHIJKLMNO", t3);
	ASSERT_EQ(t.definido("ABCDEFGHIJKLMNO"), true);
	titulo_sin_string t_leido_3 = t.obtener("ABCDEFGHIJKLMNO");
	ASSERT_EQ(t3.umbral, t_leido_3.umbral);
	ASSERT_EQ(t3.cotizacion, t_leido_3.cotizacion);
	ASSERT_EQ(t3.maximo, t_leido_3.maximo);
	
	//Nodos no definidos pero que estan para la construccion de la cadena mas larga
	ASSERT_EQ(t.definido("ABCDEFGHIJKLMN"), false);
	ASSERT_EQ(t.definido("ABCDEFGHIJKL"), false);
	ASSERT_EQ(t.definido("ABCDEF"), false);
	ASSERT_EQ(t.definido("ABC"), false);
	
	//Crear un Iterador
	DiccionarioTitulos<titulo_sin_string>::const_Iterador it = t.CrearIt();
	
	int i=0;
	while(it.HaySiguiente())
	{
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}

void test_operador_igual() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"JoseFisarasa",30);
	definir_assert(t,"Jose",40);
	definir_assert(t,"JoseLus",20);
	definir_assert(t,"JoseFina",30);
	definir_assert(t,"JoseLuis",50);
	definir_assert(t,"Joses",70);
	definir_assert(t,"Joseus",990);
	// Redefino para molestar un toque
	definir_assert(t,"JoseFisarasa",1);
	definir_assert(t,"Jose",2);
	definir_assert(t,"JoseLus",3);
	definir_assert(t,"JoseFina",4);
	definir_assert(t,"JoseLuis",5);
	definir_assert(t,"Joses",6);
	definir_assert(t,"Joseus",7);
	
	//Creo una copia del diccionario
	DiccionarioTitulos<int> t_copia;
	t_copia = t;
	
	//Crear un Iterador para cada diccionario y los comparo
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	DiccionarioTitulos<int>::const_Iterador it_copia = t_copia.CrearIt();
	
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente() && it_copia.HaySiguiente())
	{	
		i++;
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it_copia.SiguienteClave() << endl;
			cout << "			" << it.SiguienteSignificado() << " - " << it_copia.SiguienteSignificado() << endl;
		#endif	
		ASSERT_EQ(it.SiguienteClave(), it_copia.SiguienteClave());
		ASSERT_EQ(it.SiguienteSignificado(),it_copia.SiguienteSignificado());
		it.Avanzar(); it_copia.Avanzar();
	}
	ASSERT_EQ((int)it_copia.HaySiguiente(), 0);
	ASSERT_EQ((int)it.HaySiguiente(), 0);
	ASSERT_EQ((int)it_copia.HayAnterior(), 1);
	ASSERT_EQ((int)it.HayAnterior(), 1);
	ASSERT_EQ(i, 7);
}


void test_operador_igual_agrego_cosas() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"JoseFisarasa",30);
	definir_assert(t,"Jose",40);
	definir_assert(t,"JoseLus",20);
	definir_assert(t,"JoseFina",30);
	definir_assert(t,"JoseLuis",50);
	definir_assert(t,"Joses",70);
	definir_assert(t,"Joseus",990);
	// Redefino para molestar un toque
	definir_assert(t,"JoseFisarasa",1);
	definir_assert(t,"Jose",2);
	definir_assert(t,"JoseLus",3);
	definir_assert(t,"JoseFina",4);
	definir_assert(t,"JoseLuis",5);
	definir_assert(t,"Joses",6);
	definir_assert(t,"Joseus",7);
	
	//Creo una copia del diccionario
	DiccionarioTitulos<int> t_copia;
	t_copia = t;
	
	//Crear un Iterador para cada diccionario y los comparo
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	DiccionarioTitulos<int>::const_Iterador it_copia = t_copia.CrearIt();
	
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente() && it_copia.HaySiguiente())
	{	
		i++;
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it_copia.SiguienteClave() << endl;
			cout << "			" << it.SiguienteSignificado() << " - " << it_copia.SiguienteSignificado() << endl;
		#endif	
		ASSERT_EQ(it.SiguienteClave(), it_copia.SiguienteClave());
		ASSERT_EQ(it.SiguienteSignificado(),it_copia.SiguienteSignificado());
		it.Avanzar(); it_copia.Avanzar();
	}
	ASSERT_EQ((int)it_copia.HaySiguiente(), 0);
	ASSERT_EQ((int)it.HaySiguiente(), 0);
	ASSERT_EQ((int)it_copia.HayAnterior(), 1);
	ASSERT_EQ((int)it.HayAnterior(), 1);
	ASSERT_EQ(i, 7);
	
	//ahora agrego un par de cositas al diccionario nuevo
	definir_assert(t_copia,"Figaza",10);
	definir_assert(t_copia,"Sarasa",2);
	DiccionarioTitulos<int>::const_Iterador it_copia_otro = t_copia.CrearIt();
	i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it_copia_otro.HaySiguiente())
	{	
		i++;
		#ifdef DEBUG
			cout << "	" << it_copia_otro.SiguienteClave() << " - " << it_copia_otro.SiguienteSignificado() << endl;
		#endif	
		it_copia_otro.Avanzar();
	}
	ASSERT_EQ((int)it_copia_otro.HaySiguiente(), 0);
	ASSERT_EQ((int)it_copia_otro.HayAnterior(), 1);
	ASSERT_EQ(i, 9);
	
}


void test_operador_igual_pisar_dicc_lleno() {
	
	DiccionarioTitulos<int> t;
	
	definir_assert(t,"JoseFisarasa",30);
	definir_assert(t,"Jose",40);
	definir_assert(t,"JoseLus",20);
	definir_assert(t,"JoseFina",30);
	definir_assert(t,"JoseLuis",50);
	definir_assert(t,"Joses",70);
	definir_assert(t,"Joseus",990);
	
	//Creo una copia del diccionario
	DiccionarioTitulos<int> t_copia;
	
	definir_assert(t_copia,"Brasil",21);
	definir_assert(t_copia,"decime",32);
	definir_assert(t_copia,"que",321);
	definir_assert(t_copia,"se",32);
	definir_assert(t_copia,"siente",54);
	definir_assert(t_copia,"tener",54);
	definir_assert(t_copia,"en",23);
	definir_assert(t_copia,"casa",263);
	definir_assert(t_copia,"a",73);
	definir_assert(t_copia,"tu",83);
	definir_assert(t_copia,"papa",76);
	definir_assert(t_copia,"!!!",12);
	
	t_copia = t;
	#ifdef DEBUG
		cout << endl;
		t_copia.claves();
	#endif
	
	//Crear un Iterador para cada diccionario y los comparo
	DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	DiccionarioTitulos<int>::const_Iterador it_copia = t_copia.CrearIt();
	
	int i=0;
	#ifdef DEBUG
		cout << endl;
	#endif
	while(it.HaySiguiente() && it_copia.HaySiguiente())
	{	
		i++;
		#ifdef DEBUG
			cout << "	" << it.SiguienteClave() << " - " << it_copia.SiguienteClave() << endl;
			cout << "			" << it.SiguienteSignificado() << " - " << it_copia.SiguienteSignificado() << endl;
		#endif	
		ASSERT_EQ(it.SiguienteClave(), it_copia.SiguienteClave());
		ASSERT_EQ(it.SiguienteSignificado(),it_copia.SiguienteSignificado());
		it.Avanzar(); it_copia.Avanzar();
	}
	ASSERT_EQ((int)it_copia.HaySiguiente(), 0);
	ASSERT_EQ((int)it.HaySiguiente(), 0);
	ASSERT_EQ((int)it_copia.HayAnterior(), 1);
	ASSERT_EQ((int)it.HayAnterior(), 1);
	ASSERT_EQ(i, 7);
}

int main() {
  RUN_TEST(test_crear_dicc_1_elem);
  RUN_TEST(test_crear_dicc_0_elem);
  RUN_TEST(test_nombres_parecidos);
  RUN_TEST(test_pasando_structs);
  RUN_TEST(test_definir_2veces_lomismo);
  RUN_TEST(test_nombres_raros);
  RUN_TEST(test_crear_iterador);
  RUN_TEST(test_crear_iterador_2next);
  RUN_TEST(test_it_siguienteClave);
  RUN_TEST(test_it_mostrarClaves);
  RUN_TEST(test_it_mostrarClavesAndSig);
  RUN_TEST(test_it_redefinirSignificados);
  RUN_TEST(test_it_idaVuelta);
  RUN_TEST(tests_it_redef_shakeit);
  RUN_TEST(test_operador_igual);
  RUN_TEST(test_operador_igual_agrego_cosas);
  RUN_TEST(test_operador_igual_pisar_dicc_lleno);
  return 0;
}

