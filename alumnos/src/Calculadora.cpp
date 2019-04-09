#include "Calculadora.h"
#include <iostream>


// Constructor
Calculadora::Calculadora(Programa &p, const rutina &r, nat w) {

    const list<rutina> &rutinasDeP = p.rutinas();
    _estadoActual.instanteActual = 0;
    _pila = stack<int>();
    _variables = string_map<datosVariable>();
    _rutinas = string_map<infoRutina>();
    _instrucciones = vector<infoInstruc>();
    _indiceInstrucActual = 0;
    list<tuple<nat, variable> > vars = list<tuple<nat, variable> >();    // Se asume que la lista se construye vacia
    nat empieza = 0;


    bool rutinaEsta = false;
    nat i = 0;
    for (auto &rutCompleta : rutinasDeP) {

        //rutina rutCompleta = (rutinasDeP)[i];
        rutina *punt = new rutina(rutCompleta);
        infoRutina cont = infoRutina(punt, empieza, empieza + p.cantInstruccionesRutinaR(rutCompleta) - 1);
        _rutinas[rutCompleta] = cont;

        if (rutCompleta == r) {
            rutinaEsta = true; //Chequeo que la rutina que me pasaron por parametro exista, si no es asi, finalizo se marca como true;
            _indiceProxInstruc = empieza;
            _estadoActual.rutActual = &_rutinas.at(r);
            _estadoActual.terminaRut = empieza + p.cantInstruccionesRutinaR(rutCompleta) - 1;

        } else {
            // No hacer nada
        }

        empieza += p.cantInstruccionesRutinaR(rutCompleta);
        i++;
    }
    _estadoActual.finalizo = !rutinaEsta;


    int t = 0;
    for (auto &rutinaActual : rutinasDeP) {
        //Pequeño cambio respecto de TP2, la complejidad de esto sigue siendo O(#p(|V|+|R|) + W.#V)
        nat k = 0;

        while (k < p.cantInstruccionesRutinaR(rutinaActual)) {

            Instruccion instruccionActual = p.iesimaInstruccion(rutinaActual, k);
            if (instruccionActual.op() == JUMP || instruccionActual.op() == JUMPZ) {
                rutina rutinaASaltar = instruccionActual.nombreRutina();

                if (_rutinas.count(rutinaASaltar) > 0) {
                    int emp = _rutinas.at(rutinaASaltar).empieza;
                    infoRutina *punt = &(_rutinas.at(rutinaASaltar));
                    infoInstruc instruccionCompilada = infoInstruc(instruccionActual, true, punt, nullptr, emp);
                    _instrucciones.push_back(instruccionCompilada);

                } else {
                    infoInstruc instruccionCompilada = infoInstruc(instruccionActual, false, nullptr, nullptr, 0);
                    _instrucciones.push_back(instruccionCompilada);
                }

            } else if (instruccionActual.op() == READ || instruccionActual.op() == WRITE) {

                vars.push_back(make_tuple(t, instruccionActual.nombreVariable()));
                infoInstruc instruccionCompilada = infoInstruc(instruccionActual, true, nullptr, nullptr, 0);
                _instrucciones.push_back(instruccionCompilada);

            } else { // Para cualquier otra operacion

                infoInstruc instruccionCompilada = infoInstruc(instruccionActual, true, nullptr, nullptr, 0);
                _instrucciones.push_back(instruccionCompilada);
            }
            t++;
            k++;
        }

    }


    i = 0;
    while (!vars.empty()) {
        variable v = get<1>(vars.front());

        if (_variables.count(v) == 0) {
            Ventana<infoVar> *punV = new Ventana<infoVar>(w);
            list<infoVar> lista = list<infoVar>();
            datosVariable nuevo = datosVariable();
            nuevo.pVent = punV;
            nuevo.historialCompleto = lista;

            _variables[v] = nuevo;

        } else {
            // No hacer nada
        }

        datosVariable *punt = &(_variables.at(v));
        _instrucciones[get<0>(vars.front())].pVar = punt;
        vars.pop_front();
    }

    /*
     * Lo siguiente fue comentado ya que nos dimos cuenta que es ineficiente e innecesario, porque se puede usar el
     * puntero al significado del trie de variables el cual contiene la posicion donde empezaria la rutina en el vector instrucciones.
     * Por lo tanto esto puede ser omitido también en el TP2.

    i = 0;
    while (i < p.cantidadRutinas()) {
        nat k = 0;
        rutina rutinaActual = rutinasDeP[i];

        while (k < p.cantInstruccionesRutinaR(rutinaActual)) {
            Instruccion instruccionActual = p.iesimaInstruccion(rutinaActual, k);

            if ((instruccionActual.op() == JUMP || instruccionActual.op() == JUMPZ) && _instrucciones.operator[](i)->condicion == true ) {
                nat pos = _rutinas.at(instruccionActual.nombreRutina())->empieza;
                _instrucciones[i]->proxRut = pos;

            } else {
                _instrucciones[i]->proxRut = i + 1;
            }

            k++;
        }

        i++;
    }
    */

}



