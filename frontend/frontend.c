#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"

void callback(CPU c)
{
    printf("Callback\n");
    printf("\nC = %p\t", c);
    printf("A = 0x%02X\n", CPUGetA(c));
}

int main()
{

    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    ClockSetTickLimit(clk, 2);
    ClockSetMode(clk, CM_STEP_LIMIT);
    CPUSetCycleCallback(c, &callback);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x69);

    int status = CPUExecute(c);
    CPUClockTick(c);
    printf("STATUS = %d\n", status);

    // initscr();
    // cbreak();
    // noecho();

    // endwin();

    return 0;
}