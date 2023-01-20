#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"
#include "string.h"

#define MIN_ROWS 15
#define MIN_COLS 45

#define TEST_PROGRAM_PATH "../programs/6502_binaries/6502_functional_test.bin"

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
    int mem_capacity;
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

// draw_cpu_flag : Draws a status flag
void draw_cpu_flag(WINDOW *w, int r, int c, char *text, int flag_level);

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

    // Setup Color Pairs
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Flag == 1
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Flag == 0
    init_pair(3, COLOR_BLACK, COLOR_YELLOW); // Stack Pointer

    // Setup Hardware
    int mem_capacity = 0xFFFF;

    CPU c = CPUNew();
    Memory m = MemoryNew(mem_capacity);
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
    ctx->mem_capacity = mem_capacity;
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

    // Load Program into Memory
    MemoryLoadBinary(m, TEST_PROGRAM_PATH);
    CPUSetPC(c, 0x400);

    // Run
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

    Memory mem_ptr = CPUGetMemory(c);

    int start_row = 1;
    int start_col = 1;

    int m_rows, m_cols;
    getmaxyx(memwin, m_rows, m_cols);

    // Memory Heading
    wattron(memwin, A_BOLD);
    wattron(memwin, A_UNDERLINE);
    mvwprintw(memwin, start_row, start_col, "Connected Memory");
    wattroff(memwin, A_BOLD);
    wattroff(memwin, A_UNDERLINE);

    // Calculate Memory Width
    int addr_per_row = (m_cols - 1 - start_col - 6) / 5 < 0x0010 ? (m_cols - 1 - start_col - 6) / 5 : 0x0010;
    int mem_rows = m_rows - 6;

    // Calculate Range
    word prog_counter = CPUGetPC(c);
    word start_addr = prog_counter & 0xFFF0;

    // Draw Offsets
    wattron(memwin, A_BOLD);
    for (int o = 0; o < addr_per_row; o++)
    {
        mvwprintw(memwin, start_row + 2, start_col + 10 + (5 * o), "0x%02X", (word)o);
    }
    wattron(memwin, A_BOLD);

    // Draw Memory
    word offset = 0;
    for (int r = 0; r < mem_rows; r++)
    {
        word curr_addr = (word)(start_addr + offset);
        // Draw Start Address
        wattron(memwin, A_BOLD);
        mvwprintw(memwin, start_row + 4 + r, start_col + 1, "0x%04X  ", curr_addr);
        wattroff(memwin, A_BOLD);

        // Draw Data
        for (int c = 0; c < addr_per_row; c++)
        {
            word addr = (word)(curr_addr + c);

            if (addr == prog_counter)
            {
                wattron(memwin, COLOR_PAIR(3));
            }
            mvwprintw(memwin, start_row + 4 + r, start_col + 10 + (5 * c), "0x%02X", MemoryReadByte(mem_ptr, addr));
            if (addr == prog_counter)
            {
                wattroff(memwin, COLOR_PAIR(3));
            }
        }

        offset += 0x0010;
    }

    wrefresh(memwin);
}