// Destructor
Calculadora::~Calculadora() {

    const list<rutina> rutinas = _rutinas.claves();
    for (auto &it: rutinas) {
        delete _rutinas[it].pPal;
    }
}



// Finalizo?
bool Calculadora::finalizo() const {

    return _estadoActual.finalizo;
}



// Ejecutar una instruccion
void Calculadora::ejecutarUnPaso() {

    infoInstruc i = _instrucciones[_indiceProxInstruc];

    if (i.instruccion.op() == ADD) {

        if (_pila.empty()) {
            _pila.push(0);

        } else if (_pila.size() == 1) {
            // Nada

        } else {
            int a = _pila.top();
            _pila.pop();
            int b = _pila.top();
            _pila.pop();
            _pila.push(a + b);
        }

        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == SUB) {

        if (_pila.empty()) {
            _pila.push(0);

        } else if (_pila.size() == 1) {
            int a = _pila.top();
            _pila.pop();
            _pila.push(-a);

        } else {
            int a = _pila.top();
            _pila.pop();
            int b = _pila.top();
            _pila.pop();
            _pila.push(b - a);
        }

        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == MUL) {

        if (_pila.empty()) {
            _pila.push(0);

        } else if (_pila.size() == 1) {
            int a = _pila.top();
            _pila.pop();
            _pila.push(0);

        } else {
            int a = _pila.top();
            _pila.pop();
            int b = _pila.top();
            _pila.pop();
            _pila.push(a * b);
        }

        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == PUSH) {

        int a = i.instruccion.valorPush();
        _pila.push(a);
        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == READ) {

        Ventana<infoVar> *ventActual = i.pVar->pVent;
        if (i.pVar->pVent == nullptr || ventActual->tam() == 0) {
            _pila.push(0);

        } else {
            int a = ventActual->operator[](ventActual->tam() - 1).valor;
            _pila.push(a);

        }

        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == WRITE) {

        list<infoVar> &historialDeX = i.pVar->historialCompleto;
        infoVar j;

        if (_pila.empty()) {
            j.instante = _estadoActual.instanteActual;
            j.valor = 0;

        } else {
            j.instante = _estadoActual.instanteActual;
            j.valor = _pila.top();
            _pila.pop();
        }

        if (historialDeX.empty() || historialDeX.back().instante != _estadoActual.instanteActual) {
            i.pVar->pVent->registrar(j);
            historialDeX.push_back(j);

        } else {
            historialDeX.back().valor = j.valor;
            i.pVar->pVent->operator[](i.pVar->pVent->tam() - 1).valor = j.valor;
        }

        _indiceProxInstruc++;
        _indiceInstrucActual++;


    } else if (i.instruccion.op() == JUMP) {

        if (i.condicion == false) { // Checkeo que la rutina no exista para ver si termina mi ejecucion.
            _estadoActual.finalizo = true;

        } else { //Sino, salto.
            _estadoActual.rutActual = i.pRut;
            _indiceProxInstruc = i.pRut->empieza;
            _estadoActual.terminaRut = i.pRut->termina;
            _indiceInstrucActual = 0;
        }


    } else if (i.instruccion.op() == JUMPZ) {

        if (_pila.empty() || _pila.top() == 0) {

            if (i.condicion == false) {// Checkeo que la rutina no exista para ver si termina mi ejecucion.
                _estadoActual.finalizo = true;

            } else {  //Sino, salto.
                _estadoActual.rutActual = i.pRut;
                _indiceProxInstruc = i.pRut->empieza;
                _estadoActual.terminaRut = i.pRut->termina;
                _indiceInstrucActual = 0;
            }

        } else {
            _indiceProxInstruc++;
            _indiceInstrucActual++;
        }

        if (!_pila.empty()) {
            _pila.pop();
        }
    }
    _estadoActual.instanteActual++;

    if (_indiceProxInstruc - 1 == _estadoActual.terminaRut) {
        _estadoActual.finalizo = true;
    }

}



