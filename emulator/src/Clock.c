#include "Clock.h"
#include "stdlib.h"
#include "EmulatorIO.h"
#include "EmulatorTypes.h"

typedef struct clock
{
    int tick_limit; // Cycles Remaining
    int period;     // Time between each tick
    int mode;       // Clock Mode
} *Clock;

Clock ClockNew()
{
    Clock clk = (Clock)malloc(sizeof(struct clock));

    if (clk == NULL)
    {
        LOG_STATUS(error_create);
        return NULL;
    }

    clk->tick_limit = 0;
    clk->period = 0;
    clk->mode = CM_FREQ_LIMIT;

    return clk;
}

int ClockFree(Clock clk)
{
    if (clk == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    free(clk);
    return ok;
}
