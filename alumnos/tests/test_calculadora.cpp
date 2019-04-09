#include "gtest/gtest.h"
#include "../src/Calculadora.h"


TEST(test_calculadora, programa_vacio) {
    Programa p = Programa();
    Calculadora c = Calculadora(p,"asd",14);
    ASSERT_EQ(c.finalizo(),true);
    ASSERT_EQ(c.instanteActual(),0);
    ASSERT_EQ(c.pila().empty(),true);
}



TEST(test_calculadora, una_rutina_de_push) {
    Programa p = Programa();

    Instruccion i = Instruccion(PUSH,14);
    Instruccion j = Instruccion(PUSH,15);
    Instruccion k = Instruccion(PUSH,16);
    Instruccion l = Instruccion(PUSH,17);
    Instruccion m = Instruccion(PUSH,18);
    Instruccion n = Instruccion(PUSH,19);
    Instruccion o = Instruccion(PUSH,20);

    rutina A = "A";
    p.agregarInstruccion(A,i);
    p.agregarInstruccion(A,j);
    p.agregarInstruccion(A,k);
    p.agregarInstruccion(A,l);
    p.agregarInstruccion(A,m);
    p.agregarInstruccion(A,n);
    p.agregarInstruccion(A,o);

    Calculadora c = Calculadora(p,A,14);

    ASSERT_EQ(c.finalizo(),false);
    ASSERT_EQ(c.pila().empty(),true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(p.cantInstruccionesRutinaR(A), 7);

    for(int i = 0;i<7;i++){
        ASSERT_EQ(c.finalizo(),false);
        ASSERT_EQ(c.instanteActual(),i);
        ASSERT_EQ(c.indiceInstruccionActual(),i);
        ASSERT_EQ(c.rutinaActual(),A);
        c.ejecutarUnPaso();
    }

}



TEST(test_calculadora, sumas_varias) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 0);
    Instruccion push_2 = Instruccion(PUSH, 2);
    Instruccion push_3 = Instruccion(PUSH, -4);
    Instruccion push_4 = Instruccion(PUSH, 0);
    Instruccion push_5 = Instruccion(PUSH, 20);
    Instruccion push_6 = Instruccion(PUSH, 6);
    Instruccion push_7 = Instruccion(PUSH, -2);

    Instruccion add_1 = Instruccion(ADD);
    Instruccion add_2 = Instruccion(ADD);
    Instruccion add_3 = Instruccion(ADD);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, add_1);
    p.agregarInstruccion(A, add_2);
    p.agregarInstruccion(A, add_3);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);
    pilaEsperada.push(2);
    pilaEsperada.push(-4);
    pilaEsperada.push(24);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST(test_calculadora, suma_pila_vacia) {
    Programa p = Programa();

    Instruccion add_1 = Instruccion(ADD);

    rutina A = "A";
    p.agregarInstruccion(A, add_1);

    Calculadora c = Calculadora(p, A, 2);

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), true);

}



TEST(test_calculadora, suma_pila_con_un_valor) {
    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 3);
    Instruccion add_1 = Instruccion(ADD);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, add_1);

    Calculadora c = Calculadora(p, A, 2);

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(3);

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    stack<int> ccc = c.pila();
    while(!ccc.empty() && !pilaEsperada.empty()){
        ASSERT_EQ(ccc.top(), pilaEsperada.top());
        ccc.pop();
        pilaEsperada.pop();
    }
    ASSERT_EQ(c.finalizo(), false);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.finalizo(), true);

}



