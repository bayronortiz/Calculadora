// Definicion de las funciones miembro de la clase BigInteger

//Librerias
#include <iostream>
#include "../headers/biginteger.hpp"	//Contiene la definicion de la clase

//Constructor
BigInteger::BigInteger(const string &numero, const bool negativo){
	this->setNumero(numero, negativo);
}

//Destructor
BigInteger::~BigInteger(void){/*std::cout<< "Termina Objeto BigInteger"<< endl;*/}

//Modificadores y consultores
void BigInteger::setNumero(string numero){
	this->setNumero(numero, false);
}

//Modificador del numero sobrecargado
void BigInteger::setNumero(string numero, const bool negativo){
	this->negativo= negativo;
	
	if(validarNumero(numero))	//si el numero es valido lo asigna de lo contrario asigna 0 cero
		this->numero= this->ignorarCerosIzq(numero);
	else
		this->numero= "0";
	
	this->cargarNumeroPila();	//carga el numero en la pila
}

//Consultor del atributo numero
string BigInteger::getNumero(void)const{
	if(this->negativo)
		return "-" + this->numero;
	else
		return this->numero;
}

//Consultor de la pila numeros
stack<int> BigInteger::getPilaNumero(void)const{
	return this->pilaNumero;
}

//Funciones miembro utilitarias
//Valida el atributo numero de la clase.
bool BigInteger::validarNumero(string &numero){
	//Itera por c/u de los elementos del string buscando que todos los elementos
	//sean de tipo digito
	string::iterator it;	//creamos un iterador
	string::iterator itFin= numero.end();
	
	for(it=numero.begin(); it!=itFin; it++)
	{
		if(!isdigit(*it))
			return false;	//Termina la funcion inmediatamente. Numero invalido
	}
	
	return true;	//Numero es valido
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
