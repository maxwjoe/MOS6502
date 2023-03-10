#ifndef CLOCK_H
#define CLOCK_H

typedef struct clock *Clock;

enum clock_modes
{
    CM_FREQ_LIMIT,    // Clock ticks at given frequency a specified number of times
    CM_FREQ_NO_LIMIT, // Clock ticks at a given frequency forever
    CM_STEP_LIMIT,    // Clock ticks on keypress a specified number of times
    CM_STEP_NO_LIMIT  // Clock ticks on keypress forever
};

// ClockNew : Creates a new clock object and returns a pointer
Clock ClockNew();

// ClockSetMode : Sets the clock mode
int ClockSetMode(Clock clk, int clock_mode);

// ClockGetMode : Gets the clock mode
int ClockGetMode(Clock clk);

// ClockSetPeriod : Sets the clock period (ms)
int ClockSetPeriod(Clock clk, int period);

// ClockSetTickLimit : Sets the tick limit
int ClockSetTickLimit(Clock clk, int tick_limit);

// ClockTick : Ticks the clock and returns remaining ticks (-1 if result should be disregarded)
int ClockTick(Clock clk);

// ClockGetTickLimit : Returns the tick_limit (Remaining ticks)
int ClockGetTickLimit(Clock clk);

// ClockFree : Frees a clock object
int ClockFree(Clock clk);

#endif