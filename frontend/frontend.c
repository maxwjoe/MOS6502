#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"

// FE_CONTEXT : Context for the frontend to be passed to the cpu
typedef struct fe_context
{
    WINDOW *register_window;
} *FE_CONTEXT;

void callback(CPU c)
{
    FE_CONTEXT ctx = (FE_CONTEXT)CPUGetEnvContext(c);

    mvwprintw(ctx->register_window, 1, 1, "A : %X", CPUGetA(c));
    wrefresh(ctx->register_window);
}

int main()
{
    // Setup UI
    initscr();
    cbreak();
    noecho();

    // Setup Hardware
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    ClockSetTickLimit(clk, 2);
    ClockSetMode(clk, CM_STEP_LIMIT);
    CPUSetCycleCallback(c, &callback);

    // Setup Frontend Context
    FE_CONTEXT ctx = (FE_CONTEXT)malloc(sizeof(struct fe_context));

    if (ctx == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int s_rows, s_cols;
    getmaxyx(stdscr, s_rows, s_cols);

    ctx->register_window = newwin(s_rows, s_cols / 2, 0, s_cols / 2);
    box(ctx->register_window, 0, 0);

    refresh();

    CPUSetEnvContext(c, (void *)ctx);

    // Program Memory
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_IM);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x69);

    // Execute Program
    CPUExecute(c);
    CPUClockTick(c);

    free(ctx);
    endwin();

    return 0;
}