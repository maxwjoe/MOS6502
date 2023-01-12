#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"
#include "EmulatorTypes.h"

TEST(T_LDX_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x88);

    int execution_result = CPUExecute(c);

    byte x_register = CPUGetX(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x88);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDX_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x88);
    MemoryWriteByte(m, 0x0088, 0x44);

    int execution_result = CPUExecute(c);

    byte x_register = CPUGetX(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x44);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDX_ZPY)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_ZPY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x44);
    MemoryWriteByte(m, 0x0044 + y_reg, 0x56);

    int execution_result = CPUExecute(c);

    byte x_register = CPUGetX(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x56);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDX_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x44);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x55);
    MemoryWriteByte(m, 0x5544, 0x99);

    int execution_result = CPUExecute(c);

    byte x_register = CPUGetX(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x99);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDX_ABY_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte y_reg = 0x01;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x44);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x22);
    MemoryWriteByte(m, 0x2244 + y_reg, 0x99);

    int execution_result = CPUExecute(c);

    byte x_register = CPUGetX(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x99);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDX_ABY_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    byte y_reg = 0x11;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDX_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFF);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xAA);
    MemoryWriteByte(m, 0xAAFF + y_reg, 0x23);

    int execution_result = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte x_register = CPUGetX(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(x_register, 0x23);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}