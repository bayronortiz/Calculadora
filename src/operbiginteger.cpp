//Definicion de las funciones miembro de la clase OperBigInteger

#include <iostream>
#include "../include/operbiginteger.hpp"


//Constructor
OperBigInteger::OperBigInteger(){}

//Destructor
OperBigInteger::~OperBigInteger(){/*std::cout<< "Termina Objeto OperBigInteger"<< endl;*/}


//suma dos numeros enteros grandes
BigInteger OperBigInteger::sumar(const BigInteger &numA, const BigInteger &numB){
	BigInteger resultado("0"), temp;
	
	//Realiza los llamados a funciones dependiendo de los signos de los numeros
	//ingresados
	if(numA.getNegativo())
	{
		if(numB.getNegativo())
		{
			temp= numB;
			temp.setNegativo(false);
			resultado= this->restar(numA,temp);
		}
		else
		{
			temp= numA;
			temp.setNegativo(false);
			
			resultado= this->restar(numB, temp);
		}
	}
	else if(numB.getNegativo())
	{
		temp= numB;
		temp.setNegativo(false);
		resultado= this->restar(numA, temp);
	}
	else
		resultado= this->operarSuma(numA, numB);
		
	return resultado;
}

//Funcion miembro encargada de sumar
BigInteger OperBigInteger::operarSuma(const BigInteger &numA, const BigInteger &numB){
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
	
	//Operamos con ambas pilas
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
	BigInteger resultado("0");		//creamos un objeto de tipo bigInteger lo inicializamos en cero
	
	//Definimos los casos que se dan en la resta en cuanto a los signos, luego
	//se llama a la funcion miembro privada operarResta que define la operacion como tal
	if(numA.getNegativo())
	{
		if(numB.getNegativo())
			resultado= this->operarResta(numB, numA);
		else
		{
			resultado= this->operarSuma(numA, numB);
			resultado.setNegativo(true);
		}
	}
	else if(numB.getNegativo())
		resultado= this->operarSuma(numA,numB);
	else
		resultado= this->operarResta(numA, numB);
	
	return resultado;	//Retornamos el resultado
}

//Funcion miembro encargada de multiplicar dos numeros
BigInteger OperBigInteger::multiplicar(const BigInteger &numA, const BigInteger &numB){
	unsigned int n, producto, sobrante=0, i, contadorCeros=0, tamVector, tamA, tamB;
	string numeroTemp;
	BigInteger resultadoFinal("0"), resultadoTemp;		//Guarda el resultado final del producto
	vector<int> vectorFactor;
	stack<int> pilaFactor, pilaTemp;
	stack<BigInteger> pilaResultados;
	bool signoNegativo= false;  //Bandera para controlar si el numero es negativo

	//obtengo los tamaños de pilas numA, numB
	tamA= numA.getPilaNumero().size();
	tamB= numB.getPilaNumero().size();
	
	//Asignamos la pila mayor a un arreglo, y la pila menor a una pila.
	if(tamA > tamB)
	{
		vectorFactor= this->pilaToVector(numA.getPilaNumero());
		pilaFactor= numB.getPilaNumero();	
	}
	else
	{
		vectorFactor= this->pilaToVector(numB.getPilaNumero());
		pilaFactor= numA.getPilaNumero();
	}
	
	tamVector= vectorFactor.size();
	//Realizamos el producto
	while(!pilaFactor.empty())
	{
		n= pilaFactor.top();	//Obtenemos cima pila
		pilaFactor.pop();		//desapilamos
		
		//Verificamos si existen ceros a agregar 
		if(contadorCeros != 0)
		{
			for(i=0; i<contadorCeros; i++)
				pilaTemp.push(0);
		}
		
		//Realizamos el producto de cada factor
		for(i=0; i<tamVector; i++)
		{
			producto= n * vectorFactor[i] + sobrante;	//Realizo el producto y sumo el sobrante
			
			if(producto >= 10)
			{
				sobrante= producto / 10;	//Tomamos las decenas
				producto %= 10;		//Tomamos las unidades
			}
			else 
				sobrante= 0;
			
			pilaTemp.push(producto);	
		}
		
		//si hay sobrante lo apilamos
		if(sobrante != 0)
		{
			pilaTemp.push(sobrante);
			sobrante= 0;
		}
			
		//Convierto la pilaTemp en un string y lo asignamos a un BigInteger
		while(!pilaTemp.empty())
		{
			numeroTemp+= to_string(pilaTemp.top()); //Concatenamos el numero
			pilaTemp.pop();	//Eliminamos de la pila
		}
		
		//Asignamos los BigInteger en la pila de resultados temporales
		pilaResultados.emplace(BigInteger(numeroTemp));
		
		//Incrementamos contador de ceros y limpiamos el string
		contadorCeros++;
		numeroTemp.clear();
	}
	
	
	//Ahora sumamos la pilaResultados, para obtener resultado final
	while(!pilaResultados.empty())
	{
		
		resultadoTemp= this->sumar(pilaResultados.top(), resultadoFinal);
		
		resultadoFinal= resultadoTemp;
		pilaResultados.pop();
	}
	
	//Observamos si algun numero es negativo
	if(numA.getNegativo())
	{
		if(!numB.getNegativo())
			signoNegativo= true;
	}
	else if(numB.getNegativo())
		signoNegativo= true;
	
	//Le decimos al biginteger que el numero que esta tratando es negativo
	resultadoFinal.setNegativo(signoNegativo);
		
	return resultadoFinal;  //Retornamos el resutadoFinal de tipo BigInteger
}

