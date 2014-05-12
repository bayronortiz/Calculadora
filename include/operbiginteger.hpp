//Define la clase que realiza operaciones con objetos de tipo BigInteger

#ifndef OPERBIGINTEGER_HPP
#define OPERBIGINTEGER_HPP
//Librerias
#include <stack>
#include <string>
#include <vector>
using namespace std;

#include "biginteger.hpp"

//Inicio de Clase
class OperBigInteger{
	public:
		OperBigInteger();	//Constructor
		~OperBigInteger(); //Destructor de clase
		BigInteger sumar(const BigInteger&, const BigInteger&); //Aplica las acciones necesarias para sumar
		BigInteger restar(const BigInteger&, const BigInteger&); //Resta dos numero Tipo BigInteger
		BigInteger multiplicar(const BigInteger&, const BigInteger&); //Multiplica dos numeros
		BigInteger dividir(const BigInteger&, const BigInteger&);	//Realiza la division de dos numeros
	
	private:
		BigInteger operarSuma(const BigInteger&, const BigInteger&); //Suma dos numeros Tipo BigInteger
		BigInteger operarResta(const BigInteger&, const BigInteger&);		//Operacion básica de la resta
		BigInteger operarDivision(const BigInteger&, const BigInteger&);	//Operacion division
		unsigned int pesoPila(stack<int> Pila);	//Utilitaria, determina la suma de los elementos de la pila
		stack<int> complementoUno(stack<int> Pila, const unsigned int&);	//Utilitaria, realiza complemento a 1 del menor
		vector<int> pilaToVector(stack<int> Pila);		//Utilitaria que lleva el contenido de la pila a un vector
	
}; //Termina la clase OperBigInteger
#endif
