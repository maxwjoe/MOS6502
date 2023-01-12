#include "Eagle.h"
#include "CPU6502.h"
#include "EmulatorTypes.h"
#include "common_macros.h"

TEST(T_LDY_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x99);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x99);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDY_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x33);
    MemoryWriteByte(m, 0x0033, 0x44);

    int execution_result = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x44);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_LDY_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte x_reg = 0x01;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFF);
    MemoryWriteByte(m, 0x00, 0x44);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x44);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);

    CPUFree(c, 1);
}

TEST(T_LDY_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x33);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xAA);
    MemoryWriteByte(m, 0xAA33, 0x11);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x11);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);

    CPUFree(c, 1);
}

TEST(T_LDY_ABX_NO_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte x_reg = 0x01;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x33);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xAA);
    MemoryWriteByte(m, 0xAA33 + x_reg, 0x11);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x11);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);

    CPUFree(c, 1);
}

TEST(T_LDY_ABX_WITH_CROSS)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    byte x_reg = 0xAA;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDY_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFF);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0xAA);
    MemoryWriteByte(m, 0xAAFF + x_reg, 0x11);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte y_reg = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_reg, 0x11);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_N);

    CPUFree(c, 1);
}