TEST(test_calculadora, restas_varias_dos_rutinas) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 4);
    Instruccion push_2 = Instruccion(PUSH, 1);
    Instruccion push_3 = Instruccion(PUSH, -4);
    Instruccion push_4 = Instruccion(PUSH, 0);
    Instruccion push_5 = Instruccion(PUSH, 8);
    Instruccion push_6 = Instruccion(PUSH, -6);
    Instruccion push_7 = Instruccion(PUSH, -2);
    Instruccion push_8 = Instruccion(PUSH, 5);
    Instruccion push_9 = Instruccion(PUSH, 2);
    Instruccion push_10 = Instruccion(PUSH, 1);

    Instruccion sub_1 = Instruccion(SUB);
    Instruccion sub_2 = Instruccion(SUB);
    Instruccion sub_3 = Instruccion(SUB);
    Instruccion sub_4 = Instruccion(SUB);
    Instruccion sub_5 = Instruccion(SUB);
    Instruccion sub_6 = Instruccion(SUB);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, sub_1);
    p.agregarInstruccion(A, sub_2);
    p.agregarInstruccion(A, sub_3);
    p.agregarInstruccion(A, push_8);
    p.agregarInstruccion(A, push_9);
    p.agregarInstruccion(A, push_10);
    p.agregarInstruccion(A, sub_4);
    p.agregarInstruccion(A, sub_5);
    p.agregarInstruccion(A, sub_6);

    rutina B = "B";
    p.agregarInstruccion(B, push_1);
    p.agregarInstruccion(B, push_5);
    p.agregarInstruccion(B, sub_4);
    p.agregarInstruccion(B, sub_5);

    Calculadora c = Calculadora(p, A, 9);


    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
        ASSERT_EQ(c.pila().empty(), false);
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(4);
    pilaEsperada.push(1);
    pilaEsperada.push(-4);
    pilaEsperada.push(-16);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST(test_calculadora, resta_pila_vacia) {
    Programa p = Programa();

    Instruccion sub_1 = Instruccion(SUB);

    rutina A = "A";
    p.agregarInstruccion(A, sub_1);

    Calculadora c = Calculadora(p, A, 2);

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), true);

}



TEST(test_calculadora, resta_pila_con_un_valor) {
    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 7);
    Instruccion sub_1 = Instruccion(SUB);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, sub_1);

    Calculadora c = Calculadora(p, A, 2);

    stack<int> pilaEsperada = stack<int>();

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();
    pilaEsperada.push(7);

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), false);

    c.ejecutarUnPaso();
    pilaEsperada.pop();
    pilaEsperada.push(-7);

    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), true);

}



TEST(test_calculadora, mult_varias_1) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 0);
    Instruccion push_2 = Instruccion(PUSH, 2);
    Instruccion push_3 = Instruccion(PUSH, -2);
    Instruccion push_4 = Instruccion(PUSH, -1);
    Instruccion push_5 = Instruccion(PUSH, 2);
    Instruccion push_6 = Instruccion(PUSH, 1);
    Instruccion push_7 = Instruccion(PUSH, 3);

    Instruccion mul_1 = Instruccion(MUL);
    Instruccion mul_2 = Instruccion(MUL);
    Instruccion mul_3 = Instruccion(MUL);
    Instruccion mul_4 = Instruccion(MUL);


    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, mul_1);
    p.agregarInstruccion(A, mul_2);
    p.agregarInstruccion(A, mul_3);
    p.agregarInstruccion(A, mul_4);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 11; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);
    pilaEsperada.push(2);
    pilaEsperada.push(12);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST(test_calculadora, mult_varias_2) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 0);
    Instruccion push_2 = Instruccion(PUSH, 2);
    Instruccion push_3 = Instruccion(PUSH, -2);
    Instruccion push_4 = Instruccion(PUSH, -1);
    Instruccion push_5 = Instruccion(PUSH, 2);
    Instruccion push_6 = Instruccion(PUSH, 1);
    Instruccion push_7 = Instruccion(PUSH, 3);

    Instruccion mul_1 = Instruccion(MUL);
    Instruccion mul_2 = Instruccion(MUL);
    Instruccion mul_3 = Instruccion(MUL);
    Instruccion mul_4 = Instruccion(MUL);


    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, mul_1);
    p.agregarInstruccion(A, mul_2);
    p.agregarInstruccion(A, mul_3);
    p.agregarInstruccion(A, mul_4);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 11; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);
    pilaEsperada.push(2);
    pilaEsperada.push(12);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST(test_calculadora, mult_pila_vacia) {
    Programa p = Programa();

    Instruccion mul_1 = Instruccion(MUL);

    rutina A = "A";
    p.agregarInstruccion(A, mul_1);

    Calculadora c = Calculadora(p, A, 2);
    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), true);

}



