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
