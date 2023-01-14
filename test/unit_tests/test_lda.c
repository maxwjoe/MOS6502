#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"

TEST(T_LDA_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x99);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x99);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x7f);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x7f);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0x7f);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x7f);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA, 0x33);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x33);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_ABX_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x22);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x22);
    MemoryWriteByte(m, 0x2222 + x_reg, 0x89);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x89);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_ABX_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    byte x_reg = 0x22;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFF);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x22);
    MemoryWriteByte(m, 0x22FF + x_reg, 0x89);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x89);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_ABY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x22);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x22);
    MemoryWriteByte(m, 0x2222, 0x01);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x01);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_INX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_INX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x56);
    MemoryWriteByte(m, 0x56 + x_reg, 0x99);
    MemoryWriteByte(m, 0x56 + x_reg + 1, 0x99);
    MemoryWriteByte(m, 0x9999, 0x42);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x42);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_INY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    byte y_reg = 0x22;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x56);
    MemoryWriteByte(m, 0x56, 0x99);
    MemoryWriteByte(m, 0x56 + 1, 0x88);
    MemoryWriteByte(m, 0x8899 + y_reg, 0x42);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x42);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}

TEST(T_LDA_INY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    byte y_reg = 0x22;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFE);
    MemoryWriteByte(m, 0x00FE, 0xFF);
    MemoryWriteByte(m, 0x00FE + 1, 0x88);
    MemoryWriteByte(m, 0x88FF + y_reg, 0x42);

    int execution_result = CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x42);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(execution_result, ok);

    CPUFree(c, 1);
}