TEST(test_calculadora, mult_pila_con_un_valor) {
    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 7);
    Instruccion mul_1 = Instruccion(MUL);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, mul_1);

    Calculadora c = Calculadora(p, A, 2);
    stack<int> pilaEsperada = stack<int>();

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.rutinaActual(), A);

    c.ejecutarUnPaso();
    pilaEsperada.push(7);

    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), false);

    c.ejecutarUnPaso();
    pilaEsperada.pop();
    pilaEsperada.push(0);

    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila(), pilaEsperada);
    ASSERT_EQ(c.finalizo(), true);
}



TEST(test_calculadora, mult_por_cero) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 0);
    Instruccion push_2 = Instruccion(PUSH, 0);
    Instruccion push_3 = Instruccion(PUSH, 0);
    Instruccion push_4 = Instruccion(PUSH, -1);
    Instruccion push_5 = Instruccion(PUSH, 2);
    Instruccion push_6 = Instruccion(PUSH, 0);
    Instruccion push_7 = Instruccion(PUSH, 3);

    Instruccion mul_1 = Instruccion(MUL);
    Instruccion mul_2 = Instruccion(MUL);
    Instruccion mul_3 = Instruccion(MUL);
    Instruccion mul_4 = Instruccion(MUL);


    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, mul_1);
    p.agregarInstruccion(A, mul_2);
    p.agregarInstruccion(A, mul_3);
    p.agregarInstruccion(A, mul_4);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 11; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);
    pilaEsperada.push(0);
    pilaEsperada.push(0);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST(test_calculadora, varias_aritmeticas) {

    Programa p = Programa();

    Instruccion push_1 = Instruccion(PUSH, 0);
    Instruccion push_2 = Instruccion(PUSH, 5);
    Instruccion push_3 = Instruccion(PUSH, 61);
    Instruccion push_4 = Instruccion(PUSH, 4);
    Instruccion push_5 = Instruccion(PUSH, 8);
    Instruccion push_6 = Instruccion(PUSH, -1);
    Instruccion push_7 = Instruccion(PUSH, 6);
    Instruccion push_8 = Instruccion(PUSH, 4);
    Instruccion push_9 = Instruccion(PUSH, -3);
    Instruccion push_10 = Instruccion(PUSH, 6);
    Instruccion push_11 = Instruccion(PUSH, -2);
    Instruccion push_12 = Instruccion(PUSH, 0);
    Instruccion push_13 = Instruccion(PUSH, 10);

    Instruccion op_1 = Instruccion(MUL);
    Instruccion op_2 = Instruccion(ADD);
    Instruccion op_3 = Instruccion(SUB);
    Instruccion op_4 = Instruccion(SUB);
    Instruccion op_5 = Instruccion(ADD);
    Instruccion op_6 = Instruccion(ADD);
    Instruccion op_7 = Instruccion(MUL);
    Instruccion op_8 = Instruccion(SUB);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, push_5);
    p.agregarInstruccion(A, push_6);
    p.agregarInstruccion(A, push_7);
    p.agregarInstruccion(A, push_8);
    p.agregarInstruccion(A, push_9);
    p.agregarInstruccion(A, op_1);
    p.agregarInstruccion(A, op_2);
    p.agregarInstruccion(A, op_3);
    p.agregarInstruccion(A, op_4);
    p.agregarInstruccion(A, op_5);
    p.agregarInstruccion(A, push_10);
    p.agregarInstruccion(A, push_11);
    p.agregarInstruccion(A, push_12);
    p.agregarInstruccion(A, push_13);
    p.agregarInstruccion(A, op_6);
    p.agregarInstruccion(A, op_7);
    p.agregarInstruccion(A, op_8);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.pila().empty(), true);

    for (int i = 0; i < 21; i++) {
        ASSERT_EQ(c.finalizo(), false);
        ASSERT_EQ(c.instanteActual(), i);
        ASSERT_EQ(c.indiceInstruccionActual(), i);
        ASSERT_EQ(c.rutinaActual(), A);
        c.ejecutarUnPaso();
    }

    stack<int> pilaEsperada = stack<int>();
    pilaEsperada.push(0);
    pilaEsperada.push(5);
    pilaEsperada.push(61);
    pilaEsperada.push(7);
    pilaEsperada.push(26);
    ASSERT_EQ(c.pila(), pilaEsperada);
}



