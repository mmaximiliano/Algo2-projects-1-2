#include "Programa.h"

Programa::Programa() {

    _rutinas = string_map<vector<Instruccion> >();
}


void Programa::agregarInstruccion(const rutina &r, const Instruccion &i) {

    if (_rutinas.count(r) == 0){    //Si la rutina no esta en el Trie, se la agrega.
        vector<Instruccion> v = vector<Instruccion>();
        _rutinas[r] = v;
    }

    vector<Instruccion>& j = _rutinas.at(r);
    j.push_back(i);           //Agrega la instruccion al final de la rutina
}


const list<rutina>& Programa::rutinas() const {

    return _rutinas.claves(); //Devuelve un vector con todos los nombres de las rutinas.
}


nat Programa::cantidadRutinas() const {

    return _rutinas.size();
}


const vector<Instruccion> &Programa::buscarRutina(const rutina &r) const {

    return _rutinas.at(r);
}


nat Programa::cantInstruccionesRutinaR(const rutina &r) const {

    return _rutinas.at(r).size();
}


const Instruccion &Programa::iesimaInstruccion(const rutina &r, nat i) const {

    return (_rutinas.at(r).operator[](i));
}
