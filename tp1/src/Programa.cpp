#include "Programa.h"

Programa::Programa() {

}

void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion){

    int i = 0;
    while (i<rutinas.size() and rutinas[i].nombRutina != idRutina){
        i++;
    }

    if (i==rutinas.size()){
        rutinas.push_back({idRutina,{instruccion}});
    }else{
        rutinas[i].inst.push_back(instruccion);
    }
}

bool Programa::esRutinaExistente(Id idRutina) const{
    int i = 0;
    while (i<rutinas.size() and rutinas[i].nombRutina != idRutina){
        i++;
    }

    bool res = false;

    if (i!=rutinas.size()){
        res = true;
    }
    return res;
}

int Programa::longitud(Id idRutina) const{
    int i = 0;
    while (i<rutinas.size() and rutinas[i].nombRutina != idRutina){
        i++;
    }

    return rutinas[i].inst.size();
}

Instruccion Programa::instruccion(Id idRutina, int i) const{
    int j = 0;
    while (j<rutinas.size() and rutinas[j].nombRutina != idRutina){
        j++;
    }

    return rutinas[j].inst[i];
}