TEST (test_calculadora, write_con_overwrite) {

    Programa p = Programa();
    variable x = "x";

    Instruccion push_1 = Instruccion(PUSH, 5);
    Instruccion push_2 = Instruccion(PUSH, 8);
    Instruccion write_1 = Instruccion(WRITE, x);
    Instruccion write_2 = Instruccion(WRITE, x);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, write_1);
    p.agregarInstruccion(A, write_2);

    Calculadora c = Calculadora(p, A, 2);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    ASSERT_EQ(c.valorVariableActual(x), 8);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
    ASSERT_EQ(c.valorVariableActual(x), 5);

    ASSERT_EQ(c.finalizo(), true);

    ASSERT_EQ(c.valorVariableATiempoDado(x, 0), 0);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 1), 0);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 2), 8);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 3), 5);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 4), 5);

    c.asignarVariable(x, -10);
    ASSERT_EQ(c.valorVariableActual(x), -10);
    ASSERT_EQ(c.instanteActual(), 4);  // Verifica que asignarVariable no modifique el instante actual
    ASSERT_EQ(c.valorVariableATiempoDado(x, 4), -10);

}



TEST (test_calculadora, write_varias_variables) {

    Programa p = Programa();
    variable v = "v";
    variable w = "w";
    variable x = "x";
    variable y = "y";
    variable z = "z";
    variable nueva = "nueva";

    Instruccion push_1 = Instruccion(PUSH, 5);
    Instruccion push_2 = Instruccion(PUSH, 55);
    Instruccion push_3 = Instruccion(PUSH, 555);
    Instruccion push_4 = Instruccion(PUSH, 5555);
    Instruccion write_1 = Instruccion(WRITE, v);
    Instruccion write_2 = Instruccion(WRITE, w);
    Instruccion write_3 = Instruccion(WRITE, x);
    Instruccion write_4 = Instruccion(WRITE, y);
    Instruccion write_5 = Instruccion(WRITE, z);

    rutina A = "A";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, write_1);
    p.agregarInstruccion(A, write_2);
    p.agregarInstruccion(A, write_3);
    p.agregarInstruccion(A, write_4);
    p.agregarInstruccion(A, write_5);

    Calculadora c = Calculadora(p, A, 3);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.valorVariableActual(v), 0);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(v), 0);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 55);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.valorVariableActual(v), 0);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 555);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    ASSERT_EQ(c.valorVariableActual(v), 0);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5555);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
    ASSERT_EQ(c.valorVariableActual(v), 0);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 555);
    ASSERT_EQ(c.instanteActual(), 5);
    ASSERT_EQ(c.indiceInstruccionActual(), 5);
    ASSERT_EQ(c.valorVariableActual(v), 5555);
    ASSERT_EQ(c.valorVariableActual(w), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 55);
    ASSERT_EQ(c.instanteActual(), 6);
    ASSERT_EQ(c.indiceInstruccionActual(), 6);
    ASSERT_EQ(c.valorVariableActual(v), 5555);
    ASSERT_EQ(c.valorVariableActual(w), 555);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 7);
    ASSERT_EQ(c.indiceInstruccionActual(), 7);
    ASSERT_EQ(c.valorVariableActual(v), 5555);
    ASSERT_EQ(c.valorVariableActual(w), 555);
    ASSERT_EQ(c.valorVariableActual(x), 55);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 8);
    ASSERT_EQ(c.indiceInstruccionActual(), 8);
    ASSERT_EQ(c.valorVariableActual(v), 5555);
    ASSERT_EQ(c.valorVariableActual(w), 555);
    ASSERT_EQ(c.valorVariableActual(x), 55);
    ASSERT_EQ(c.valorVariableActual(y), 5);
    ASSERT_EQ(c.valorVariableActual(z), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 9);
    ASSERT_EQ(c.indiceInstruccionActual(), 9);
    ASSERT_EQ(c.valorVariableActual(v), 5555);
    ASSERT_EQ(c.valorVariableActual(w), 555);
    ASSERT_EQ(c.valorVariableActual(x), 55);
    ASSERT_EQ(c.valorVariableActual(y), 5);
    ASSERT_EQ(c.valorVariableActual(z), 0);

    ASSERT_EQ(c.finalizo(), true);

    c.asignarVariable(nueva, 0);
    c.asignarVariable(z, -5);

    ASSERT_EQ(c.instanteActual(), 9); // Verifica que asignarVariable no modifique el instante actual
    ASSERT_EQ(c.valorVariableActual(nueva), 0);
    ASSERT_EQ(c.valorVariableActual(z), -5);

}


