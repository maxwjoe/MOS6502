#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"

// === Declarations ===

// FE_CONTEXT : Context for the frontend to be passed to the cpu
typedef struct fe_context
{
    WINDOW *main;
    WINDOW *title_window;
    WINDOW *cpu_window;
    WINDOW *memory_window;
    WINDOW *stack_window;
    int cycles;
    int main_rows;
    int main_cols;
    int main_s_row;
    int main_s_col;
} *FE_CONTEXT;

// cycle_callback : Callback function to execute on each CPU Cycle
void cycle_callback(CPU c);

// draw_title : Draws the title window
void draw_title(CPU c, FE_CONTEXT ctx);

// draw_cpu : Draws the cpu window
void draw_cpu(CPU c, FE_CONTEXT ctx);

// get_window_dimensions : Calculates window sizes and positions
void get_window_dimensions(FE_CONTEXT ctx, int *twr, int *twc, int *cwr, int *cwc);

// === Main ===

int main()
{
    // Initialise UI
    initscr();
    cbreak();
    noecho();

    if (!has_colors())
    {
        exit(EXIT_FAILURE);
    }

    start_color();
    curs_set(0);

    // Setup Hardware
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();
    ClockSetMode(clk, CM_STEP_NO_LIMIT);

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    // Add Context, Windows and Callback to CPU
    FE_CONTEXT ctx = (FE_CONTEXT)malloc(sizeof(struct fe_context));

    if (!ctx)
    {
        exit(EXIT_FAILURE);
    }

    ctx->cycles = 0;
    ctx->main = stdscr;

    getmaxyx(stdscr, ctx->main_rows, ctx->main_cols);
    getbegyx(stdscr, ctx->main_s_row, ctx->main_s_col);

    ctx->title_window = newwin(ctx->main_rows / 5, ctx->main_cols, ctx->main_s_row, ctx->main_s_col);
    ctx->cpu_window = newwin(3 * ctx->main_rows / 5, ctx->main_cols / 3, ctx->main_rows / 5, 0);

    refresh();

    CPUSetEnvContext(c, (void *)ctx);
    CPUSetCycleCallback(c, &cycle_callback);

    // Tick Clock once to see static layout
    CPUExecute(c);

    // Cleanup
    getch();
    endwin();
    free(ctx);

    return 0;
}

// === Function Definitions ===

void draw_title(CPU c, FE_CONTEXT ctx)
{
    WINDOW *terminal = ctx->main;
    WINDOW *titlewin = ctx->title_window;

    box(titlewin, 0, 0);

    wrefresh(titlewin);
}

void draw_cpu(CPU c, FE_CONTEXT ctx)
{
    WINDOW *terminal = ctx->main;
    WINDOW *cpuwin = ctx->cpu_window;

    box(cpuwin, 0, 0);

    wrefresh(cpuwin);
}

void cycle_callback(CPU c)
{
    // Unpack Context and Check for Terminal Resize
    FE_CONTEXT ctx = (FE_CONTEXT)CPUGetEnvContext(c);

    int rs, cs;

    getmaxyx(ctx->main, rs, cs);

    if (rs != ctx->main_rows || cs != ctx->main_cols)
    {
        // Update Sizes
        ctx->main_rows = rs;
        ctx->main_cols = cs;

        // Clear Windows
        wclear(ctx->main);
        wclear(ctx->title_window);
        wclear(ctx->cpu_window);

        // Resize Windows
        int twr, twc, cwr, cwc;
        twr = rs / 5;
        twc = cs;
        cwr = rs - twr;
        cwc = cs / 3;

        wresize(ctx->title_window, twr, twc);
        wresize(ctx->cpu_window, cwr, cwc);

        // Refresh Windows
        wrefresh(ctx->main);
        wrefresh(ctx->title_window);
        wrefresh(ctx->cpu_window);
    }

    // Draw Data
    draw_title(c, ctx);
    draw_cpu(c, ctx);
}

void get_window_dimensions(FE_CONTEXT ctx, int *twr, int *twc, int *cwr, int *cwc)
{
}
