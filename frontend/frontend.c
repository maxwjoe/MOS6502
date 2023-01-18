#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "CPU6502.h"

// === Declarations ===

// FE_CONTEXT : Context for the frontend to be passed to the cpu
typedef struct fe_context
{
    WINDOW *stdscr;
    WINDOW *register_window;
    WINDOW *memory_window;
    WINDOW *stack_window;
} *FE_CONTEXT;

// cycle_callback : Callback function to execute on each CPU Cycle
void cycle_callback(CPU c);

// print_registers : Prints registers to the register window
void print_registers(CPU c);

// print_memory : Prints memory around the program counter
void print_memory(CPU c);

// print_stack : Prints the stack about the stack pointer
void print_stack(CPU c);

// === Main ===

int main()
{
    // Setup UI
    initscr();
    cbreak();
    noecho();

    if (!has_colors())
    {
        exit(EXIT_FAILURE);
    }

    start_color();
    curs_set(0);
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);

    // Setup Hardware
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();

    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);

    // Setup Windows and Context
    FE_CONTEXT ctx = (FE_CONTEXT)malloc(sizeof(struct fe_context));

    if (!ctx)
    {
        exit(EXIT_FAILURE);
    }

    int s_rows, s_cols;
    getmaxyx(stdscr, s_rows, s_cols);

    ctx->stdscr = stdscr;
    ctx->register_window = newwin(s_rows / 2, s_cols / 3, 0, 2 * s_cols / 3);
    ctx->stack_window = newwin(s_rows / 2, s_cols / 3, 0, 2 * s_cols / 3);
    ctx->memory_window = newwin(s_rows, 2 * s_cols / 3, 0, 0);

    refresh();

    CPUSetEnvContext(c, ctx);
    CPUSetCycleCallback(c, &cycle_callback);

    // Program Memory

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, JSR_AB);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0x32);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x45);
    MemoryWriteByte(m, 0x4532, LDA_IM);
    MemoryWriteByte(m, 0x4532 + 1, 0x01);
    MemoryWriteByte(m, 0x4532 + 2, ADC_IM);
    MemoryWriteByte(m, 0x4532 + 3, 0x02);

    ClockSetTickLimit(clk, 6);
    ClockSetMode(clk, CM_STEP_NO_LIMIT);

    CPUExecute(c);
    CPUClockTick(c);

    // Cleanup
    getch();
    endwin();

    return 0;
}

// === Function Definitions ===

void print_stack(CPU c)
{
    // Unpack Windows
    FE_CONTEXT ctx = CPUGetEnvContext(c);

    if (!ctx)
    {
        exit(EXIT_FAILURE);
    }

    WINDOW *stkwin = ctx->stack_window;
    WINDOW *terminal = ctx->stdscr;
    Memory mem_ptr = CPUGetMemory(c);

    int stk_rows, stk_cols;
    int start_row, start_col;
    getbegyx(stkwin, stk_rows, stk_cols);
    getmaxyx(stkwin, start_row, start_col);

    wclear(stkwin);
    box(stkwin, 0, 0);

    wrefresh(stkwin);
}

void print_memory(CPU c)
{
    // Unpack Windows
    FE_CONTEXT ctx = CPUGetEnvContext(c);

    if (!ctx)
    {
        exit(EXIT_FAILURE);
    }

    WINDOW *memwin = ctx->memory_window;
    WINDOW *terminal = ctx->stdscr;
    Memory mem_ptr = CPUGetMemory(c);

    int mem_rows, mem_cols;
    int start_row, start_col;
    getbegyx(memwin, start_row, start_col);
    getmaxyx(memwin, mem_rows, mem_cols);

    // Clear, Draw Border
    wclear(memwin);
    box(memwin, 0, 0);

    // Draw Heading
    wattron(memwin, A_BOLD);
    wattron(memwin, A_UNDERLINE);
    mvwprintw(memwin, start_row + 1, start_col + 2, "Connected Memory");
    wattroff(memwin, A_BOLD);
    wattroff(memwin, A_UNDERLINE);

    // Draw Address Space
    int address_rows = mem_rows - 5;
    word prog_counter = CPUGetPC(c);

    word start_address = prog_counter & 0xFFF0;

    word addr_i = start_address;
    int curr_row = 0;

    while (curr_row < address_rows)
    {
        // Print Address
        wattron(memwin, A_BOLD);
        mvwprintw(memwin, start_row + 3 + curr_row, start_col + 2, "0x%04X :", addr_i);
        wattroff(memwin, A_BOLD);

        // Print Data
        for (byte i = 0x00; i <= 0x0F; i++)
        {
            int is_pc = ((addr_i + i) == prog_counter);

            if (is_pc)
            {
                wattron(memwin, COLOR_PAIR(1));
            }
            mvwprintw(memwin, start_row + 3 + curr_row, start_col + 12 + (5 * i), "0x%02X", MemoryReadByte(mem_ptr, addr_i + i));
            if (is_pc)
            {
                wattroff(memwin, COLOR_PAIR(1));
            }
        }

        addr_i += 0x0010;
        curr_row++;
    }

    wrefresh(memwin);
}