TEST (test_calculadora, write_pila_vacia) {

    Programa p = Programa();
    variable x = "x";

    Instruccion write_1 = Instruccion(WRITE, x);

    rutina rut = "No es A";
    p.agregarInstruccion(rut, write_1);

    Calculadora c = Calculadora(p, rut, 10);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), rut);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), rut);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(x), 0);

    ASSERT_EQ(c.finalizo(), true);

    ASSERT_EQ(c.valorVariableATiempoDado(x, 0), 0);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 1), 0);

}



TEST (test_calculadora, read_write) {

    Programa p = Programa();
    variable x = "x";
    variable y = "y";

    Instruccion push_1 = Instruccion(PUSH, 5);
    Instruccion push_2 = Instruccion(PUSH, 8);
    Instruccion push_3 = Instruccion(PUSH, 0);
    Instruccion push_4 = Instruccion(PUSH, 9);
    Instruccion add_1 = Instruccion(ADD);
    Instruccion sub_1 = Instruccion(SUB);
    Instruccion write_1 = Instruccion(WRITE, x);
    Instruccion write_2 = Instruccion(WRITE, y);
    Instruccion read_1 = Instruccion(READ, x);

    rutina B = "A camuflada";
    p.agregarInstruccion(B, push_1);
    p.agregarInstruccion(B, push_2);
    p.agregarInstruccion(B, add_1);
    p.agregarInstruccion(B, write_1);
    p.agregarInstruccion(B, push_3);
    p.agregarInstruccion(B, push_4);
    p.agregarInstruccion(B, read_1);
    p.agregarInstruccion(B, sub_1);
    p.agregarInstruccion(B, write_2);

    Calculadora c = Calculadora(p, B, 3);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 13);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 0);
    ASSERT_EQ(c.instanteActual(), 5);
    ASSERT_EQ(c.indiceInstruccionActual(), 5);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 9);
    ASSERT_EQ(c.instanteActual(), 6);
    ASSERT_EQ(c.indiceInstruccionActual(), 6);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 13);
    ASSERT_EQ(c.instanteActual(), 7);
    ASSERT_EQ(c.indiceInstruccionActual(), 7);
    ASSERT_EQ(c.valorVariableActual(x), c.pila().top());
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), -4);
    ASSERT_EQ(c.instanteActual(), 8);
    ASSERT_EQ(c.indiceInstruccionActual(), 8);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    ASSERT_EQ(c.valorVariableActual(y), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 0);
    ASSERT_EQ(c.instanteActual(), 9);
    ASSERT_EQ(c.indiceInstruccionActual(), 9);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    ASSERT_EQ(c.valorVariableActual(y), -4);

    ASSERT_EQ(c.finalizo(), true);

}



TEST (test_calculadora, read_vacia) {

    Programa p = Programa();
    variable x = "x";

    Instruccion read_1 = Instruccion(READ, x);
    Instruccion write_1 = Instruccion(WRITE, x);

    rutina A = "A volvio, en forma de fichas";
    p.agregarInstruccion(A, read_1);
    p.agregarInstruccion(A, write_1);

    Calculadora c = Calculadora(p, A, 1);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();


    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 0);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.valorVariableActual(x), 0);

    ASSERT_EQ(c.finalizo(), true);
    ASSERT_EQ(p.cantInstruccionesRutinaR(A), 2);

    nat i = 0;
    while (i < p.cantInstruccionesRutinaR(A)) {
        ASSERT_EQ(c.valorVariableATiempoDado(x, i), 0);
        i++;
    }

}



