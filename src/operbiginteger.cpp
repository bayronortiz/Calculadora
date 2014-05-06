//Definicion de las funciones miembro de la clase OperBigInteger

#include <iostream>
#include "../headers/operbiginteger.hpp"


//Constructor
OperBigInteger::OperBigInteger(){}

//Destructor
OperBigInteger::~OperBigInteger(){/*std::cout<< "Termina Objeto OperBigInteger"<< endl;*/}

//Funcion miembro encargada de sumar
BigInteger OperBigInteger::sumar(const BigInteger &numA, const BigInteger &numB){
	int n1=0, n2=0, totalTemp=0, sobrante= 0;
	stack<int> pilaMayor, pilaMenor, pilaResultado;
	string resultadoTexto;
	BigInteger Resultado;	//Guarda la respuesta en un objeto biginteger
	
	if(numA.getPilaNumero().size() > numB.getPilaNumero().size())
	{
		pilaMayor= numA.getPilaNumero();
		pilaMenor= numB.getPilaNumero();
	}
	else
	{
		pilaMayor= numB.getPilaNumero();
		pilaMenor= numA.getPilaNumero();
	}
	
	while(!pilaMayor.empty()) //Repito el ciclo hasta que la pila este vacia
	{
		n1= pilaMayor.top();	//Obtengo el valor de la cima de la pila Mayor
		pilaMayor.pop();  //Desapilo el elemento pila Mayor
		
		if(!pilaMenor.empty())
		{
			n2= pilaMenor.top();
			pilaMenor.pop();
		}
		else 
			n2= 0;
		
		totalTemp= n1 + n2 + sobrante;
		
		if(totalTemp >= 10)
		{
			sobrante= totalTemp / 10;	//Tomamos las decenas
			totalTemp %= 10;		//Tomamos las unidades
		}
		else 
			sobrante= 0;
		
		pilaResultado.push(totalTemp);
	}
	
	if(sobrante != 0)
		pilaResultado.push(sobrante); //Apilo el resultado sobrante si no es cero
	
	while(!pilaResultado.empty())
	{
		resultadoTexto+= to_string(pilaResultado.top());
		pilaResultado.pop();
	}
	
	Resultado.setNumero(resultadoTexto);
	
	return Resultado;
}

//Funcion miembro encargada de restart
BigInteger OperBigInteger::restar(const BigInteger &numA, const BigInteger &numB){
	unsigned int tamA, tamB, pesoA, pesoB, n1, n2, sumTemp, sobrante;
	stack<int> pilaMayor, pilaMenor, pilaResultado, temp;
	string resultadoTexto;
	bool signoNegativo= false;
	BigInteger resultado;

	tamA= numA.getPilaNumero().size();	//Obtenemos tamaño pila A
	tamB= numB.getPilaNumero().size();	//Obtenemos tamaño pila B

	//Escogemos cual es la pilaMayor
	if(tamA > tamB)
	{
		pilaMayor= numA.getPilaNumero();
		pilaMenor= numB.getPilaNumero();
	}
	else if(tamA < tamB)
	{
		pilaMayor= numB.getPilaNumero();
		pilaMenor= numA.getPilaNumero();
		signoNegativo= true;		//Activamos la bandera signo
	}
	else
	{
		pesoA= this->pesoPila(numA.getPilaNumero());	//Obtengo el peso de la pila numA
		pesoB= this->pesoPila(numB.getPilaNumero());	//Obtengo el peso de la pila numB
		
		//definimos mayor y menor
		if(pesoA > pesoB)
		{
			pilaMayor= numA.getPilaNumero();
			pilaMenor= numB.getPilaNumero();
		}
		else if(pesoA < pesoB)
		{
			pilaMayor= numB.getPilaNumero();
			pilaMenor= numA.getPilaNumero();
			signoNegativo= true;		//Activamos la bandera signo		
		}
		else
		{
			if(stoll(numA.getNumero()) > stoll(numB.getNumero()))	
			{
				pilaMayor= numA.getPilaNumero();
				pilaMenor= numB.getPilaNumero();
			}
			else
			{
				pilaMayor= numB.getPilaNumero();
				pilaMenor= numA.getPilaNumero();
				signoNegativo= true;		//Activamos la bandera signo	
			}
			
		}
	}

	//Luego de tener las pilas ya seleccionadas, realizamos complemento a 1
	//para la pilaMenor y sumamos
	temp= this->complementoUno(pilaMenor, pilaMayor.size());
	pilaMenor= temp;
	
	while(!pilaMayor.empty())
	{
		n1= pilaMayor.top();
		pilaMayor.pop();
		
		if(!pilaMenor.empty())
		{
			n2= pilaMenor.top();
			pilaMenor.pop();
		}
		else 
			n2= 0;
		
		sumTemp= n1 + n2 + sobrante;
		
		if(sumTemp >= 10)
		{
			sobrante= sumTemp / 10;	//Tomamos las decenas
			sumTemp %= 10;		//Tomamos las unidades
		}
		else 
			sobrante= 0;
		
		pilaResultado.push(sumTemp);	//Apilamos el resultado
	}
	
	while(!pilaResultado.empty())
	{
		resultadoTexto+= to_string(pilaResultado.top());
		pilaResultado.pop();
	}
	
	if(resultadoTexto != "0")
		resultado.setNumero(resultadoTexto,signoNegativo);	//Se asigna el numero, con o sin signo
	else
		resultado.setNumero("0");
	
	return resultado;	//Retorna el objeto BigInteger
}

//Funcion utilitaria que encuentra el peso de la pila
unsigned int OperBigInteger::pesoPila(stack<int> Pila){
	unsigned int total= 0;
	
	while(!Pila.empty())
	{
		total+= Pila.top();
		Pila.pop();
	}
	
	return total;
}

//Funcion utilitaria que realiza complemento a 1, retorna una pila
stack<int> OperBigInteger::complementoUno(stack<int> Pila, const unsigned int &tamPilaMayor){
	stack<int> resultado, temp;	//Pila que se retorna como resultado y temporal
	unsigned int sobrante= 0, complemento, i;
	unsigned int agregar= tamPilaMayor - Pila.size();	//Define la cantidad de 9s a agregar en el complemento
	
	
	while(!Pila.empty())
	{
		Pila.top()+= sobrante;
		
		if(Pila.top() == 0)
			temp.push(Pila.top());	//Agregamos directamente a la pila temporal
		else
		{
			complemento= 10 - Pila.top();	//Encontramos el complemento de cada numero
			temp.push(complemento);		//Agregamos a la cola
			sobrante= 1;
		}
		Pila.pop();
	}
	
	//Agregamos los 9 necesarios a la pila resultado
	if(agregar > 0)
		for(i=0; i<agregar; i++)
			resultado.push(9);
		
	//Agregamos los numero de la pila temporal a la pila resultado
	while(!temp.empty())
	{
		resultado.push(temp.top());
		temp.pop();
	}
	
	return resultado;
}