void print_registers(CPU c)
{
    // Unpack Windows
    FE_CONTEXT ctx = CPUGetEnvContext(c);

    if (!ctx)
    {
        exit(EXIT_FAILURE);
    }

    WINDOW *regwin = ctx->register_window;
    WINDOW *terminal = ctx->stdscr;

    int reg_rows, reg_cols;
    int start_row = 1;
    getmaxyx(regwin, reg_rows, reg_cols);

    // Clear and Draw Border
    wclear(regwin);
    box(regwin, 0, 0);

    // Draw Internal Registers
    wattron(regwin, A_UNDERLINE);
    wattron(regwin, A_BOLD);
    mvwprintw(regwin, start_row, 2, "Internal Registers");
    wattroff(regwin, A_BOLD);
    wattroff(regwin, A_UNDERLINE);

    // Draw Titles
    mvwprintw(regwin, start_row + 2, 2, "Program Counter :");
    mvwprintw(regwin, start_row + 3, 2, "Stack Pointer :");
    mvwprintw(regwin, start_row + 4, 2, "Accumulator :");
    mvwprintw(regwin, start_row + 5, 2, "X Register :");
    mvwprintw(regwin, start_row + 6, 2, "Y Register :");

    // Draw Values
    wattron(regwin, A_BOLD);
    mvwprintw(regwin, start_row + 2, reg_cols - 10, "0x%04X", CPUGetPC(c));
    mvwprintw(regwin, start_row + 3, reg_cols - 10, "0x%02X", CPUGetSP(c));
    mvwprintw(regwin, start_row + 4, reg_cols - 10, "0x%02X", CPUGetA(c));
    mvwprintw(regwin, start_row + 5, reg_cols - 10, "0x%02X", CPUGetX(c));
    mvwprintw(regwin, start_row + 6, reg_cols - 10, "0x%02X", CPUGetY(c));
    wattroff(regwin, A_BOLD);

    // Draw Processor Status
    wattron(regwin, A_UNDERLINE);
    wattron(regwin, A_BOLD);
    mvwprintw(regwin, start_row + 10, 2, "Processor Flags");
    wattroff(regwin, A_BOLD);
    wattroff(regwin, A_UNDERLINE);

    // Draw Titles
    mvwprintw(regwin, start_row + 12, 2, "Carry :");
    mvwprintw(regwin, start_row + 13, 2, "Zero :");
    mvwprintw(regwin, start_row + 14, 2, "Interrupt Enable :");
    mvwprintw(regwin, start_row + 15, 2, "Decimal Mode :");
    mvwprintw(regwin, start_row + 16, 2, "Break :");
    mvwprintw(regwin, start_row + 17, 2, "Overflow :");
    mvwprintw(regwin, start_row + 18, 2, "Negative :");
    mvwprintw(regwin, start_row + 19, 2, "Unused :");

    // Draw Values
    wattron(regwin, A_BOLD);
    mvwprintw(regwin, start_row + 12, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_C));
    mvwprintw(regwin, start_row + 13, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_Z));
    mvwprintw(regwin, start_row + 14, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_I));
    mvwprintw(regwin, start_row + 15, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_D));
    mvwprintw(regwin, start_row + 16, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_B));
    mvwprintw(regwin, start_row + 17, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_V));
    mvwprintw(regwin, start_row + 18, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_N));
    mvwprintw(regwin, start_row + 19, reg_cols - 10, "%d", CPUGetStatusFlag(c, PS_U));
    wattron(regwin, A_BOLD);

    wrefresh(regwin);
}

void cycle_callback(CPU c)
{
    print_registers(c);
    print_memory(c);
    print_stack(c);
}
