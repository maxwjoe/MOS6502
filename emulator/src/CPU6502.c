#include "CPU6502.h"
#include "stdlib.h"
#include "EmulatorHelper.h"

static void s_setup_op_array(CPU c);

typedef struct cpu6502
{
    // === CPU Internals ===

    word PC; // Program Counter
    byte SP; // Stack Pointer

    byte A; // Accumulator Register
    byte X; // X Register
    byte Y; // Y Register

    byte PS; // Processor Status Flags

    // === Connections ===

    Clock clk;  // Connected Clock
    Memory mem; // Connected Memory

    // === Other ===

    cpu_operation *ops; // Array of function pointers to CPU Operations

} *CPU;

CPU CPUNew()
{
    CPU c = (CPU)malloc(sizeof(struct cpu6502));

    if (c == NULL)
    {
        LOG_STATUS(error_create);
        return NULL;
    }

    c->ops = (cpu_operation *)calloc(0xFF, sizeof(cpu_operation));

    if (c->ops == NULL)
    {
        free(c);
        LOG_STATUS(error_create);
        return NULL;
    }

    c->PC = DEFAULT_PROGRAM_COUNTER;
    c->PS = DEFAULT_PROCESSOR_STATUS_FLAGS;

    c->SP = 0x00;
    c->A = 0x00;
    c->X = 0x00;
    c->Y = 0x00;

    c->clk = NULL;
    c->mem = NULL;

    s_setup_op_array(c);

    return c;
}

int CPUFree(CPU c, int free_connections)
{
    if (c == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    int free_status = ok;

    if (free_connections)
    {
        int clk_status = ClockFree(c->clk);
        int mem_status = MemoryFree(c->mem);

        if (clk_status != ok || mem_status != ok)
        {
            LOG_STATUS(error_free);
            free_status = error_free;
        }
    }

    free(c->ops);
    free(c);

    return free_status;
}

int CPUConnectMemory(CPU c, Memory m)
{
    if (c == NULL || m == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    c->mem = m;
    return ok;
}

int CPUConnectClock(CPU c, Clock clk)
{
    if (c == NULL || clk == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    c->clk = clk;
    return ok;
}

byte CPUFetchByte(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    if (c->mem == NULL || c->clk == NULL)
    {
        LOG_STATUS(error_read);
        return error_read;
    }

    byte data = MemoryReadByte(c->mem, c->PC);
    ClockTick(c->clk);
    c->PC++;

    return data;
}

word CPUFetchWord(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    if (c->mem == NULL || c->clk == NULL)
    {
        LOG_STATUS(error_read);
        return error_read;
    }

    // MOS6502 Is Little Endian

    word data = MemoryReadByte(c->mem, c->PC);
    ClockTick(c->clk);
    c->PC++;

    data |= MemoryReadByte(c->mem, c->PC) << 8;
    ClockTick(c->clk);
    c->PC++;

    return data;
}

word CPUGetPC(CPU c)
{
    HANDLE_NULL(c, -1);
    return c->PC;
}

static void s_setup_op_array(CPU c)
{
    return;
}