// Asignar valor a variable
void Calculadora::asignarVariable(const variable &x, int n) {

    infoVar nueva = infoVar();
    nueva.instante = _estadoActual.instanteActual;
    nueva.valor = n;

    if (_variables.count(x) > 0) {              // Me fijo si la variable esta definida en el TRIE.
        datosVariable &d = _variables.at(x);    // En el TP2 decia 'int d', el tipo correcto es datosVariable.

        if (d.historialCompleto.size() > 0 && (d.historialCompleto.back()).instante == _estadoActual.instanteActual) {
            (d.historialCompleto.back()).valor = n;

        } else {
            d.historialCompleto.push_back(nueva);
        }

        if (d.pVent != nullptr) {
            Ventana<infoVar> &v = *(d.pVent);

            if (v.tam() > 0 && v[v.tam() - 1].instante == _estadoActual.instanteActual) {
                v[v.tam() - 1].valor = n;

            } else {
                v.registrar(nueva);

            }

        } else {
            //No hacer Nada.
        }

    } else {                          //Si no está definido en el TRIE, es porque no está en el código fuente y por lo tanto cuando lo defina no tendrá Ventana propia.
        Ventana<infoVar> *punt = nullptr;       // En el TP2 decia 'Ventana<int>*', el tipo correcto es Ventana<infoVar>*.
        list<infoVar> lista = list<infoVar>();  // Se asume que la lista se construye vacia
        lista.push_back(nueva);

        datosVariable aDefinir = datosVariable();   // En el TP2 decía int, el tipo correcto es el actual.
        aDefinir.pVent = punt;
        aDefinir.historialCompleto = lista;

        _variables[x] = aDefinir;
    }

}



// Instante actual
nat Calculadora::instanteActual() const {

    return _estadoActual.instanteActual;
}



// Rutina actual
const rutina &Calculadora::rutinaActual() const {

    return *(_estadoActual.rutActual->pPal);
}



// Indice de Instruccion actual
nat Calculadora::indiceInstruccionActual() const {

    return _indiceInstrucActual;
}



// Valor historico de variable
int Calculadora::valorVariableATiempoDado(variable &x, nat t) const {

    int res = 0;
    if (_variables.at(x).pVent != nullptr) {    //Checkeo que la variable tenga ventana.

        Ventana<infoVar> &v = *(_variables.at(x).pVent);

        int w = _variables.at(x).pVent->capacidad();

        int ultInstModificado = 0;
        if (v.tam() > 0) {
            ultInstModificado = v[v.tam() - 1].instante;

            if (_variables.at(x).pVent != nullptr && ultInstModificado - w < t && t <= ultInstModificado) { //Me fijo si el instante t esta entre los que guarda la ventana. Caso afirmativo, hago busqueda binaria.
                res = binaryT(*(_variables.at(x).pVent), t);

            } else { //De lo contrario, busco en el Historial.

                auto it = _variables.at(x).historialCompleto.end();
                it--;
                while (it != _variables.at(x).historialCompleto.begin() && (*it).instante > t) {
                    --it;
                }

                if (it->instante > t) {
                    res = 0;

                } else {
                    res = (*it).valor;
                }
            }

        } else {
            res = 0;
        }

    } else {     //Caso en que la variable no tiene ventana: solo puedo buscar en el historial.
        const list<infoVar> &historialDeX = _variables.at(x).historialCompleto;
        if (historialDeX.size() > 0) {

            auto it = historialDeX.end();
            it--;
            while (it != historialDeX.begin() && (*it).instante > t) {
                --it;
            }

            if (it->instante > t) {
                res = 0;

            } else {
                res = (*it).valor;
            }

        } else {
            //No hacer Nada.
        }
    }

    return res;
}



// Valor actual de variable
int Calculadora::valorVariableActual(variable &x) const {

    int res = 0;
    const list<infoVar> &historialDeX = _variables.at(x).historialCompleto;

    if (historialDeX.size() > 0) {  //Si la variable fue inicializada en algun momento, devuelvo el ultimo elemento de la lista.

        auto it = historialDeX.end();
        --it;
        res = (*it).valor;

    } else {
        //Caso contrario, al no haber sido inicializada, devuelvo 0.
    }

    return res;
}



// Estado de la pila
const stack<int> &Calculadora::pila() const {

    return _pila;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //



// Funcion auxiliar: busqueda binaria para ventanas
int Calculadora::binaryT(const Ventana<infoVar> &w, nat t) const {

    int res = 0;
    if (w.tam() == 0) {
        // No hacer nada, se devuelve 0
    } else if (w.tam() == 1 && w[0].instante > t) {
        res = 0;


    } else if (w[w.tam() - 1].instante <= t) {
        res = w[w.tam() - 1].valor;

    } else {

        nat low = 0;
        nat high = w.tam() - 1;

        while (low + 1 < high && w[low].instante != t) {
            nat mid = low + (high - low) / 2;
            if (w[mid].instante <= t) {
                low = mid;
            } else {
                high = mid;
            }
        }

        res = w[low].valor;

    }

    return res;
}
