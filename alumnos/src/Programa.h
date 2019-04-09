#ifndef SOLUCION_PROGRAMA_H
#define SOLUCION_PROGRAMA_H

#include "string_map.h"
#include "Instruccion.h"

using namespace std;


class Programa {

public:

    // Constructor por defecto
    Programa();

    // Agrega la instruccion i a la rutina r. Si esta no existe, la crea
    void agregarInstruccion(const rutina &r, const Instruccion &i);

    // Devuelve el conjunto de rutinas del programa
    const list<rutina> &rutinas() const;

    // Devuelve la cantidad de rutinas del programa
    nat cantidadRutinas() const;

    // Busca la rutina r en el programa
    const vector<Instruccion> &buscarRutina(const rutina &r) const;

    // Indica la cantidad de instrucciones de una rutina del programa
    nat cantInstruccionesRutinaR(const rutina &r) const;

    // Devuelve la instruccion en la posicion i de la rutina r en el programa
    const Instruccion &iesimaInstruccion(const rutina &r, nat i) const;


private:

    string_map<vector<Instruccion> > _rutinas;

};


#endif //SOLUCION_PROGRAMA_H
