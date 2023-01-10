#include "Eagle.h"
#include "Clock.h"
#include "EmulatorTypes.h"

TEST(T_CLOCK_CREATE)
{
    Clock clk = ClockNew();

    CHECK_TRUE(clk != NULL);

    ClockFree(clk);
}

TEST(T_CLOCK_FREE)
{
    Clock clk = ClockNew();

    int status_code = ClockFree(clk);

    CHECK_EQ(status_code, ok);
}
