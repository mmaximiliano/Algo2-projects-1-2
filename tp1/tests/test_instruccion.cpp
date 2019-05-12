#include "gtest/gtest.h"

#include "../src/Instruccion.h"

TEST(test_instruccion, i_push) {
    Instruccion i(PUSH, 121);
    EXPECT_EQ(i.operacion(), PUSH);
    EXPECT_EQ(i.valor(), 121);
}

TEST(test_instruccion, i_add) {
    Instruccion i(ADD);
    EXPECT_EQ(i.operacion(), ADD);
}

TEST(test_instruccion, i_sub) {
    Instruccion i(SUB);
    EXPECT_EQ(i.operacion(), SUB);
}

TEST(test_instruccion, i_mul) {
    Instruccion i(MUL);
    EXPECT_EQ(i.operacion(), MUL);
}

TEST(test_instruccion, i_read) {
    Instruccion i(READ, "foo");
    EXPECT_EQ(i.operacion(), READ);
    EXPECT_EQ(i.nombre(), "foo");
}

TEST(test_instruccion, i_write) {
    Instruccion i(WRITE, "bar");
    EXPECT_EQ(i.operacion(), WRITE);
    EXPECT_EQ(i.nombre(), "bar");
}

TEST(test_instruccion, i_jump) {
    Instruccion i(JUMP, "baz");
    EXPECT_EQ(i.operacion(), JUMP);
    EXPECT_EQ(i.nombre(), "baz");
}

TEST(test_instruccion, i_jumpz) {
    Instruccion i(JUMPZ, "quux");
    EXPECT_EQ(i.operacion(), JUMPZ);
    EXPECT_EQ(i.nombre(), "quux");
}

TEST(test, push01) {
    Instruccion i(PUSH, 0);
    EXPECT_EQ(i.operacion(), PUSH);
    EXPECT_EQ(i.valor(), 0);
}

TEST(test, push02) {
    Instruccion i(PUSH, -5);
    EXPECT_EQ(i.operacion(), PUSH);
    EXPECT_EQ(i.valor(), -5);
}

TEST(test, push03) {
    Instruccion i(PUSH, 00);
    EXPECT_EQ(i.operacion(), PUSH);
    EXPECT_EQ(i.valor(), 00);
}

TEST(test2, read01) {
    Instruccion i(READ, "foot");
    EXPECT_EQ(i.operacion(), READ);
    EXPECT_EQ(i.nombre(), "foot");
}

TEST(test2, read02) {
    Instruccion i(READ, " ");
    EXPECT_EQ(i.operacion(), READ);
    EXPECT_EQ(i.nombre(), " ");
}

TEST(test2, read03) {
    Instruccion i(READ, "0");
    EXPECT_EQ(i.operacion(), READ);
    EXPECT_EQ(i.nombre(), "0");
}

TEST(test3, write01) {
    Instruccion i(WRITE, " ");
    EXPECT_EQ(i.operacion(), WRITE);
    EXPECT_EQ(i.nombre(), " ");
}

TEST(test3, write02) {
    Instruccion i(WRITE, "");
    EXPECT_EQ(i.operacion(), WRITE);
    EXPECT_EQ(i.nombre(), "");
}

TEST(test3, write03) {
    Instruccion i(WRITE, "5");
    EXPECT_EQ(i.operacion(), WRITE);
    EXPECT_EQ(i.nombre(), "5");
}

TEST(test4, jump01) {
    Instruccion i(JUMP, "b");
    EXPECT_EQ(i.operacion(), JUMP);
    EXPECT_EQ(i.nombre(), "b");
}

TEST(test4, jump02) {
    Instruccion i(JUMP, "5");
    EXPECT_EQ(i.operacion(), JUMP);
    EXPECT_EQ(i.nombre(), "5");
}

TEST(test4, jump03) {
    Instruccion i(JUMP, " ");
    EXPECT_EQ(i.operacion(), JUMP);
    EXPECT_EQ(i.nombre(), " ");
}

TEST(test5, jumpz01) {
    Instruccion i(JUMPZ, "4");
    EXPECT_EQ(i.operacion(), JUMPZ);
    EXPECT_EQ(i.nombre(), "4");
}

TEST(test5, jumpz02) {
    Instruccion i(JUMPZ, " ");
    EXPECT_EQ(i.operacion(), JUMPZ);
    EXPECT_EQ(i.nombre(), " ");
}

TEST(test5, jumpz03) {
    Instruccion i(JUMPZ, "q");
    EXPECT_EQ(i.operacion(), JUMPZ);
    EXPECT_EQ(i.nombre(), "q");
}
