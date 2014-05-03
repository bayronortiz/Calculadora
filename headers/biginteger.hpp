//Definicion de la clase BigInteger, contenedora de numeros enteros muy grandes

#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

//Librerias
#include <stack>
#include <string>
using namespace std;

//Inicio de Clase
class BigInteger{
	public:
		BigInteger(const string &numero = "0", const bool negativo= false);	//Constructor por defecto
		~BigInteger();		//Destructor
		void setNumero(string);		//Establece el numero
		void setNumero(string,const bool);		//sobrecargamos setNumero
		string getNumero(void)const;  //Obtiene el numero tipo string, no modifica al objeto
		stack<int> getPilaNumero(void)const;	//Obtiene la pila de enteros
	
	private:
		bool validarNumero(string&);	//Utilitaria valida que el atributo numero, solo contenga numeros
		void cargarNumeroPila(void);	//utilitaria Carga un string a una pilaNumero
		void vaciarPila(void);	//Utilitaria Limpia el contenido del atributo miembro pilaNumero
		string ignorarCerosIzq(string&);	//Utilitaria ignora los ceros a la izquierda ingresados en el numero
		bool negativo;		//Atributo que indica si el numero es negativo
		string numero;		//Contienen el numero
		stack<int> pilaNumero;	//Contiene la pila del numero
		
}; //Termina clase BigInteger
#endif
