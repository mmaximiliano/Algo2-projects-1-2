#include "Instruccion.h"

Instruccion::Instruccion(Operacion operacion, int valor){
    operacion_ = operacion;
    valor_ = valor;

}

Instruccion::Instruccion(Operacion operacion){
    operacion_ = operacion;
}

Instruccion::Instruccion(Operacion operacion, Id nombre){
    operacion_ = operacion;
    nombre_ = nombre;

}

Operacion Instruccion::operacion() const{
    return operacion_;
}

int Instruccion::valor() const{
    return valor_;
}

Id Instruccion::nombre() const{
    return nombre_;
}
