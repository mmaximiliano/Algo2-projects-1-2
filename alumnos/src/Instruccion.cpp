#include "Instruccion.h"

const Operacion &Instruccion::op() const {
    return _op;
}


const int &Instruccion::valorPush() const {
    return _valor;
}


const variable &Instruccion::nombreVariable() const {
    return _var;
}


const rutina &Instruccion::nombreRutina() const {
    return _rut;
}


Instruccion::Instruccion(const Operacion &oper, int n) {
    _op = oper;
    _valor = n;
    _rut ="";
    _var ="";
}


Instruccion::Instruccion(const Operacion &oper) {
    _op = oper;
    _valor = 0;
    _rut ="";
    _var ="";
}


Instruccion::Instruccion(const Operacion &oper, const string &nombre) {
    if (oper == READ || oper == WRITE) {
        _op = oper;
        _var = nombre;
        _rut = "";

    } else {  // if (oper == JUMP || oper == JUMPZ)
        _op = oper;
        _rut = nombre;
        _var = "";
    }

    _valor =0;
}