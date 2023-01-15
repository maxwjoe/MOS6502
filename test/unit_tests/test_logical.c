#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"

TEST(T_AND_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xC0);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0x80);

    CPUFree(c, 1);
}

TEST(T_AND_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0x85);

    CPUFree(c, 1);
}

TEST(T_AND_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x85);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0x85);

    CPUFree(c, 1);
}

TEST(T_AND_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x00);

    CPUFree(c, 1);
}

TEST(T_AND_ABX_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x00);

    CPUFree(c, 1);
}

TEST(T_AND_ABX_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x01);

    byte x_reg = 0xFF;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x01);

    CPUFree(c, 1);
}

TEST(T_AND_ABY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x44);

    CPUFree(c, 1);
}

TEST(T_AND_ABY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x44);

    CPUFree(c, 1);
}

TEST(T_AND_INX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_INX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0x33);
    MemoryWriteByte(m, 0x00AA + x_reg + 1, 0x33);
    MemoryWriteByte(m, 0x3333, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x44);

    CPUFree(c, 1);
}

TEST(T_AND_INY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x11);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x00);

    CPUFree(c, 1);
}

TEST(T_AND_INY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, AND_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x11);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x00);

    CPUFree(c, 1);
}

TEST(T_EOR_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xC0);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x45);

    CPUFree(c, 1);
}

TEST(T_EOR_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x7A);

    CPUFree(c, 1);
}

TEST(T_EOR_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x85);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x7A);

    CPUFree(c, 1);
}

TEST(T_EOR_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_EOR_ABX_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_EOR_ABX_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x00);

    byte x_reg = 0xFF;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_EOR_ABY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x12);

    CPUFree(c, 1);
}

TEST(T_EOR_ABY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x12);

    CPUFree(c, 1);
}

TEST(T_EOR_INX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_INX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0x33);
    MemoryWriteByte(m, 0x00AA + x_reg + 1, 0x33);
    MemoryWriteByte(m, 0x3333, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xBB);

    CPUFree(c, 1);
}

TEST(T_EOR_INY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x11);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x55);

    CPUFree(c, 1);
}

TEST(T_EOR_INY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, EOR_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x00);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x44);

    CPUFree(c, 1);
}

TEST(T_ORA_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xC0);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xC5);

    CPUFree(c, 1);
}

TEST(T_ORA_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x85);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x85);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_ABX_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x00);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_ABX_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x01);

    byte x_reg = 0xFF;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_ABY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x56);

    CPUFree(c, 1);
}

TEST(T_ORA_ABY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xBB);
    MemoryWriteByte(m, 0xBBAA + y_reg, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x56);

    CPUFree(c, 1);
}

TEST(T_ORA_INX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte x_reg = 0x11;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_INX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA + x_reg, 0x33);
    MemoryWriteByte(m, 0x00AA + x_reg + 1, 0x33);
    MemoryWriteByte(m, 0x3333, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);
    CHECK_EQ(a_value, 0xFF);

    CPUFree(c, 1);
}

TEST(T_ORA_INY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x44);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x11);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x55);

    CPUFree(c, 1);
}

TEST(T_ORA_INY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x44);

    byte y_reg = 0xFF;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ORA_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xAA);
    MemoryWriteByte(m, 0x00AA, 0x33);
    MemoryWriteByte(m, 0x00AA + 1, 0x33);
    MemoryWriteByte(m, 0x3333 + y_reg, 0x11);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_value = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);
    CHECK_EQ(a_value, 0x55);

    CPUFree(c, 1);
}