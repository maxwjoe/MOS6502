#include "CPU6502.h"
#include "Eagle.h"

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
