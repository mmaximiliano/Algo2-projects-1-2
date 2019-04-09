#include "gtest/gtest.h"
#include "../src/Instruccion.h"


TEST(test_instruccion, pushTest) {
    Instruccion i = Instruccion(PUSH,5);
    ASSERT_EQ(PUSH,i.op());
    ASSERT_EQ(5, i.valorPush());
}



TEST(test_instruccion, test_Add) {
    Instruccion i = Instruccion(ADD);
    ASSERT_EQ(ADD, i.op());
}



TEST(test_instruccion, test_Sub) {
    Instruccion i = Instruccion(SUB);
    ASSERT_EQ(SUB, i.op());
}



TEST(test_instruccion, test_Mul) {
    Instruccion i = Instruccion(MUL);
    ASSERT_EQ(MUL, i.op());
}



TEST(test_instruccion, test_Read) {
    variable x ="x";
    Instruccion i = Instruccion(READ,x);
    ASSERT_EQ(READ, i.op());
    ASSERT_EQ(x, i.nombreVariable());
}



TEST(test_instruccion, test_Write) {
    variable var = "y";
    Instruccion i = Instruccion(WRITE,var);
    ASSERT_EQ(WRITE, i.op());
    ASSERT_EQ(var, i.nombreVariable());
}



TEST(test_instruccion, test_Jump) {
    rutina rut = "A";
    Instruccion i = Instruccion(JUMP, rut);
    ASSERT_EQ(JUMP, i.op());
    ASSERT_EQ(rut, i.nombreRutina());
}



TEST(test_instruccion, test_JumpZ) {
    rutina rut = "B";
    Instruccion i = Instruccion(JUMPZ, rut);
    ASSERT_EQ(JUMPZ, i.op());
    ASSERT_EQ(rut, i.nombreRutina());
}
