#include <iostream>
#include <cstdlib>
using namespace std;

#include "include/biginteger.hpp"
#include "include/operbiginteger.hpp"


int main(){
	BigInteger num1("123456789"), num2("123456789");
	BigInteger num3("123456789"), num4("987654321");
	OperBigInteger oper;
	
	
	cout<< "Suma:\n\t";
	cout<< num1.getNumero()<< " + "<< num2.getNumero()<< "= "<< oper.sumar(num1,num2).getNumero()<<endl;
	
	cout<< "Resta: \n\t";
	cout<< num3.getNumero()<< " - "<< num4.getNumero()<< "= "<< oper.restar(num3,num4).getNumero()<< endl;
	
	
	_Exit(EXIT_SUCCESS);
}
