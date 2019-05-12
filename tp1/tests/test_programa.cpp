#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"

TEST(test_programa, rutinaExistente) {
    Programa p;
    EXPECT_EQ(p.esRutinaExistente("a"), false);
    EXPECT_EQ(p.esRutinaExistente("b"), false);
    p.agregarInstruccion("a", Instruccion(PUSH, 10));
    p.agregarInstruccion("a", Instruccion(ADD));
    EXPECT_EQ(p.esRutinaExistente("a"), true);
    EXPECT_EQ(p.esRutinaExistente("b"), false);
    p.agregarInstruccion("b", Instruccion(WRITE, "z"));
    EXPECT_EQ(p.esRutinaExistente("a"), true);
    EXPECT_EQ(p.esRutinaExistente("b"), true);
}

TEST(test_programa, longitud) {
    Programa p;
    p.agregarInstruccion("foo", Instruccion(PUSH, 10));
    EXPECT_EQ(p.longitud("foo"), 1);
    p.agregarInstruccion("foo", Instruccion(ADD));
    EXPECT_EQ(p.longitud("foo"), 2);
    p.agregarInstruccion("foo", Instruccion(PUSH, 12));
    EXPECT_EQ(p.longitud("foo"), 3);
    p.agregarInstruccion("foo", Instruccion(MUL));
    EXPECT_EQ(p.longitud("foo"), 4);
}

TEST(test_programa, instruccion) {
    Programa p;
    p.agregarInstruccion("X", Instruccion(READ, "x"));
    p.agregarInstruccion("X", Instruccion(PUSH, 2));
    p.agregarInstruccion("X", Instruccion(MUL));
    p.agregarInstruccion("X", Instruccion(READ, "y"));
    p.agregarInstruccion("X", Instruccion(ADD));
    EXPECT_EQ(p.longitud("X"), 5);
    EXPECT_EQ(p.instruccion("X", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("X", 0).nombre(), "x");
    EXPECT_EQ(p.instruccion("X", 1).operacion(), PUSH);
    EXPECT_EQ(p.instruccion("X", 1).valor(), 2);
    EXPECT_EQ(p.instruccion("X", 2).operacion(), MUL);
    EXPECT_EQ(p.instruccion("X", 3).operacion(), READ);
    EXPECT_EQ(p.instruccion("X", 3).nombre(), "y");
    EXPECT_EQ(p.instruccion("X", 4).operacion(), ADD);
}

TEST(test_programa, dosRutinas) {
    Programa p;
    p.agregarInstruccion("A", Instruccion(READ, "a"));
    p.agregarInstruccion("B", Instruccion(WRITE, "b"));
    p.agregarInstruccion("A", Instruccion(JUMP, "c"));
    p.agregarInstruccion("B", Instruccion(JUMPZ, "d"));
    p.agregarInstruccion("A", Instruccion(READ, "e"));

    EXPECT_EQ(p.longitud("A"), 3);
    EXPECT_EQ(p.longitud("B"), 2);
    EXPECT_EQ(p.instruccion("A", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 0).nombre(), "a");
    EXPECT_EQ(p.instruccion("A", 1).operacion(), JUMP);
    EXPECT_EQ(p.instruccion("A", 1).nombre(), "c");
    EXPECT_EQ(p.instruccion("A", 2).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 2).nombre(), "e");

    EXPECT_EQ(p.instruccion("B", 0).operacion(), WRITE);
    EXPECT_EQ(p.instruccion("B", 0).nombre(), "b");
    EXPECT_EQ(p.instruccion("B", 1).operacion(), JUMPZ);
    EXPECT_EQ(p.instruccion("B", 1).nombre(), "d");
}

