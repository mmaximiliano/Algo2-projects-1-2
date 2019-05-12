#include "gtest/gtest.h"
#include "../src/Instruccion.h"
#include "../src/Programa.h"
#include "../src/Calculadora.h"

TEST(test_calulcadora, add) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),2);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),4);
}

TEST(test_calulcadora, mul) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(MUL));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));

    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),0);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),0);
}

TEST(test_calulcadora, sub) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-2);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-4);
}

TEST(test_calulcadora, jumpz_nosalta) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(JUMPZ,"SECU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 2));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),2);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),4);
}

TEST(test_calulcadora, jumpzsalta) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));//x=2
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 0));
    p.agregarInstruccion("MAIN", Instruccion(JUMPZ,"SECU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-4);
    c.ejecutar("SECU");
    EXPECT_EQ(c.valorVariable("x"),-10);
}

TEST(test_calulcadora, jumpzsalta2) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 0));
    p.agregarInstruccion("MAIN", Instruccion(JUMPZ,"SECU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-4);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-8);
}

TEST(test_calulcadora, jumpzsalta3) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(JUMPZ,"SECU"));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));


    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-6);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),0);//jumpz tacha el -6 dejando la pila vacia y por defecto, write escribe 0
}


TEST(test_calulcadora, jump_nosalta) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(JUMP,"SECUU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 2));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),2);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),4);
}

TEST(test_calulcadora, jumpsalta) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(JUMP,"SECU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-4);
    c.ejecutar("SECU");
    EXPECT_EQ(c.valorVariable("x"),-10);
}

TEST(test_calulcadora, jumpsalta2) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));
    p.agregarInstruccion("MAIN", Instruccion(JUMP,"SECU"));

    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-4);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-8);
}

TEST(test_calulcadora, jumpsalta3) {
    Programa p;
    p.agregarInstruccion("MAIN", Instruccion(READ, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 2));
    p.agregarInstruccion("MAIN", Instruccion(ADD));
    p.agregarInstruccion("MAIN", Instruccion(JUMP,"SECU"));
    p.agregarInstruccion("MAIN", Instruccion(WRITE, "x"));
    p.agregarInstruccion("MAIN", Instruccion(PUSH, 40));
    p.agregarInstruccion("MAIN", Instruccion(SUB));


    p.agregarInstruccion("SECU", Instruccion(READ, "x"));
    p.agregarInstruccion("SECU", Instruccion(PUSH, 6));
    p.agregarInstruccion("SECU", Instruccion(SUB));
    p.agregarInstruccion("SECU", Instruccion(WRITE, "x"));
    Calculadora c(p);

    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-6);
    c.ejecutar("MAIN");
    EXPECT_EQ(c.valorVariable("x"),-12);
}