//funcion que realiza la division de enteros
BigInteger OperBigInteger::dividir(const BigInteger &dividendo, const BigInteger &divisor){
	BigInteger cociente("0");
	
	//Llamamos operar division y pasamos los numeros como parametros
	cociente= this->operarDivision(dividendo, divisor);
	
	//Definimos si el resultado es positivo o negativo
	if(dividendo.getNegativo())
	{
		if(!divisor.getNegativo())
			cociente.setNegativo(true);
	}
	else if(divisor.getNegativo())
		cociente.setNegativo(true);
		
	return cociente;
}

//Funcion miembro utilitaria que define la operacion basica de la resta
BigInteger OperBigInteger::operarResta(const BigInteger &numA, const BigInteger &numB){
	unsigned int  n1, n2, sumTemp, sobrante;
	stack<int> pilaMayor, pilaMenor, pilaResultado, temp;
	string resultadoTexto;
	bool signoNegativo= false;
	BigInteger resultado("0");
	long long int nA= 0, nB= 0;
	
	//Tomamos los valores absolutos de los numeros
	nA= labs(stoll(numA.getNumero()));
	nB= labs(stoll(numB.getNumero()));
	
	if(nA == nB)
		return resultado;		//si son iguales se retorna inmediatamente el resultado
	else if(nA > nB)
	{
		pilaMayor= numA.getPilaNumero();
		pilaMenor= numB.getPilaNumero();
	}
	else
	{
		pilaMayor= numB.getPilaNumero();
		pilaMenor= numA.getPilaNumero();
		signoNegativo= true;
	}

	//Luego de tener las pilas ya seleccionadas, realizamos complemento a 1
	//para la pilaMenor y sumamos
	if(!(pilaMenor.size() == 1 && pilaMenor.top() == 0))
	{
		temp= this->complementoUno(pilaMenor, pilaMayor.size());
		pilaMenor= temp;
	}
	
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

	
	//Llevamos la pila resultado a una cadena de texto
	while(!pilaResultado.empty())
	{
		resultadoTexto+= to_string(pilaResultado.top());
		pilaResultado.pop();
	}
	
	if(resultadoTexto != "0")
	{
		resultado.setNumero(resultadoTexto);	//Se asigna el numero, con o sin signo
		resultado.setNegativo(signoNegativo);
	}
	else
		resultado.setNumero("0");
	
	return resultado;	//Retorna el objeto BigInteger
}

BigInteger OperBigInteger::operarDivision(const BigInteger &numA, const BigInteger &numB){
	BigInteger cociente("0"), dividendo= numA, divisor= numB;
	const BigInteger uno("1");
	long long int nA= labs(stoll(numA.getNumero())), nB= labs(stoll(numB.getNumero()));
	
	dividendo.setNegativo(false);
	divisor.setNegativo(false);
	
	while(nA >= nB)
	{
		dividendo= this->restar(dividendo, divisor);
		cociente= this->sumar(cociente, uno);
		
		nA= stoll(dividendo.getNumero());
		nB= stoll(divisor.getNumero());
	}
	
	return cociente;
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

//Funcion utilitaria que lleva el contenido de una pila de enteros
//	a un vector de numeros enteros
vector<int> OperBigInteger::pilaToVector(stack<int> pila){
	vector<int> vectorNumeros;
	
	//Asignamos cada elemento de la pila al vector
	while(!pila.empty())
	{
		vectorNumeros.push_back(pila.top());
		pila.pop();
	}

	return vectorNumeros;	//Termina funcion retornando el vectorNumeros
}
