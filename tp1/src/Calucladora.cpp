#include "Calculadora.h"


Calculadora::Calculadora(Programa programa){
    prog=programa;
}

void Calculadora::asignarVariable(Id idVariable, int valor){
    int i = 0;
    while (i<memoria.size() and memoria[i].var != idVariable){
        i++;
    }

    if (i==memoria.size()){
        memoria.push_back({idVariable,valor});
    }else{
        memoria[i].val = valor;
    }
}

void Calculadora::ejecutar(Id idRutina) {
    bool res = prog.esRutinaExistente(idRutina);
    if (res) {
        int i = 0;
        while (i < prog.longitud(idRutina) and res) {
            Instruccion instruc = prog.instruccion(idRutina, i);
            hacerInstruccion(instruc, idRutina, i);
            i++;
            res = prog.esRutinaExistente(idRutina);
        }
    }
}

void Calculadora::hacerInstruccion(Instruccion instruc, Id &idRutina, int &i) {
    if (instruc.operacion() == PUSH) {
        pila.push(instruc.valor());
    }

    if (instruc.operacion() == ADD) {
        if (pila.size() == 1){
            int ult = pila.top();
            pila.pop();
            int ant = 0;
            pila.push(ant + ult);
        }else if(pila.size() >= 2){
            int ult = pila.top();
            pila.pop();
            int ant = pila.top();
            pila.pop();
            pila.push(ant + ult);
        } else if (pila.empty()) {
            pila.push(0);
        }
    }

    if (instruc.operacion() == SUB) {
        if (pila.size() == 1){
            int ult = pila.top();
            pila.pop();
            int ant = 0;
            pila.push(ant - ult);
        }else if (pila.size() >= 2) {
            int ult = pila.top();
            pila.pop();
            int ant = pila.top();
            pila.pop();
            pila.push(ant - ult);
        } else if (pila.empty()) {
            pila.push(0);
        }
    }

    if (instruc.operacion() == MUL) {
        if (pila.size() == 1){
            int ult = pila.top();
            pila.pop();
            int ant = 0;
            pila.push(ant * ult);
        }else if (pila.size() >= 2) {
            int ult = pila.top();
            pila.pop();
            int ant = pila.top();
            pila.pop();
            pila.push(ant * ult);
        } else if (pila.empty()) {
            pila.push(0);
        }
    }

    if (instruc.operacion() == WRITE) {
        int j = 0;
    while (j < memoria.size() and memoria[j].var != instruc.nombre()) {
        j++;
    }
    if (j == memoria.size()) {
        memoria.push_back({instruc.nombre(), instruc.valor()});
    }
    if (pila.size() > 0) {
        memoria[j].val = pila.top();
        pila.pop();
    } else {
        memoria[j].val = 0;
    }

}

    if (instruc.operacion() == READ) {
        int j = 0;
        while (j < memoria.size() and memoria[j].var != instruc.nombre()) {
            j++;
        }
        if (j < memoria.size()) {
            pila.push(memoria[j].val);
        } else {
            pila.push(0);
        }
    }

    if (instruc.operacion() == JUMP) {
        bool res = prog.esRutinaExistente(instruc.nombre());

        if (res) {
            idRutina = instruc.nombre();
            i = -1;
        } else {
            i = prog.longitud(idRutina);
        }
    }
    if (instruc.operacion() == JUMPZ) {
        bool res = prog.esRutinaExistente(instruc.nombre());
        if (res) {
            if (!pila.empty()) {
                int top = pila.top();
                pila.pop();
                if(top== 0) {
                    idRutina = instruc.nombre();
                    i = -1;
                }
            }else if(pila.empty()){
                idRutina = instruc.nombre();
                i = -1;
            }
        } else {
            i = prog.longitud(idRutina);
        }

    }

}

int Calculadora::valorVariable(Id idVariable) const {
    int i = 0;
    while (i < memoria.size() and memoria[i].var != idVariable) {
        i++;
    }

    if (i == memoria.size()) {
        return 0;
    } else {
        return memoria[i].val;
    }
}
