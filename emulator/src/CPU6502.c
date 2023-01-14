#include "CPU6502.h"
#include "stdlib.h"
#include "EmulatorHelper.h"
#include "Instructions.h"

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

    int cycle_penalty;  // Flag to indicate additional cycle required
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

word CPUReadWord(CPU c, word address)
{
    HANDLE_NULL(c, error_invalid_argument);

    word data = MemoryReadByte(c->mem, address);
    CPUClockTick(c);
    address++;

    data |= MemoryReadByte(c->mem, address) << 8;
    CPUClockTick(c);

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

int CPUClockTick(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    ClockTick(c->clk);
    return ok;
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

int CPUSetCyclePenalty(CPU c, int value)
{
    HANDLE_NULL(c, error_invalid_argument);
    c->cycle_penalty = value;
}

int CPUGetCyclePenalty(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);
    return c->cycle_penalty;
}

int CPUExecute(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    int tick_forever = ClockGetMode(c->clk);

    while (tick_forever || ClockGetTickLimit(c->clk) > 0)
    {
        byte instruction = CPUFetchByte(c);

        cpu_operation func = c->ops[instruction];

        if (!func)
        {
            // LOG_STATUS(error_invalid_op_code);
            return error_invalid_op_code;
        }

        func(c);
        CPUSetCyclePenalty(c, 0);
    }

    return ok;
}

static void s_setup_op_array(CPU c)
{
    if (c == NULL)
    {
        return;
    }

    // LDA
    c->ops[LDA_IM] = &INS_LDA_IM;
    c->ops[LDA_ZP] = &INS_LDA_ZP;
    c->ops[LDA_ZPX] = &INS_LDA_ZPX;
    c->ops[LDA_AB] = &INS_LDA_AB;
    c->ops[LDA_ABX] = &INS_LDA_ABX;
    c->ops[LDA_ABY] = &INS_LDA_ABY;
    c->ops[LDA_INX] = &INS_LDA_INX;
    c->ops[LDA_INY] = &INS_LDA_INY;

    // LDX
    c->ops[LDX_IM] = &INS_LDX_IM;
    c->ops[LDX_ZP] = &INS_LDX_ZP;
    c->ops[LDX_ZPY] = &INS_LDX_ZPY;
    c->ops[LDX_AB] = &INS_LDX_AB;
    c->ops[LDX_ABY] = &INS_LDX_ABY;

    // LDY
    c->ops[LDY_IM] = &INS_LDY_IM;
    c->ops[LDY_ZP] = &INS_LDY_ZP;
    c->ops[LDY_ZPX] = &INS_LDY_ZPX;
    c->ops[LDY_AB] = &INS_LDY_AB;
    c->ops[LDY_ABX] = &INS_LDY_ABX;

    // STA
    c->ops[STA_ZP] = &INS_STA_ZP;
    c->ops[STA_ZPX] = &INS_STA_ZPX;
    c->ops[STA_AB] = &INS_STA_AB;
    c->ops[STA_ABX] = &INS_STA_ABX;
    c->ops[STA_ABY] = &INS_STA_ABY;
    c->ops[STA_INX] = &INS_STA_INX;
    c->ops[STA_INY] = &INS_STA_INY;
}
