#include "Eagle.h"
#include "Clock.h"

TEST(T_CLOCK_CREATE)
{
    Clock clk = ClockNew();

    CHECK_TRUE(clk != NULL);

    ClockFree(clk);
}
