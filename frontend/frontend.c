#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"
#include "string.h"

#define MIN_ROWS 15
#define MIN_COLS 45

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

// draw_stack : Draws the cpu stack
void draw_stack(CPU c, FE_CONTEXT ctx);

// draw_memory : Draws connected memory
void draw_memory(CPU c, FE_CONTEXT ctx);

// draw_too_small : Draws too small warning
void draw_too_small(FE_CONTEXT ctx);

// get_window_dimensions : Calculates window sizes and positions
int get_window_dimensions(FE_CONTEXT ctx, int *twr, int *twc, int *cwr, int *cwc, int *swr, int *swc, int *mwr, int *mwc);

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

    // Initial Window Create
    int twr, twc, cwr, cwc, swr, swc, mwr, mwc;
    int size_status = get_window_dimensions(ctx, &twr, &twc, &cwr, &cwc, &swr, &swc, &mwr, &mwc);

    if (size_status == -1)
    {
        draw_too_small(ctx);
    }

    ctx->title_window = newwin(twr, twc, 0, 0);
    ctx->cpu_window = newwin(cwr, cwc, twr, 0);
    ctx->stack_window = newwin(swr, swc, twr, cwc);
    ctx->memory_window = newwin(mwr, mwc, twr, (cwc + swc) + 1);

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
    WINDOW *titlewin = ctx->title_window;

    int rows, cols;
    getmaxyx(titlewin, rows, cols);

    box(titlewin, 0, 0);

    char *title_text = "MOS Technologies 6502 CPU Emulator";
    int title_offset = strlen(title_text) / 2;

    wattron(titlewin, A_BOLD);
    wattron(titlewin, A_UNDERLINE);
    mvwprintw(titlewin, rows / 2, (cols / 2) - title_offset, "MOS Technologies 6502 CPU Emulator");
    wattroff(titlewin, A_UNDERLINE);
    wattroff(titlewin, A_BOLD);

    wrefresh(titlewin);
}

void draw_memory(CPU c, FE_CONTEXT ctx)
{
    WINDOW *memwin = ctx->memory_window;

    box(memwin, 0, 0);

    wrefresh(memwin);
}

void draw_cpu(CPU c, FE_CONTEXT ctx)
{
    WINDOW *terminal = ctx->main;
    WINDOW *cpuwin = ctx->cpu_window;

    box(cpuwin, 0, 0);

    wrefresh(cpuwin);
}

void draw_stack(CPU c, FE_CONTEXT ctx)
{
    WINDOW *stackwin = ctx->stack_window;

    box(stackwin, 0, 0);

    wrefresh(stackwin);
}

void cycle_callback(CPU c)
{
    // Unpack Context and Check for Terminal Resize
    FE_CONTEXT ctx = (FE_CONTEXT)CPUGetEnvContext(c);

    int twr, twc, cwr, cwc, swr, swc, mwr, mwc;
    int resize_status = get_window_dimensions(ctx, &twr, &twc, &cwr, &cwc, &swr, &swc, &mwr, &mwc);

    // Screen too small
    if (resize_status == -1)
    {
        draw_too_small(ctx);
    }

    // Handle Window Resize
    if (resize_status == 1)
    {
        // Clear Windows
        wclear(ctx->main);
        wclear(ctx->title_window);
        wclear(ctx->cpu_window);
        wclear(ctx->stack_window);
        wclear(ctx->memory_window);

        // Resize
        wresize(ctx->title_window, twr, twc);
        mvwin(ctx->title_window, 0, 0);

        wresize(ctx->cpu_window, cwr, cwc);
        mvwin(ctx->cpu_window, twr, 0);

        wresize(ctx->stack_window, swr, swc);
        mvwin(ctx->stack_window, twr, cwc);

        wresize(ctx->memory_window, mwr, mwc);
        mvwin(ctx->memory_window, twr, ctx->main_cols - mwc);
    }

    // Draw Data
    draw_title(c, ctx);
    draw_cpu(c, ctx);
    draw_stack(c, ctx);
    draw_memory(c, ctx);

    refresh();
}

int get_window_dimensions(FE_CONTEXT ctx, int *twr, int *twc, int *cwr, int *cwc, int *swr, int *swc, int *mwr, int *mwc)
{

    // Get Screen Size
    int num_rows, num_cols;
    getmaxyx(ctx->main, num_rows, num_cols);

    int needs_resize = !(num_rows == ctx->main_rows && num_cols == ctx->main_cols);

    ctx->main_rows = num_rows;
    ctx->main_cols = num_cols;

    // Scale Title Window
    *twr = (num_rows / 6) > 3 ? (num_rows / 6) : 3;
    *twc = num_cols;

    // Scale CPU Window
    *cwr = num_rows - *twr - 1;
    *cwc = num_cols / 3;

    // Scale Stack Window
    *swr = *cwr;
    *swc = (num_cols - *cwc) - (num_cols / 2);

    // Scale Memory Window
    *mwr = *cwr;
    *mwc = num_cols - (*swc + *cwc) - 1;

    // Check that Screen is big enough
    if (num_rows < MIN_ROWS && num_cols < MIN_COLS)
    {
        return -1;
    }

    return needs_resize;
}

void draw_too_small(FE_CONTEXT ctx)
{
    wclear(ctx->main);
    mvwprintw(ctx->main, 1, 1, "Screen too small!");
}
