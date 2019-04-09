#include "gtest/gtest.h"
#include "../src/Programa.h"


TEST(test_programa, programa_vacio) {
    Programa p = Programa();
    list<rutina> vacio;
    ASSERT_EQ(p.rutinas(), vacio);
    ASSERT_EQ(p.rutinas().size(), 0);
}



TEST(test_programa, programa_1rut) {
    Programa p = Programa();
    Instruccion i = Instruccion(PUSH, 25);
    rutina A = "A";
    p.agregarInstruccion(A, i);
    list<rutina> unaSola;
    unaSola.push_back(A);
    ASSERT_EQ(p.rutinas(), unaSola);
    ASSERT_EQ(p.rutinas().size(), 1);
}



TEST(test_programa, programa_1rut_variasInstrucciones) {
    Programa p = Programa();
    Instruccion i = Instruccion(PUSH, 25);
    Instruccion j = Instruccion(PUSH, 14);
    Instruccion k = Instruccion(ADD);
    Instruccion l = Instruccion(PUSH, 75);
    Instruccion m = Instruccion(MUL);
    Instruccion n = Instruccion(PUSH, 342);
    Instruccion o = Instruccion(SUB);

    rutina A = "A";
    p.agregarInstruccion(A, i);
    p.agregarInstruccion(A, j);
    p.agregarInstruccion(A, k);
    p.agregarInstruccion(A, l);
    p.agregarInstruccion(A, m);
    p.agregarInstruccion(A, n);
    p.agregarInstruccion(A, o);
    vector<Instruccion> InstrPosta;
    InstrPosta.push_back(i);
    InstrPosta.push_back(j);
    InstrPosta.push_back(k);
    InstrPosta.push_back(l);
    InstrPosta.push_back(m);
    InstrPosta.push_back(n);
    InstrPosta.push_back(o);
    vector<Instruccion> InstrATestear = p.buscarRutina(A);
    ASSERT_EQ(p.cantInstruccionesRutinaR(A), InstrPosta.size());
    ASSERT_EQ(p.rutinas().size(), 1);
    for (int i = 0; i < InstrPosta.size(); i++) {
        ASSERT_EQ(InstrPosta[i].op(), InstrATestear[i].op());
    }
}



TEST(test_programa, programa_2rut) {
    Programa p = Programa();
    Instruccion i = Instruccion(PUSH, 25);
    Instruccion j = Instruccion(ADD);
    rutina A = "A";
    p.agregarInstruccion(A, i);

    Instruccion t = Instruccion(PUSH, 50);
    rutina B = "B";
    p.agregarInstruccion(B, t);


    p.agregarInstruccion(A, i);
    list<rutina> dosRutinas;
    dosRutinas.push_back(A);
    dosRutinas.push_back(B);
    ASSERT_EQ(p.rutinas(), dosRutinas);
    ASSERT_EQ(p.rutinas().size(), 2);
    ASSERT_EQ(p.cantidadRutinas(), 2);
}

