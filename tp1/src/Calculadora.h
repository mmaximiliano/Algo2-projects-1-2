#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H
#include "Instruccion.h"
#include "Programa.h"
#include <stack>

class Calculadora {
public:
    // Precondición: la operación es PUSH
    Calculadora(Programa programa);
    void asignarVariable(Id idVariable, int valor);
    void ejecutar(Id idRutina);
    int valorVariable(Id idVariable) const;


private:
    struct variable{
        Id var;
        int val;
    };
    vector<variable> memoria;
    Programa prog;
    void hacerInstruccion(Instruccion instruc, Id &idRutina, int &i);
    stack<int> pila;
};


#endif //SOLUCION_CALCULADORA_H

