#include "CPU6502.h"
#include "stdlib.h"
#include "EmulatorHelper.h"
#include "EmulatorConfig.h"
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

int CPUPushByteToStack(CPU c, byte data)
{
    HANDLE_NULL(c, error_invalid_argument);

    CPUWriteByte(c, DEFAULT_STACK_BEGIN + c->SP, data);

    c->SP--;
    CPUClockTick(c);

    return ok;
}

byte CPUPopByteFromStack(CPU c)
{
    HANDLE_NULL(c, error_invalid_argument);

    c->SP++;
    CPUClockTick(c);

    byte data = CPUReadByte(c, DEFAULT_STACK_BEGIN + c->SP);
    return data;
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
    tick_forever = 0; // Remove Later

    while (tick_forever || ClockGetTickLimit(c->clk) > 0)
    {
        byte instruction = CPUFetchByte(c);

#if !DEBUG_MODE
        if (!instruction)
        {
            CPUClockTick(c);
            continue;
        }
#endif

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

    // STX
    c->ops[STX_ZP] = &INS_STX_ZP;
    c->ops[STX_ZPY] = &INS_STX_ZPY;
    c->ops[STX_AB] = &INS_STX_AB;

    // STY
    c->ops[STY_ZP] = &INS_STY_ZP;
    c->ops[STY_ZPX] = &INS_STY_ZPX;
    c->ops[STY_AB] = &INS_STY_AB;

    // TAX
    c->ops[TAX_IMP] = &INS_TAX_IMP;

    // TAY
    c->ops[TAY_IMP] = &INS_TAY_IMP;

    // TXA
    c->ops[TXA_IMP] = &INS_TXA_IMP;

    // TYA
    c->ops[TYA_IMP] = &INS_TYA_IMP;

    // TSX
    c->ops[TSX_IMP] = &INS_TSX_IMP;

    // TXS
    c->ops[TXS_IMP] = &INS_TXS_IMP;

    // PHA
    c->ops[PHA_IMP] = &INS_PHA_IMP;

    // PHP
    c->ops[PHP_IMP] = &INS_PHP_IMP;

    // PLA
    c->ops[PLA_IMP] = &INS_PLA_IMP;

    // PLP
    c->ops[PLP_IMP] = &INS_PLP_IMP;

    // AND
    c->ops[AND_IM] = &INS_AND_IM;
    c->ops[AND_ZP] = &INS_AND_ZP;
    c->ops[AND_ZPX] = &INS_AND_ZPX;
    c->ops[AND_AB] = &INS_AND_AB;
    c->ops[AND_ABX] = &INS_AND_ABX;
    c->ops[AND_ABY] = &INS_AND_ABY;
    c->ops[AND_INX] = &INS_AND_INX;
    c->ops[AND_INY] = &INS_AND_INY;

    // EOR
    c->ops[EOR_IM] = &INS_EOR_IM;
    c->ops[EOR_ZP] = &INS_EOR_ZP;
    c->ops[EOR_ZPX] = &INS_EOR_ZPX;
    c->ops[EOR_AB] = &INS_EOR_AB;
    c->ops[EOR_ABX] = &INS_EOR_ABX;
    c->ops[EOR_ABY] = &INS_EOR_ABY;
    c->ops[EOR_INX] = &INS_EOR_INX;
    c->ops[EOR_INY] = &INS_EOR_INY;

    // ORA
    c->ops[ORA_IM] = &INS_ORA_IM;
    c->ops[ORA_ZP] = &INS_ORA_ZP;
    c->ops[ORA_ZPX] = &INS_ORA_ZPX;
    c->ops[ORA_AB] = &INS_ORA_AB;
    c->ops[ORA_ABX] = &INS_ORA_ABX;
    c->ops[ORA_ABY] = &INS_ORA_ABY;
    c->ops[ORA_INX] = &INS_ORA_INX;
    c->ops[ORA_INY] = &INS_ORA_INY;

    // BIT
    c->ops[BIT_ZP] = &INS_BIT_ZP;
    c->ops[BIT_AB] = &INS_BIT_AB;

    // ADC
    c->ops[ADC_IM] = &INS_ADC_IM;
    c->ops[ADC_ZP] = &INS_ADC_ZP;
    c->ops[ADC_ZPX] = &INS_ADC_ZPX;
    c->ops[ADC_AB] = &INS_ADC_AB;
    c->ops[ADC_ABX] = &INS_ADC_ABX;
    c->ops[ADC_ABY] = &INS_ADC_ABY;
    c->ops[ADC_INX] = &INS_ADC_INX;
    c->ops[ADC_INY] = &INS_ADC_INY;

    // SBC
    c->ops[SBC_IM] = &INS_SBC_IM;
    c->ops[SBC_ZP] = &INS_SBC_ZP;
    c->ops[SBC_ZPX] = &INS_SBC_ZPX;
    c->ops[SBC_AB] = &INS_SBC_AB;
    c->ops[SBC_ABX] = &INS_SBC_ABX;
    c->ops[SBC_ABY] = &INS_SBC_ABY;
    c->ops[SBC_INX] = &INS_SBC_INX;
    c->ops[SBC_INY] = &INS_SBC_INY;

    // CMP
    c->ops[CMP_IM] = &INS_CMP_IM;
    c->ops[CMP_ZP] = &INS_CMP_ZP;
    c->ops[CMP_ZPX] = &INS_CMP_ZPX;
    c->ops[CMP_AB] = &INS_CMP_AB;
    c->ops[CMP_ABX] = &INS_CMP_ABX;
    c->ops[CMP_ABY] = &INS_CMP_ABY;
    c->ops[CMP_INX] = &INS_CMP_INX;
    c->ops[CMP_INY] = &INS_CMP_INY;

    // CPX
    c->ops[CPX_IM] = &INS_CPX_IM;
    c->ops[CPX_ZP] = &INS_CPX_ZP;
    c->ops[CPX_AB] = &INS_CPX_AB;

    // CPY
    c->ops[CPY_IM] = &INS_CPY_IM;
    c->ops[CPY_ZP] = &INS_CPY_ZP;
    c->ops[CPY_AB] = &INS_CPY_AB;

    // INC
    c->ops[INC_ZP] = &INS_INC_ZP;
    c->ops[INC_ZPX] = &INS_INC_ZPX;
    c->ops[INC_AB] = &INS_INC_AB;
    c->ops[INC_ABX] = &INS_INC_ABX;

    // DEC
    c->ops[DEC_ZP] = &INS_DEC_ZP;
    c->ops[DEC_ZPX] = &INS_DEC_ZPX;
    c->ops[DEC_AB] = &INS_DEC_AB;
    c->ops[DEC_ABX] = &INS_DEC_ABX;

    // INX
    c->ops[INX_IMP] = &INS_INX_IMP;

    // DEX
    c->ops[DEX_IMP] = &INS_DEX_IMP;

    // INY
    c->ops[INY_IMP] = &INS_INY_IMP;

    // DEY
    c->ops[DEY_IMP] = &INS_DEY_IMP;

    // ASL
    c->ops[ASL_ACC] = &INS_ASL_ACC;
    c->ops[ASL_ZP] = &INS_ASL_ZP;
    c->ops[ASL_ZPX] = &INS_ASL_ZPX;
    c->ops[ASL_AB] = &INS_ASL_AB;
    c->ops[ASL_ABX] = &INS_ASL_ABX;

    // LSR
    c->ops[LSR_ACC] = &INS_LSR_ACC;
    c->ops[LSR_ZP] = &INS_LSR_ZP;
    c->ops[LSR_ZPX] = &INS_LSR_ZPX;
    c->ops[LSR_AB] = &INS_LSR_AB;
    c->ops[LSR_ABX] = &INS_LSR_ABX;

    // ROL
    c->ops[ROL_ACC] = &INS_ROL_ACC;
    c->ops[ROL_ZP] = &INS_ROL_ZP;
    c->ops[ROL_ZPX] = &INS_ROL_ZPX;
    c->ops[ROL_AB] = &INS_ROL_AB;
    c->ops[ROL_ABX] = &INS_ROL_ABX;

    // ROR
    c->ops[ROR_ACC] = &INS_ROR_ACC;
    c->ops[ROR_ZP] = &INS_ROR_ZP;
    c->ops[ROR_ZPX] = &INS_ROR_ZPX;
    c->ops[ROR_AB] = &INS_ROR_AB;
    c->ops[ROR_ABX] = &INS_ROR_ABX;
}
