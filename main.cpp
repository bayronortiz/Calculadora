#include <iostream>
#include <cstdlib>
using namespace std;

#include "include/biginteger.hpp"
#include "include/operbiginteger.hpp"


int main(){
	string n1, n2, resultado;
	BigInteger num1, num2;
	OperBigInteger oper;
	
	cout<< "\n:::OPERACIONES CON NUMEROS ENTEROS GRANDES:::\n\n";
	cout<< "Ingrese el Primer Numero--> ";
	cin>> n1;
	cout<< "Ingrese el Segundo Numero--> ";
	cin>> n2;
	
	num1.setNumero(n1);
	num2.setNumero(n2);
		
	resultado= oper.sumar(num1, num2).getNumero();	//Sumamos
	
	cout<< "\nResultados: \n";
	cout<< "\t"<< num1.getNumero()<< " + "<< num2.getNumero()<< "= "<< resultado<< endl;
	
	resultado= oper.restar(num1, num2).getNumero();		//Restamos
	
	cout<< "\t"<< num1.getNumero()<< " - "<< num2.getNumero()<< "= "<< resultado<< endl;
	
	resultado= oper.multiplicar(num1, num2).getNumero();		//Multiplicamos
	
	cout<< "\t"<< num1.getNumero()<< " * "<< num2.getNumero()<< "= "<< resultado<< endl;
	
	resultado= oper.dividir(num1, num2).getNumero();		//Dividimos
	
	cout<< "\t"<< num1.getNumero()<< " / "<< num2.getNumero()<< "= "<< resultado<< endl;
	
	
	exit(EXIT_SUCCESS);
}
