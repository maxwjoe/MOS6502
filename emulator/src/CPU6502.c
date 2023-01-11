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

    byte data = MemoryReadByte(c->mem, c->PC);
    ClockTick(c->clk);
    c->PC++;

    return data;
}

word CPUFetchWord(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    // MOS6502 Is Little Endian

    word data = MemoryReadByte(c->mem, c->PC);
    ClockTick(c->clk);
    c->PC++;

    data |= MemoryReadByte(c->mem, c->PC) << 8;
    ClockTick(c->clk);
    c->PC++;

    return data;
}

byte CPUReadByte(CPU c, word address)
{
    HANDLE_NULL(c, error_invalid_argument);

    byte data = MemoryReadByte(c->mem, address);
    ClockTick(c->clk);

    return data;
}

int CPUWriteByte(CPU c, word address, byte data)
{
    HANDLE_NULL(c, error_invalid_argument);

    int status_code = MemoryWriteByte(c->mem, address, data);
    ClockTick(c->clk);

    return status_code;
}

int CPUSetStatusFlag(CPU c, int flag_id, int flag_value)
{
    HANDLE_NULL(c, error_invalid_argument);

    if (flag_id < 0 || flag_id > 7)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    if (flag_value)
    {
        c->PS |= 1 << flag_id;
        return ok;
    }

    c->PS &= ~(1 << flag_id);
    return ok;
}

byte CPUGetStatusRegister(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    return c->PS;
}

int CPUSetStatusRegister(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);

    c->PS = val;
    return ok;
}

int CPUGetStatusFlag(CPU c, int flag_id)
{
    HANDLE_NULL(c, error_invalid_argument);

    if (flag_id < 0 || flag_id > 7)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    return (c->PS >> flag_id) & 0x01;
}

Clock CPUGetClock(CPU c)
{
    HANDLE_NULL(c, NULL);

    return c->clk;
}

Memory CPUGetMemory(CPU c)
{
    HANDLE_NULL(c, NULL);

    return c->mem;
}

int CPUIncrementPC(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    return ++c->PC;
}

int CPUIncrementSP(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    return ++c->SP;
}

int CPUSetPC(CPU c, word val)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->PC = val;
    return ok;
}

int CPUSetSP(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->SP = val;
    return ok;
}

int CPUSetA(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->A = val;
    return ok;
}

int CPUSetX(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->X = val;
    return ok;
}

int CPUSetY(CPU c, byte val)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->Y = val;
    return ok;
}

word CPUGetPC(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->PC;
}

byte CPUGetSP(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->SP;
}

byte CPUGetA(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->A;
}

byte CPUGetX(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->X;
}

byte CPUGetY(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->Y;
}

static void s_setup_op_array(CPU c)
{
    return;
}