TEST (test_calculadora, read_asignar_variable) {

    Programa p = Programa();
    rutina aAa = "Soy A, pero mejor";
    variable A  = "Fui degradada";

    Instruccion push_1 = Instruccion(PUSH, 5);
    Instruccion push_2 = Instruccion(PUSH, 8);
    Instruccion read_1 = Instruccion(READ, A);
    Instruccion write_1 = Instruccion(WRITE, A);
    Instruccion mul_1 = Instruccion(MUL);

    p.agregarInstruccion(aAa, push_1);
    p.agregarInstruccion(aAa, push_2);
    p.agregarInstruccion(aAa, read_1);
    p.agregarInstruccion(aAa, mul_1);
    p.agregarInstruccion(aAa, write_1);

    Calculadora c = Calculadora(p, aAa, 3);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_EQ(c.valorVariableActual(A), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_EQ(c.valorVariableActual(A), 0);

    c.asignarVariable(A, 9);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.valorVariableActual(A), 9);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 1), 0);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 9);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    ASSERT_EQ(c.valorVariableActual(A), 9);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 72);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
    ASSERT_EQ(c.valorVariableActual(A), 9);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), aAa);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 5);
    ASSERT_EQ(c.indiceInstruccionActual(), 5);
    ASSERT_EQ(c.valorVariableActual(A), 72);

    ASSERT_EQ(c.finalizo(), true);

    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual()), 72);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 1), 72);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 2), 9);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 3), 9);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 4), 0);
    ASSERT_EQ(c.valorVariableATiempoDado(A, c.instanteActual() - 5), 0);

}



TEST (test_calculadora, read_variable_no_inicializada) {

    Programa p = Programa();
    variable y = "y";

    Instruccion push_1 = Instruccion(PUSH, -5);
    Instruccion push_2 = Instruccion(PUSH, 8);
    Instruccion push_3 = Instruccion(PUSH, -3);
    Instruccion push_4 = Instruccion(PUSH, 10);
    Instruccion read_1 = Instruccion(READ, y);

    rutina A = "En verdad, soy aAa";
    p.agregarInstruccion(A, push_1);
    p.agregarInstruccion(A, push_2);
    p.agregarInstruccion(A, push_3);
    p.agregarInstruccion(A, push_4);
    p.agregarInstruccion(A, read_1);

    Calculadora c = Calculadora(p, A, 4);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), -5);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), -3);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 10);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);

    c.ejecutarUnPaso();

    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 0);  // Como el valor de y no esta inicializado, deberia "pushear" 0  a la pila.
    ASSERT_EQ(c.instanteActual(), 5);
    ASSERT_EQ(c.indiceInstruccionActual(), 5);

    ASSERT_EQ(c.finalizo(), true);

    ASSERT_EQ(c.valorVariableActual(y), 0);

    nat i = 0;
    while (i < p.cantInstruccionesRutinaR(A)) {
        ASSERT_EQ(c.valorVariableATiempoDado(y, i), 0);
        i++;
    }

}


TEST (test_calculadora, una_variable_asignar_variable) {

    Programa p = Programa();
    rutina A = "A";
    variable x = "x";

    Instruccion pushA_1 = Instruccion(PUSH, 8);
    Instruccion pushA_2 = Instruccion(PUSH, 5);
    Instruccion subA_1 = Instruccion(SUB);
    Instruccion writeA = Instruccion(WRITE, x);

    p.agregarInstruccion(A, pushA_1);
    p.agregarInstruccion(A, pushA_2);
    p.agregarInstruccion(A, subA_1);
    p.agregarInstruccion(A, writeA);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();
    c.asignarVariable(x, 13);

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.valorVariableActual(x), 13);
    c.ejecutarUnPaso();
    c.asignarVariable(x, 11);

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 5);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.valorVariableActual(x), 11);
    c.ejecutarUnPaso();
    c.asignarVariable(x, 7);

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 3);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.valorVariableActual(x), 7);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.finalizo(), true);
    ASSERT_EQ(c.valorVariableActual(x), 3);

    //Recapitulo los valores de x a lo largo de la ejecucion:

    ASSERT_EQ(c.valorVariableATiempoDado(x, 0), 0);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 1), 13);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 2), 11);
    ASSERT_EQ(c.valorVariableATiempoDado(x, 3),
              3); //No es 7 ya que en el instante 3 sobreescribo el 7 que se genero en ese instante con asignarVariable
    ASSERT_EQ(c.valorVariableATiempoDado(x, 4), 3);

}



