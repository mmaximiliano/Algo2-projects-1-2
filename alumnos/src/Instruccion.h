#ifndef SOLUCION_INSTRUCCION_H
#define SOLUCION_INSTRUCCION_H


#include "Utiles.h"

using namespace std;


class Instruccion {

public:

    //Indica que operacion corresponde a la instruccion
    const Operacion &op() const;

    //Indica el valor a pushear si la instruccion es PUSH
    const int &valorPush() const;

    //Indica el nombre de la variable a leer o modificar si la instruccion es READ o WRITE
    const variable &nombreVariable() const;

    //Indica el nombre de la rutina a la que se salta, si la instruccion es JUMP o JUMPZ
    const rutina &nombreRutina() const;

    // Constructor. Precondición: la operación es PUSH
    Instruccion(const Operacion &oper, int n);

    // Constructor. Precondición: la operación es ADD, SUB o MUL
    Instruccion(const Operacion &oper);

    // Constructor. Precondición: la operación es READ o WRITE, o bien JUMP o JUMPZ
    Instruccion(const Operacion &oper, const string &nombre);


private:

    Operacion _op;

    int _valor;

    variable _var;

    rutina _rut;

};


#endif //SOLUCION_INSTRUCCION_H
