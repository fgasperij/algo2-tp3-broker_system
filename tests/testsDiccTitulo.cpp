// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include <ostream>
#include <string>
#include "../mini_test.h"
#include "../wolfie/DiccionarioTitulos.h"
 
using namespace std;
typedef unsigned long Nat;

struct titulo
{	
	public:
	string nombre;
    int maximo;             		
    int umbral; 
    int cotizacion;            		   	
};


/*
 * Crea un Diccionario con 1 elemento, lo buscamos y lo obtenemos
 */
void crear_dicc_1_elem() {
	
	aed2::DiccionarioTitulos<int> t;
	
	string nombre = "Jose";
	int valor=5;
	
	t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), true);
	ASSERT_EQ(t.obtener(nombre), valor);
}

/*
 * Crea un Diccionario sin elementos
 */
void crear_dicc_0_elem() {
	
	aed2::DiccionarioTitulos<int> t;
	
	string nombre = "Jose";
	
	//t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), false);
}


/*
 * Auxiliar para definir y chequear
 */

template<typename T>
void definir_assert(aed2::DiccionarioTitulos<T>& t, const string& nombre, const T& valor)
{
	t.definir(nombre, valor);
	ASSERT_EQ(t.definido(nombre), true);
	ASSERT_EQ(t.obtener(nombre), valor)
}
/*
 * Crea un Diccionario con elementos parecidos
 */
void nombres_parecidos() {
	
	aed2::DiccionarioTitulos<int> t;
	
	definir_assert(t,"Jose",40);
	definir_assert(t,"JoseLus",20);
	definir_assert(t,"JoseFina",30);
	definir_assert(t,"JoseLuis",50);
	definir_assert(t,"Joses",70);
	definir_assert(t,"Joseus",990);
	cout << endl;
	t.claves();
	
}
/*
 * Pasamos una estructura
 * TODO: revisar .claves()
 * Obviamente cout << struct explota. Ver de sobrecargar un ostream
 */
void pasando_structs() {

	titulo t1;
	t1.maximo = 2;
	t1.cotizacion = 10;
	t1.umbral=22;
	t1.nombre="YPF";
	
	aed2::DiccionarioTitulos<titulo> t;
	
	t.definir(t1.nombre, t1);
	ASSERT_EQ(t.definido(t1.nombre), true);
	
	titulo t_leido = t.obtener(t1.nombre);
	ASSERT_EQ(t1.umbral, t_leido.umbral);
	ASSERT_EQ(t1.cotizacion, t_leido.cotizacion);
	ASSERT_EQ(t1.maximo, t_leido.maximo);
	
	cout << endl;
	cout << "	" 	<< t_leido.nombre			<<	endl;
	cout << "		Max:"<< t_leido.maximo		<<	endl;
	cout << "		Cot:"<< t_leido.cotizacion	<<	endl;
	cout << "		Umb:"<< t_leido.umbral		<<	endl;
}
/*
 * Definir 2 veces la misma structura
 */
void definir_2veces_lomismo() {

	titulo t1;
	t1.maximo = 2;
	t1.cotizacion = 10;
	t1.umbral=22;
	t1.nombre="YPF";
	
	aed2::DiccionarioTitulos<titulo> t;
	
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
	
	cout << endl;
	cout << "	" 	<< t_leido.nombre			<<	endl;
	cout << "		Max:"<< t_leido.maximo		<< " - " << t_leido2.maximo 	<<	endl;
	cout << "		Cot:"<< t_leido.cotizacion	<< " - " << t_leido2.cotizacion <<	endl;
	cout << "		Umb:"<< t_leido.umbral		<< " - " << t_leido2.umbral		<<	endl;
	
}


/*
 * Titulos con nombres rockeros
 */
void nombres_raros() {
	
	aed2::DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	definir_assert(t,"_%$32e432",30);
	definir_assert(t,"PEEP",50);
	definir_assert(t,"!DSA",70);
	definir_assert(t,"Jose",990);
	cout << endl;
	t.claves();
}

/*
 * Crear Iterador 
 */
void crear_iterador() {
	
	aed2::DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	//cout << endl;
	//t.claves();
}
/*
 * Crear Iterador y ver si hay siguiente
 */
