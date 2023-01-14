#include "Eagle.h"
#include "CPU6502.h"
#include "EmulatorTypes.h"
#include "common_macros.h"

TEST(T_STA_ZP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x77);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_ZP);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x33);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte value_written = MemoryReadByte(m, 0x0033);

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(value_written, 0x77);

    CPUFree(c, 1);
}

TEST(T_STA_ZPX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x89);
    byte x_reg = 0x44;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_ZPX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x55);

    int execution_status = CPUExecute(c);

    byte value_written = MemoryReadByte(m, 0x55 + x_reg);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(value_written, 0x89);
    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}

TEST(T_STA_AB)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetA(c, 0x11);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x55);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x33);

    int execution_status = CPUExecute(c);

    byte value_written = MemoryReadByte(m, 0x3355);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(value_written, 0x11);
    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}

TEST(T_STA_ABX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x11);
    byte x_reg = 0x45;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x55);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x33);

    int execution_status = CPUExecute(c);

    byte value_written = MemoryReadByte(m, 0x3355 + x_reg);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(value_written, 0x11);
    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}

TEST(T_STA_ABY)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 5);

    CPUSetA(c, 0x11);
    byte y_reg = 0x25;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_ABY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x55);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x33);

    int execution_status = CPUExecute(c);

    byte value_written = MemoryReadByte(m, 0x3355 + y_reg);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(value_written, 0x11);
    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}

TEST(T_STA_INX)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x78);
    byte x_reg = 0x43;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_INX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x23);
    MemoryWriteByte(m, 0x23 + x_reg, 0x43);
    MemoryWriteByte(m, 0x23 + x_reg + 1, 0x43);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte value_written = MemoryReadByte(m, 0x4343);

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(value_written, 0x78);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}

TEST(T_STA_INY)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 6);

    CPUSetA(c, 0x78);
    byte y_reg = 0x21;
    CPUSetY(c, y_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, STA_INY);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x23);
    MemoryWriteByte(m, 0x23, 0x43);
    MemoryWriteByte(m, 0x23 + 1, 0x43);

    int execution_status = CPUExecute(c);

    int cycles_remaining = ClockGetTickLimit(clk);
    byte value_written = MemoryReadByte(m, 0x4343 + y_reg);

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(value_written, 0x78);
    CHECK_EQ(cycles_remaining, 0);

    CPUFree(c, 1);
}
