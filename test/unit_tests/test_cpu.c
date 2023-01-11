#include "CPU6502.h"
#include "Eagle.h"
#include "common_macros.h"

TEST(T_CPU_CREATE)
{
    CPU c = CPUNew();

    CHECK_TRUE(c != NULL);

    CPUFree(c, 0);
}

TEST(T_CPU_FREE_ONLY)
{
    CPU c = CPUNew();

    int free_status = CPUFree(c, 0);

    CHECK_EQ(free_status, ok);
}

TEST(T_CPU_FREE_WITH_MEMORY_AND_CLOCK)
{
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectMemory(c, m);
    CPUConnectClock(c, clk);

    int free_status = CPUFree(c, 1);

    CHECK_EQ(free_status, ok);
}

TEST(T_CPU_FETCH_BYTE)
{
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    ClockSetTickLimit(clk, 5);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, 0x33);

    byte fetched_data = CPUFetchByte(c);
    word prog_counter = CPUGetPC(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(fetched_data, 0x33);
    CHECK_EQ(prog_counter, DEFAULT_PROGRAM_COUNTER + 1);
    CHECK_EQ(cycles_remaining, 4);

    CPUFree(c, 1);
}

TEST(T_CPU_FETCH_WORD)
{
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, 0x11);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x22);

    word data_read = CPUFetchWord(c);

    word prog_counter = CPUGetPC(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(data_read, 0x2211);
    CHECK_EQ(prog_counter, DEFAULT_PROGRAM_COUNTER + 2);
    CHECK_EQ(cycles_remaining, 1);

    CPUFree(c, 1);
}

TEST(T_CPU_READ_BYTE)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, 0xAAAA, 0x65);
    byte data_read = CPUReadByte(c, 0xAAAA);
    word prog_counter = CPUGetPC(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(data_read, 0x65);
    CHECK_EQ(prog_counter, DEFAULT_PROGRAM_COUNTER);
    CHECK_EQ(cycles_remaining, 2);

    CPUFree(c, 1);
}

TEST(T_CPU_READ_WORD)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, 0x65);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x33);

    word word_read = CPUReadWord(c, DEFAULT_PROGRAM_COUNTER);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(word_read, 0x3365);
    CHECK_EQ(cycles_remaining, 1);

    CPUFree(c, 1);
}

TEST(T_CPU_WRITE_BYTE)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUWriteByte(c, 0x4444, 0x11);
    byte data_written = MemoryReadByte(m, 0x4444);
    word prog_counter = CPUGetPC(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    CHECK_EQ(data_written, 0x11);
    CHECK_EQ(prog_counter, DEFAULT_PROGRAM_COUNTER);
    CHECK_EQ(cycles_remaining, 2);

    CPUFree(c, 1);
}

TEST(T_CPU_SET_AND_READ_STATUS_REG)
{
    SETUP_HW();

    CPUSetStatusRegister(c, 0x13);
    byte status_register = CPUGetStatusRegister(c);

    CHECK_EQ(status_register, 0x13);

    CPUFree(c, 1);
}

TEST(T_CPU_SET_AND_READ_FLAGS)
{
    SETUP_HW();

    CPUSetStatusFlag(c, PS_N, 1);
    int neg_flag = CPUGetStatusFlag(c, PS_N);

    CPUSetStatusFlag(c, PS_Z, 0);
    int zero_flag = CPUGetStatusFlag(c, PS_Z);

    CHECK_TRUE(neg_flag);
    CHECK_FALSE(zero_flag);

    CPUFree(c, 1);
}