TEST(test_programa, testTodo) {
    Programa p;
    p.agregarInstruccion("A", Instruccion(READ, "x"));
    p.agregarInstruccion("A", Instruccion(PUSH, 2));
    p.agregarInstruccion("A", Instruccion(ADD));
    p.agregarInstruccion("A", Instruccion(WRITE, "y"));
    p.agregarInstruccion("B", Instruccion(PUSH, 2));
    p.agregarInstruccion("B", Instruccion(READ, "x"));
    p.agregarInstruccion("B", Instruccion(MUL));
    p.agregarInstruccion("B", Instruccion(WRITE, "x"));
    p.agregarInstruccion("B", Instruccion(JUMP, "A"));

    EXPECT_EQ(p.longitud("A"), 4);
    EXPECT_EQ(p.longitud("B"), 5);
    EXPECT_EQ(p.esRutinaExistente("A"), true);
    EXPECT_EQ(p.esRutinaExistente("B"), true);
    EXPECT_EQ(p.esRutinaExistente("c"), false);
    EXPECT_EQ(p.instruccion("A", 2).operacion(), ADD);
    EXPECT_EQ(p.instruccion("A", 0).nombre(), "x");
    EXPECT_EQ(p.instruccion("B", 2).operacion(), MUL);
    EXPECT_EQ(p.instruccion("B", 1).nombre(), "x");
}

TEST(test_programa, testTodo2) {
    Programa p;
    EXPECT_EQ(p.esRutinaExistente("A"), false);

    p.agregarInstruccion("A", Instruccion(READ, "n"));
    EXPECT_EQ(p.longitud("A"), 1);
    p.agregarInstruccion("A", Instruccion(PUSH, 2));
    EXPECT_EQ(p.longitud("A"), 2);
    p.agregarInstruccion("A", Instruccion(SUB));
    EXPECT_EQ(p.esRutinaExistente("A"), true);
    EXPECT_EQ(p.esRutinaExistente("c"), false);
    EXPECT_EQ(p.longitud("A"), 3);
    p.agregarInstruccion("A", Instruccion(WRITE, "n"));
    EXPECT_EQ(p.longitud("A"), 4);
    p.agregarInstruccion("A", Instruccion(READ, "n"));
    EXPECT_EQ(p.longitud("A"), 5);
    EXPECT_EQ(p.esRutinaExistente("A"), true);
    EXPECT_EQ(p.esRutinaExistente("c"), false);
    p.agregarInstruccion("c", Instruccion(PUSH, 2));
    EXPECT_EQ(p.esRutinaExistente("c"), true);
    EXPECT_EQ(p.longitud("c"), 1);
    p.agregarInstruccion("A", Instruccion(JUMPZ, "c"));
    EXPECT_EQ(p.longitud("A"), 6);
    p.agregarInstruccion("A", Instruccion(JUMP, "ASD"));
    EXPECT_EQ(p.longitud("A"), 7);
}

TEST(testPrograma, tresRutinas) {
    Programa p;
    p.agregarInstruccion("A", Instruccion(READ, "a"));
    p.agregarInstruccion("B", Instruccion(WRITE, "b"));
    p.agregarInstruccion("C", Instruccion(READ, "j"));
    p.agregarInstruccion("A", Instruccion(JUMP, "c"));
    p.agregarInstruccion("B", Instruccion(JUMPZ, "d"));
    p.agregarInstruccion("C", Instruccion(WRITE, "j"));
    p.agregarInstruccion("A", Instruccion(READ, "e"));
    p.agregarInstruccion("C", Instruccion(JUMPZ, "j"));

    EXPECT_EQ(p.longitud("A"), 3);
    EXPECT_EQ(p.longitud("B"), 2);
    EXPECT_EQ(p.longitud("C"), 3);
    EXPECT_EQ(p.instruccion("A", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 0).nombre(), "a");
    EXPECT_EQ(p.instruccion("A", 1).operacion(), JUMP);
    EXPECT_EQ(p.instruccion("A", 1).nombre(), "c");
    EXPECT_EQ(p.instruccion("A", 2).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 2).nombre(), "e");

    EXPECT_EQ(p.instruccion("B", 0).operacion(), WRITE);
    EXPECT_EQ(p.instruccion("B", 0).nombre(), "b");
    EXPECT_EQ(p.instruccion("B", 1).operacion(), JUMPZ);
    EXPECT_EQ(p.instruccion("B", 1).nombre(), "d");

    EXPECT_EQ(p.instruccion("C", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("C", 0).nombre(), "j");
    EXPECT_EQ(p.instruccion("C", 1).operacion(), WRITE);
    EXPECT_EQ(p.instruccion("C", 1).nombre(), "j");
    EXPECT_EQ(p.instruccion("C", 2).operacion(), JUMPZ);
    EXPECT_EQ(p.instruccion("C", 2).nombre(), "j");

}
