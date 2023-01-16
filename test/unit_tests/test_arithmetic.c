#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"

TEST(T_ADC_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x3A);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ADC_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x56);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte sum = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(sum, 0x3A + 0x56);
    CHECK_TRUE(F_N);
    CHECK_TRUE(F_V);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_C);

    CPUFree(c, 1);
}

TEST(T_ADC_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x01);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ADC_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x44);
    MemoryWriteByte(m, 0x0044, 0x32);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte sum = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(sum, 0x33);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_V);
    CHECK_FALSE(F_Z);
    CHECK_FALSE(F_C);

    CPUFree(c, 1);
}

TEST(T_ADC_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    byte x_reg = 0x33;
    CPUSetX(c, x_reg);

    CPUSetA(c, 0xFF);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, ADC_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x44);
    MemoryWriteByte(m, 0x0044 + x_reg, 0xFF);

    int execution_result = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte sum = CPUGetA(c);
    GET_ALL_FLAGS();

    printf("\n0x%02X\n", sum);

    CHECK_EQ(execution_result, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(sum, 0xFF + 0xFF);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_V);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_C);

    CPUFree(c, 1);
}