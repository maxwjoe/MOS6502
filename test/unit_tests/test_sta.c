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
}

TEST(T_STA_AB)
{
}

TEST(T_STA_ABX)
{
}

/*
Problem : STA_ABX does not require an extra cycle on page cross
You have put the extra cycle inside the ABX addressing function which is wrong
Instead, set a flag on CPU struct that an extra cycle is needed (do it inside ADDR_ABX)
Following this, inside the OPER_LDA for example, set a flag that an extra cycle COULD BE needed

inside the execution loop, check that both flags are high, if both are high do the extra cycle
Set both back to low again regardless

*/