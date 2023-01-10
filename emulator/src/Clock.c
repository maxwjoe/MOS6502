#include "Clock.h"
#include "stdlib.h"
#include "EmulatorHelper.h"
#include "EmulatorTypes.h"

static void s_clock_delay(int ms);

typedef struct clock
{
    int tick_limit; // Ticks Remaining
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

int ClockTick(Clock clk)
{
    HANDLE_NULL(clk, -1)

    switch (clk->mode)
    {
    case CM_FREQ_LIMIT:
        s_clock_delay(clk->period);
        clk->tick_limit--;
        break;
    case CM_FREQ_NO_LIMIT:
        s_clock_delay(clk->period);
        break;
    case CM_STEP_LIMIT:
        // Implement
        break;
    case CM_STEP_NO_LIMIT:
        // Implement
        break;
    default:
        LOG_STATUS(error_generic);
        return -1;
    }
}

int ClockSetTickLimit(Clock clk, int tick_limit)
{
    HANDLE_NULL(clk, error_invalid_argument);

    clk->tick_limit = tick_limit;
    return ok;
}

int ClockGetTickLimit(Clock clk)
{
    HANDLE_NULL(clk, -1);
    return clk->tick_limit;
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

static void s_clock_delay(int ms)
{
    return;
}
