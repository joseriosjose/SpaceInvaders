#include <stdio.h>
#include <iostream>
using namespace std;

class nodo {
    public:
    nodo(int x,int y, nodo *sig = NULL) {
       valorX = x;
       valorY = y;
       siguiente = sig;
    }

    public:
    int valorX, valorY;
    nodo *siguiente;

    friend class Pila;
};

typedef nodo *pnodo;

class Pila {
   public:
    Pila() : ultimo(NULL) {}
    ~Pila();

    void push(int x, int y);
    int* pop();
    bool estaVacia();
    void printPila();

   private:
    pnodo ultimo;
};
Pila::~Pila() { /*while(ultimo) pop();*/}

void Pila::push(int x, int y) {
   pnodo nuevo;
   nuevo = new nodo(x, y, ultimo);
   ultimo = nuevo;
}
bool Pila::estaVacia()
{
    return (ultimo == NULL);
}
int* Pila::pop() {
   pnodo nodo;
   if(estaVacia()) {
        throw "Pila vacía, no se puede extraer.";
        return 0;
   }else{
       int * a = new int[2];
       nodo = ultimo;
       a[0] = nodo->valorX;
       a[1] = nodo->valorY;
       ultimo = nodo->siguiente;
       return a;
   }
}