TEST (test_calculadora, jump_tres_rutinas_existentes) {

    Programa p = Programa();
    rutina A = "A";
    rutina B = "B";
    rutina C = "C";
    variable x = "x";

    Instruccion pushA_1 = Instruccion(PUSH, 2);
    Instruccion pushA_2 = Instruccion(PUSH, 4);
    Instruccion addA_1 = Instruccion(ADD);
    Instruccion jumpA = Instruccion(JUMP, C);
    p.agregarInstruccion(A, pushA_1);
    p.agregarInstruccion(A, pushA_2);
    p.agregarInstruccion(A, addA_1);
    p.agregarInstruccion(A, jumpA);

    Instruccion readB = Instruccion(READ, x);
    p.agregarInstruccion(B, readB);

    Instruccion writeC = Instruccion(WRITE, x);
    Instruccion jumpzC = Instruccion(JUMPZ, B);
    p.agregarInstruccion(C, writeC);
    p.agregarInstruccion(C, jumpzC);

    Calculadora c = Calculadora(p, A, 9);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().top(), 2);
    ASSERT_EQ(c.instanteActual(), 1);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().top(), 4);
    ASSERT_EQ(c.instanteActual(), 2);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().top(), 6);
    ASSERT_EQ(c.instanteActual(), 3);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), C);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.valorVariableActual(x), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.valorVariableActual(x), 6);
    ASSERT_EQ(c.instanteActual(), 5);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), B);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.instanteActual(), 6);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), true);
    ASSERT_EQ(c.instanteActual(), 7);
    ASSERT_EQ(c.pila().empty(), false);
}



TEST (test_calculadora, jump_rutina_inexistente) {

    Programa p = Programa();
    rutina A = "A";
    variable cl = "cl";

    Instruccion pushA_1 = Instruccion(PUSH, 16);
    Instruccion pushA_2 = Instruccion(PUSH, 15);
    Instruccion addA_1 = Instruccion(ADD);
    Instruccion writeA = Instruccion(WRITE, cl);
    Instruccion jumpA = Instruccion(JUMP, "DOOM");
    p.agregarInstruccion(A, pushA_1);
    p.agregarInstruccion(A, pushA_2);
    p.agregarInstruccion(A, addA_1);
    p.agregarInstruccion(A, writeA);
    p.agregarInstruccion(A, jumpA);

    Calculadora c = Calculadora(p, A, 2);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    ASSERT_EQ(c.valorVariableActual(cl), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 16);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 15);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 31);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.valorVariableActual(cl), 31);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), true);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.instanteActual(), 5);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
}



TEST (test_calculadora, jumpz_no_salto_a_existente) {

    Programa p = Programa();
    rutina A = "A";
    rutina NOPE = "NOPE";

    Instruccion pushA_1 = Instruccion(PUSH, 7);
    Instruccion pushA_2 = Instruccion(PUSH, 8);
    Instruccion subA_1 = Instruccion(SUB);
    Instruccion jumpZ = Instruccion(JUMPZ, NOPE);
    p.agregarInstruccion(A, pushA_1);
    p.agregarInstruccion(A, pushA_2);
    p.agregarInstruccion(A, subA_1);
    p.agregarInstruccion(A, jumpZ);

    Instruccion d = Instruccion(PUSH, 6);
    Instruccion i = Instruccion(PUSH, 6);
    Instruccion e = Instruccion(PUSH, 6);
    p.agregarInstruccion(NOPE, d);
    p.agregarInstruccion(NOPE, i);
    p.agregarInstruccion(NOPE, e);

    Calculadora c = Calculadora(p, A, 2);

    ASSERT_EQ(c.finalizo(), false);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.instanteActual(), 0);
    ASSERT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 7);
    ASSERT_EQ(c.instanteActual(), 1);
    ASSERT_EQ(c.indiceInstruccionActual(), 1);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), 8);
    ASSERT_EQ(c.instanteActual(), 2);
    ASSERT_EQ(c.indiceInstruccionActual(), 2);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.pila().empty(), false);
    ASSERT_EQ(c.pila().top(), -1);
    ASSERT_EQ(c.instanteActual(), 3);
    ASSERT_EQ(c.indiceInstruccionActual(), 3);
    c.ejecutarUnPaso();

    ASSERT_EQ(c.finalizo(), true);
    ASSERT_EQ(c.pila().empty(), true);
    ASSERT_EQ(c.rutinaActual(), A);
    ASSERT_EQ(c.instanteActual(), 4);
    ASSERT_EQ(c.indiceInstruccionActual(), 4);
}