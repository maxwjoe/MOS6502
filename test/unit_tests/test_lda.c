#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"

TEST(T_LDA_IM)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x99);

    CPUExecute(c);

    byte a_register = CPUGetA(c);
    int cycles_remaining = ClockGetTickLimit(clk);
    GET_ALL_FLAGS();

    CHECK_EQ(a_register, 0x99);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}