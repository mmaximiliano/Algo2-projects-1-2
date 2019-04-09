#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H

#endif //SOLUCION_CALCULADORA_H

#include "string_map.h"
#include "Programa.h"
#include "Ventana.h"

using namespace std;

class Calculadora {

public:

    // Constructor: Inicia una nueva calcluladora, con el programa p cargado, rutina inicial r y capacidad de ventana w
    Calculadora(Programa &p, const rutina &r, nat w);

    // Destructor
    ~Calculadora();

    // Indica si finalizo la ejecucion del programa cargado en la calculadora
    bool finalizo() const;

    // Ejecuta la siguiente instruccion cargada en la rutina actual del programa en la calculadora
    void ejecutarUnPaso();

    // Asigna el valor n a la variable en memoria x; en el caso de no existir dicha variable, la crea y la inicializa con el valor n
    void asignarVariable(const variable &x, int n);

    // Indica el instante de la ejecucion en el que se encuentra la calculadora
    nat instanteActual() const;

    // Dada una calculadora, indica el nombre de la rutina que se este ejecutando
    const rutina &rutinaActual() const;

    // Dada una calculadora, indica el indice (numero natural) de instruccion actual dentro de la rutina que se este ejecutando
    nat indiceInstruccionActual() const;

    // Dada una calculadora, una variable arbitraria y un instante, devuelve el valor de dicha variable en ese instante
    int valorVariableATiempoDado(variable &x, nat t) const;

    // Dada una calculadora y una variable arbitraria, devuelve el valor actual de dicha variable.
    int valorVariableActual(variable &x) const;

    // Indica el estado actual de la pila de la calculadora
    const stack<int> &pila() const;


private:

    // Estructuras que corresponden a las tuplas del TP2:

    struct infoVar {
        nat instante;
        int valor;
    };

    struct datosVariable {
        Ventana<infoVar> *pVent;
        list<infoVar> historialCompleto;

        datosVariable() : pVent(nullptr) {}

        datosVariable(const datosVariable &o) : datosVariable() {
            *this = o;
        }

        datosVariable &operator=(const datosVariable &o) {
            if (o.pVent == nullptr) {
                pVent = nullptr;
            } else {
                pVent = new Ventana<infoVar>(*(o.pVent));
            }
            historialCompleto = o.historialCompleto;
        }

        ~datosVariable() {
            if (pVent != nullptr) {
                delete pVent;
            }
        }
    };

    struct infoRutina {
        rutina *pPal;
        nat empieza;
        nat termina;

        infoRutina() : pPal(nullptr) {}

        infoRutina(rutina *r, nat e, nat t) {
            pPal = r;
            empieza = e;
            termina = t;
        }
    };

    struct estadoCalc {
        infoRutina *rutActual;
        nat terminaRut;
        nat instanteActual;
        bool finalizo;
    };

    struct infoInstruc {
        infoInstruc(Instruccion i, bool cond, infoRutina *infR, datosVariable *d, nat pR) : instruccion(i) {
            condicion = cond;
            pRut = infR;
            pVar = d;
            proxRut = pR;
        }

        Instruccion instruccion;
        bool condicion;
        infoRutina *pRut;    // antes era rutina*. Cambiado para que ande la nueva version de nuevaCalculadora (ver asignacion de punt en segundo while)
        datosVariable *pVar;
        nat proxRut;

    };


    // Representacion interna de Calculadora, a partir de las estructuras intermedias previamente definidas:

    string_map<datosVariable> _variables;

    string_map<infoRutina> _rutinas;

    estadoCalc _estadoActual;

    vector<infoInstruc> _instrucciones;

    nat _indiceInstrucActual;

    nat _indiceProxInstruc;

    stack<int> _pila;


    //Funcion auxiliar: Busca un cierto instante dado en la ventana de una variable, y devuelve el valor que tiene dicha variable en dicho instante
    int binaryT(const Ventana<infoVar> &w, nat t) const;


};

