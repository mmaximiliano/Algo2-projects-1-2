#include "Driver.h"


Driver::Driver() {
    prog = Programa();
}



Driver::~Driver() {
    delete calculadora;
}



void Driver::begin(string rutina) {
    ultRut = rutina;
}



void Driver::end(string rutina) {

}



void Driver::push(int n) {
    Instruccion iPush = Instruccion(PUSH, n);
    prog.agregarInstruccion(ultRut, iPush);

}



void Driver::add() {
    Instruccion iAdd = Instruccion(ADD);
    prog.agregarInstruccion(ultRut, iAdd);
}



void Driver::sub() {
    Instruccion iSub = Instruccion(SUB);
    prog.agregarInstruccion(ultRut, iSub);
}



void Driver::mul() {
    Instruccion iMul = Instruccion(MUL);
    prog.agregarInstruccion(ultRut, iMul);
}



void Driver::read(string variable) {
    Instruccion iRead = Instruccion(READ, variable);
    prog.agregarInstruccion(ultRut, iRead);
}



void Driver::write(string variable) {
    Instruccion iWrite = Instruccion(WRITE, variable);
    prog.agregarInstruccion(ultRut, iWrite);
}



void Driver::jump(string rutina) {
    Instruccion iJump = Instruccion(JUMP, rutina);
    prog.agregarInstruccion(ultRut, iJump);
}



void Driver::jumpz(string rutina) {
    Instruccion iJumpZ = Instruccion(JUMPZ, rutina);
    prog.agregarInstruccion(ultRut, iJumpZ);
}


// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
    calculadora = new Calculadora(prog, rutina, capacidadVentana);

}



void Driver::asignarVariable(string x, int valor) {
    calculadora->asignarVariable(x, valor);
}



bool Driver::ejecucionFinalizada() const {
    return calculadora->finalizo();
}



void Driver::ejecutarInstruccionActual() {
    calculadora->ejecutarUnPaso();
}



int Driver::topePila() const {
    int tope = 0;

    if (!calculadora->pila().empty()) {
        tope = calculadora->pila().top();
    } else {
        // Devuelve 0
    }

    return tope;
}



int Driver::valorVariable(string x) const {
    return calculadora->valorVariableActual(x);
}



int Driver::valorHistoricoVariable(string x, int t) const {
    return calculadora->valorVariableATiempoDado(x, t);
}



int Driver::instanteActual() const {
    return calculadora->instanteActual();
}


