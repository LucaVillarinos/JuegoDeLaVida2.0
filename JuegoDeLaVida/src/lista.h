/*
 * lista.h
 *
 *  Created on: Dec 3, 2020
 *      Author: francisco
 */

#ifndef LISTA_H_
#define LISTA_H_


#ifndef NODO
#define NODO
#include "nodo.h"
#endif


#ifndef IMPRESION
#define IMPRESION
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
#endif

/*
 * Template de lista simplemente
 * enlazada con cursor
 *
 */
template <typename Type> class Lista{

private:

	Nodo<Type>* head;

	Nodo<Type>* cursor;

	unsigned int tamanio;

	unsigned int posicionActual;

	/*
	 * Post: Libera la memoria de todos
	 * los nodos de la lista
	 */
	void liberar(Nodo<Type>* actual);

	/*
	 * Post: Verifica que la posicion
	 * sea valida
	 */
	bool posicionValida(int posicion);

	/*
	 * Pre: La posicion debe ser valida y el cursor
	 * debe estar apuntando al head
	 * Post: inserta al elemento en la posicion dada
	 */
	void insertarElemento(Type valor, int posObjetivo);

	/*
	 * Pre: La posicion debe ser valida y el cursor apuntar
	 * al head
	 * post: elimina al elemento en la posicion i de la
	 * lista
	 */
	void eliminarElemento(int posObjetivo);

	/*
	 * pre: La lista no puede estar vacia
	 * Post: Elimina al primer elemento de la lista
	 */
	void eliminarPrimero();

	/*
	 * Post: Dirije el cursor al
	 * head
	 */
	void apuntarHead();

	/*
	 * Post: Mueve el cursor
	 * a la derecha, si la posicion
	 * es la ultima, lo devuelve
	 * al head
	 */
	void avanzarCursor();

	/*
	 * Pre: La posicion debe estar en el rango
	 * Post: Apunta el cursor a la posicion pasada
	 * por parametro
	 */
	void moverCursor(int posicion);


public:

	/*
	 * Post: Crea una lista con
	 * un elemento
	 */
	Lista(Type valor);

	/*
	 * Post: Crea una lista vacia
	 */
	Lista();

	/*
	 * Post:---
	 */
	~Lista();

	/*
	 * Pre: La posicion debe ser valida
	 * (Estar entre 0 y tamano)
	 * Post: Agrega al elemento en la posicion
	 * especificada
	 */
	void insertar(Type valor, int posicion);

	/*
	 * Post: Devuelve la cantidad de
	 * elementos de la lista
	 */
	unsigned int longitud();

	/*
	 * Post: Agrega el elemento al
	 * final de la lista
	 */
	void append(Type valor);

	/*
	 * Post: Agrega al elemento al
	 * principio de la lista
	 */
	void push(Type valor);

	/*
	 * Post: Elimina al elemento
	 * de la lista, solo la primer
	 * aparicion.
	 * Si no esta en la lista, no hace nada
	 */
	void pop(Type valor);

	/*
	 * pre: La posicion debe ser valida
	 * post: Elimina al elemento de
	 * la posicion i
	 */
	void remove(int posicion);

	/*
	 * Post: Imprime la lista en orden
	 */
	void imprimir();

	/*
	 * Pre: La posicion debe ser valida
	 * Post: Devuelve una referencia a la posicion indicada
	 * (a el nodo de esa posicion)
	 *
	 */
	 Type operator[](int posicion);

};

template <class Type>
Lista<Type>::Lista(){

	head = NULL;

	cursor = NULL;

	tamanio = 0;

	posicionActual = -1;

}

template <class Type>
Lista<Type>::Lista(Type valor){

	head = new Nodo<Type>(valor);

	cursor = head;

	posicionActual = 0;

	tamanio = 1;



}

template <class Type>
Lista<Type>::~Lista(){

	if(head){
		liberar(head);
	}

}

template <class Type>
void Lista<Type>::insertar(Type valor, int posicion){

	if(posicion != tamanio && !(posicionValida(posicion))){
		throw string("POSICION INVALIDA");
	}

	if(posicion == 0){
		push(valor);
	}
	else{
		insertarElemento(valor, posicion);
	}
}

template <class Type>
void Lista<Type>::append(Type valor){

	insertarElemento(valor, tamanio);
}

template <class Type>
void Lista<Type>::push(Type valor){

	Nodo<Type>* nuevo = new Nodo<Type>(valor, head);

	head = nuevo;
	apuntarHead();
	tamanio++;
}

template <class Type>
void Lista<Type>::pop(Type valor){

	cursor = head;

	if (head->getValue() == valor){
		eliminarPrimero();
	}
	else{
		while(cursor->getNext() &&
				cursor->getNext()->getValue() != valor){

			cursor = cursor->getNext();

		}
		if(cursor){
			Nodo<Type>* auxiliar = cursor->getNext();

			cursor->setNext(auxiliar->getNext());

			delete auxiliar;
			tamanio--;
		}
	}

}

template <class Type>
void Lista<Type>::remove(int posicion){

	if(!(posicionValida(posicion))){
		throw string("POSICION INVALIDA");
	}

	if(posicion == 0){
		eliminarPrimero();
	}
	else{
		eliminarElemento(posicion);
	}

}

template <class Type>
void Lista<Type>::imprimir(){

	cursor = head;
	while(cursor){
		cout << cursor->getValue() << "->";
		cursor = cursor->getNext();
	}
	cout << endl;

}

template <class Type>
unsigned int Lista<Type>::longitud(){

	return tamanio;
}

template <class Type>
Type Lista<Type>::operator[](int posicion){

	if(!posicionValida(posicion)){
		throw string("POSICION INVALIDA");
	}

	moverCursor(posicion);

	return (this->cursor->getValue());

}

/*
 * Metodos privados
 */
template <class Type>
void Lista<Type>::liberar(Nodo<Type>* actual){

	if(actual->getNext()){

		liberar(actual->getNext());

	}
	delete actual;

}

template <class Type>
bool Lista<Type>::posicionValida(int posicion){

	return ((posicion >= 0) && (posicion < tamanio));
}

template <class Type>
void Lista<Type>::insertarElemento(Type valor, int posFinal){

	moverCursor(posFinal-1);


	Nodo<Type>* nuevo = new Nodo<Type>(valor, cursor->getNext());

	cursor->setNext(nuevo);
	tamanio++;




}

template <class Type>
void Lista<Type>::eliminarElemento(int posObjetivo){


	moverCursor(posObjetivo-1);
	Nodo<Type>* auxiliar = cursor->getNext();

	cursor->setNext(auxiliar->getNext());
	delete auxiliar;
	tamanio--;

}

template <class Type>
void Lista<Type>::eliminarPrimero(){

	Nodo<Type>* nuevoHead = head->getNext();

	delete head;
	head = nuevoHead;
	tamanio--;
	apuntarHead();

}

template <class Type>
void Lista<Type>::apuntarHead(){

	cursor = head;
	posicionActual = 0;

}

template <class Type>
void Lista<Type>::avanzarCursor(){

	cursor = cursor->getNext();

	posicionActual++;
}

template <class Type>
void Lista<Type>::moverCursor(int posicion){

	if(posicionActual > posicion){
		apuntarHead();
	}
	while(posicionActual != posicion){
		avanzarCursor();
	}

}

#endif /* LISTA_H_ */
