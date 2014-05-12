// Definicion de las funciones miembro de la clase BigInteger

//Librerias
#include <iostream>
#include "../include/biginteger.hpp"	//Contiene la definicion de la clase

//Constructor
BigInteger::BigInteger(const string &numero){
	this->setNegativo(false);
	this->setNumero(numero);
}

//Destructor
BigInteger::~BigInteger(void){/*std::cout<< "Termina Objeto BigInteger"<< endl;*/}

//Modificador del numero sobrecargado
void BigInteger::setNumero(string numero){
	if(validarNumero(numero))	//si el numero es valido lo asigna de lo contrario asigna 0 cero
		this->numero= this->ignorarCerosIzq(numero);
	else
		this->numero= "0";
	
	//Si el número es cero, quita el signo
	if(this->numero == "0")
		this->setNegativo(false);
	
	this->cargarNumeroPila();	//carga el numero en la pila
}

//Consultor del atributo numero
string BigInteger::getNumero(void)const{
	if(this->numero == "0")
		return this->numero;
	else if(this->getNegativo())
		return "-" + this->numero;
	else
		return this->numero;
}

//Consultor de la pila numeros
stack<int> BigInteger::getPilaNumero(void)const{ return this->pilaNumero; }

//Consulta si el numero es negativos
bool BigInteger::getNegativo(void)const {	return this->negativo; }

//Funciones miembro utilitarias
void BigInteger::setNegativo(bool opcion){ this->negativo= opcion; }

//Valida el atributo numero de la clase.
bool BigInteger::validarNumero(string &numero){
	//Itera por c/u de los elementos del string buscando que todos los elementos
	//sean de tipo digito
	string::iterator it;	//creamos un iterador
	string::iterator itFin= numero.end();
	bool valido= true, signoNegativo= false;	//bandera para controlar que el numero sea valido y negativo
	
	//Accedemos al primer caracter de la cadena para verificar si es negativo
	//Establece el valor de la variable miembro negativo de la clase BigInteger
	if(numero.front() == '-')
	{
		numero.front()= '0';	
		signoNegativo= true;
	}
	
	for(it=numero.begin(); it!=itFin; it++)
	{
		if(!isdigit(*it))
		{
			valido= false;	//Termina la funcion inmediatamente. Numero invalido
			this->setNegativo(false);
			break;
		}
	}

	if(valido)
	{
		if(signoNegativo)
			this->setNegativo(true);	//Establecemos que el numero sea negativo
		else
			this->setNegativo(false);
			
		return true;	//Numero es valido
	}
	else
		return false;	//Numero es invalido
}

//Carga el string numero, a una pila elemento x elemento
void BigInteger::cargarNumeroPila(void){
	string::iterator it, itFin= this->numero.end();	//Creamos los iteradores
	string caracter;
	
	this->vaciarPila();	//Vacía el atributo pilaNumero de la clase 
	
	for(it=this->numero.begin(); it!=itFin; it++)
	{
		caracter= *it;
		this->pilaNumero.push(stoi(caracter));	//convertimos a entero el string, y apilamos
	}
}

//Encargado de limpiar el contenido del atributo pilaNumero
void BigInteger::vaciarPila(void){
	if(!this->pilaNumero.empty())
	{
		while(!this->pilaNumero.empty())
			this->pilaNumero.pop();		//Desapila hasta que la pila este vacia
	}
}

//Funcion utilitaria encaragada de eliminar ceros a la izquierda del numero
string BigInteger::ignorarCerosIzq(string &numero){
	string resultado, caracter;	//Cadena que guarda el resultado, y c/u de los caracteres
	string::iterator itIni, itFin= numero.end();
	bool ignorarCeros= true;
	
	for(itIni=numero.begin(); itIni!=itFin; itIni++)
	{
		caracter= *itIni;
		
		if(!(ignorarCeros == true && caracter == "0"))
		{
			resultado+= caracter;	//Concatena el caracter en la cadena
			ignorarCeros= false;
		}
	}
	
	if(resultado.size() != 0)
		return resultado;
	else
		return "0";
}