void draw_cpu(CPU c, FE_CONTEXT ctx)
{
    WINDOW *cpuwin = ctx->cpu_window;
    box(cpuwin, 0, 0);

    Memory mem_ptr = CPUGetMemory(c);

    int start_row = 1;
    int start_col = 1;

    int m_r, m_c;
    getmaxyx(cpuwin, m_r, m_c);

    // Internal Register Heading
    wattron(cpuwin, A_BOLD);
    wattron(cpuwin, A_UNDERLINE);
    mvwprintw(cpuwin, start_row, start_col, "Internal Registers");
    wattroff(cpuwin, A_BOLD);
    wattroff(cpuwin, A_UNDERLINE);

    // Draw Register Headings
    mvwprintw(cpuwin, start_row + 2, start_col, "Program Counter :");
    mvwprintw(cpuwin, start_row + 3, start_col, "Stack Pointer :");

    mvwprintw(cpuwin, start_row + 5, start_col, "A Register :");
    mvwprintw(cpuwin, start_row + 6, start_col, "X Register :");
    mvwprintw(cpuwin, start_row + 7, start_col, "Y Register :");
    mvwprintw(cpuwin, start_row + 9, start_col, "CPU Status :");

    // Register Values
    mvwprintw(cpuwin, start_row + 2, m_c - 8, "0x%04X", CPUGetPC(c));
    mvwprintw(cpuwin, start_row + 3, m_c - 6, "0x%02X", CPUGetSP(c));

    mvwprintw(cpuwin, start_row + 5, m_c - 6, "0x%02X", CPUGetA(c));
    mvwprintw(cpuwin, start_row + 6, m_c - 6, "0x%02X", CPUGetX(c));
    mvwprintw(cpuwin, start_row + 7, m_c - 6, "0x%02X", CPUGetY(c));

    // Status Values
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 17, "C", CPUGetStatusFlag(c, PS_C));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 15, "Z", CPUGetStatusFlag(c, PS_Z));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 13, "I", CPUGetStatusFlag(c, PS_I));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 11, "D", CPUGetStatusFlag(c, PS_D));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 9, "B", CPUGetStatusFlag(c, PS_V));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 7, "V", CPUGetStatusFlag(c, PS_B));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 5, "N", CPUGetStatusFlag(c, PS_N));
    draw_cpu_flag(cpuwin, start_row + 9, m_c - 3, "U", CPUGetStatusFlag(c, PS_U));
    mvwprintw(cpuwin, start_row + 10, m_c - 8, "[0x%02X]", CPUGetStatusRegister(c));

    // Vectors
    wattron(cpuwin, A_BOLD);
    wattron(cpuwin, A_UNDERLINE);
    mvwprintw(cpuwin, start_row + 12, start_col, "Vectors");
    wattroff(cpuwin, A_BOLD);
    wattroff(cpuwin, A_UNDERLINE);

    word reset_vec = MemoryReadByte(mem_ptr, DEFAULT_PROGRAM_COUNTER) & 0x00FF;
    reset_vec |= (MemoryReadByte(mem_ptr, DEFAULT_PROGRAM_COUNTER + 1) << 8);

    word irq_vec = MemoryReadByte(mem_ptr, IRQ_VECTOR_START) & 0x00FF;
    irq_vec |= (MemoryReadByte(mem_ptr, IRQ_VECTOR_START + 1) << 8);

    word nmi_vec = MemoryReadByte(mem_ptr, NMI_VECTOR_START) & 0x00FF;
    nmi_vec |= (MemoryReadByte(mem_ptr, NMI_VECTOR_START + 1) << 8);

    mvwprintw(cpuwin, start_row + 14, start_col, "Reset :");
    mvwprintw(cpuwin, start_row + 14, m_c - 8, "0x%04X", reset_vec);
    mvwprintw(cpuwin, start_row + 15, start_col, "IRQ :");
    mvwprintw(cpuwin, start_row + 15, m_c - 8, "0x%04X", irq_vec);
    mvwprintw(cpuwin, start_row + 16, start_col, "NMI :");
    mvwprintw(cpuwin, start_row + 16, m_c - 8, "0x%04X", nmi_vec);

    // CPU Connections
    wattron(cpuwin, A_BOLD);
    wattron(cpuwin, A_UNDERLINE);
    mvwprintw(cpuwin, start_row + 18, start_col, "Connected Devices");
    wattroff(cpuwin, A_BOLD);
    wattroff(cpuwin, A_UNDERLINE);

    mvwprintw(cpuwin, start_row + 20, start_col, "Clock Cycles :");
    mvwprintw(cpuwin, start_row + 20, m_c - 7, "%05d", ctx->cycles);
    mvwprintw(cpuwin, start_row + 21, start_col, "Memory Capacity :");
    mvwprintw(cpuwin, start_row + 21, m_c - 8, "0x%04X", ctx->mem_capacity);

    wrefresh(cpuwin);
}

void draw_stack(CPU c, FE_CONTEXT ctx)
{
    WINDOW *stackwin = ctx->stack_window;
    box(stackwin, 0, 0);

    Memory mem_ptr = CPUGetMemory(c);
    int start_row = 1;
    int start_col = 1;

    int sw_rows, sw_cols;
    getmaxyx(stackwin, sw_rows, sw_cols);

    // Window Title
    wattron(stackwin, A_BOLD);
    wattron(stackwin, A_UNDERLINE);
    mvwprintw(stackwin, start_row, start_col, "Stack");
    wattroff(stackwin, A_BOLD);
    wattroff(stackwin, A_UNDERLINE);

    // Calculate Address Range
    int num_addresses = sw_rows - 4;
    byte stack_ptr = CPUGetSP(c);

    byte lo_addr = stack_ptr - (num_addresses / 2);

    // Print Data
    for (int i = 0; i < num_addresses; i++)
    {
        byte curr_addr = (byte)(lo_addr + i);
        if (curr_addr == stack_ptr)
        {
            wattron(stackwin, COLOR_PAIR(3));
        }
        mvwprintw(stackwin, start_row + 2 + i, start_col + 1, "0x%02X : ", curr_addr);
        mvwprintw(stackwin, start_row + 2 + i, sw_cols - 6, "0x%02X", MemoryReadByte(mem_ptr, DEFAULT_STACK_BEGIN + curr_addr));

        if (curr_addr == stack_ptr)
        {
            // Fill whitespace
            int string_length = strlen("0x%02X");
            for (int s = start_col + 1 + string_length; s < sw_cols - 6; s++)
            {
                mvwprintw(stackwin, start_row + 2 + i, s, " ");
            }

            wattroff(stackwin, COLOR_PAIR(3));
        }
    }

    wrefresh(stackwin);
}

void cycle_callback(CPU c)
{
    // Unpack Context and Check for Terminal Resize
    FE_CONTEXT ctx = (FE_CONTEXT)CPUGetEnvContext(c);
    ctx->cycles++;

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
        mvwin(ctx->memory_window, twr, ctx->main_cols - mwc - 1);
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
    *cwc = num_cols / 4;

    // Scale Stack Window
    *swr = *cwr;
    *swc = ((num_cols - *cwc) / 4) < 20 ? ((num_cols - *cwc) / 4) : 20;

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

void draw_cpu_flag(WINDOW *w, int r, int c, char *text, int flag_level)
{
    wattron(w, A_BOLD);
    if (flag_level)
    {
        wattron(w, COLOR_PAIR(1));
    }
    else
    {
        wattron(w, COLOR_PAIR(2));
    }

    mvwprintw(w, r, c, text);

    if (flag_level)
    {
        wattroff(w, COLOR_PAIR(1));
    }
    else
    {
        wattroff(w, COLOR_PAIR(2));
    }
    wattroff(w, A_BOLD);
}
