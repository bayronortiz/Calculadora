//Define la clase que realiza operaciones con objetos de tipo BigInteger

#ifndef OPERBIGINTEGER_HPP
#define OPERBIGINTEGER_HPP
//Librerias
#include <stack>
#include <string>
using namespace std;

#include "biginteger.hpp"

//Inicio de Clase
class OperBigInteger{
	public:
		OperBigInteger();	//Constructor
		~OperBigInteger(); //Destructor de clase
		BigInteger sumar(const BigInteger&, const BigInteger&); //Suma dos numeros Tipo BigInteger
		BigInteger restar(const BigInteger&, const BigInteger&); //Resta dos numero Tipo BigInteger
	
	private:
		unsigned int pesoPila(stack<int> Pila);	//Utilitaria, determina la suma de los elementos de la pila
		stack<int> complementoUno(stack<int> Pila, const unsigned int&);	//Utilitaria, realiza complemento a 1 del menor
	
}; //Termina la clase OperBigInteger
#endif