void crear_iterador_2next() {
	
	aed2::DiccionarioTitulos<int> t;
	
	definir_assert(t,"8765432",40);
	definir_assert(t,"_5342eERWERWew",20);
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), false);
	//cout << endl;
	//t.claves();
}

/*
 * It - Siguiente Clave
 */
void it_siguienteClave() {
	
	aed2::DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Maradona";
	claves[2]= "Messi";
	
	definir_assert(t,claves[1],10);
	definir_assert(t,claves[2],4);
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
  ASSERT_EQ(it.HaySiguiente(), true);
  ASSERT_EQ(it.SiguienteClave(), claves[1]);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), true);
  it.Avanzar();
  ASSERT_EQ(it.HaySiguiente(), false);
	//cout << endl;
	//t.claves();
}

/*
 * It - iteramos y mostramos todas las claves
 */
void it_mostrarClaves() {
	
	aed2::DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Maradona";
	claves[2]= "Messi";
	claves[0] = "Pipita";
	
	definir_assert(t,claves[1],10);
	definir_assert(t,claves[2],4);
	definir_assert(t,claves[0],16);
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	int i=0;
	cout << endl;
	while(it.HaySiguiente())
	{
		cout << "	" << it.SiguienteClave() << endl;
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos y vemos el significado
 */
void it_mostrarClavesAndSig() {
	
	aed2::DiccionarioTitulos<int> t;
	
	string claves[3];
	claves[1] = "Rojo";
	claves[2]= "Messi";
	claves[0] = "Pipita";
	
	definir_assert(t,claves[1],16);
	definir_assert(t,claves[2],10);
	definir_assert(t,claves[0],9);
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();
	int i=0;
	cout << endl;
	while(it.HaySiguiente())
	{
		cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos y vemos el significado
 */
void it_redefinirSignificados() {
	
	aed2::DiccionarioTitulos<int> t;
	
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
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();

	definir_assert(t,claves[0],num[0]*10);
	definir_assert(t,claves[1],num[1]*10);
	definir_assert(t,claves[2],num[2]*10);
	
	int i=0;
	cout << endl;
	while(it.HaySiguiente())
	{
		cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		ASSERT_EQ(it.SiguienteSignificado(), num[i]*10);
		it.Avanzar();
		i++;
	}
	ASSERT_EQ(i, 3);
}


/*
 * It - iteramos pa delante y pa tras
 */
void it_idaVuelta() {
	
	aed2::DiccionarioTitulos<int> t;
	
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
	aed2::DiccionarioTitulos<int>::const_Iterador it = t.CrearIt();

	definir_assert(t,claves[0],num[0]*10);
	definir_assert(t,claves[1],num[1]*10);
	definir_assert(t,claves[2],num[2]*10);
	
	int i=0;
	cout << endl;
	while(it.HaySiguiente())
	{
		cout << "	" << it.SiguienteClave() << " - " << it.SiguienteSignificado() << endl;
		ASSERT_EQ(it.SiguienteSignificado(), num[i]*10);
		it.Avanzar();
		i++;
	}
	
	i=0;
	cout << endl << " ---- Para Atras " << endl;
	while(it.HayAnterior())
	{
		cout << "	" << it.AnteriorClave() << " - " << it.AnteriorSignificado() << endl;
		ASSERT_EQ(it.AnteriorSignificado(), num[2-i]*10);
		it.Retroceder();
		i++;
	}
	
	
	ASSERT_EQ(i, 3);
	
}



int main() {
  RUN_TEST(crear_dicc_1_elem);
  RUN_TEST(crear_dicc_0_elem);
  RUN_TEST(nombres_parecidos);
  RUN_TEST(pasando_structs);
  RUN_TEST(definir_2veces_lomismo);
  RUN_TEST(nombres_raros);
  RUN_TEST(crear_iterador);
  RUN_TEST(crear_iterador_2next);
  RUN_TEST(it_siguienteClave);
  RUN_TEST(it_mostrarClaves);
  RUN_TEST(it_mostrarClavesAndSig);
  RUN_TEST(it_redefinirSignificados);
  RUN_TEST(it_idaVuelta);
  return 0;
}

