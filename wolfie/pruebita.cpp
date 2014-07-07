// g++ ../wolfie/pruebita.cpp -o pruebita

#include <iostream>

using namespace std;

int main () {
	string *stringArray  = new string[10];
	string nombre = "lola";
	stringArray[0] = nombre;
	cout << stringArray[0] << endl;

	delete [] stringArray;


	return 0;

}