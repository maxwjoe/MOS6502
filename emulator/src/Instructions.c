#include "Instructions.h"
#include "AddressModes.h"
#include "Operations.h"
#include "CPU6502.h"
#include "stdio.h"

/*
File : Instructions
Description : Code to be executed in emulating an individual CPU Instruction

Notes :

1. Writing with offset (eg. STA_ABX) requires an additional CPU Cycle after addressing.
This is to emulate the 6502 checking that no overflow has occurred in the low byte, if overflow happens
it needs to increment the high byte to avoid indexing 256 bytes too low into memory.

*/

void INS_LDA_IM(CPU c)
{
    byte load_value = CPUFetchByte(c);
    CPUSetA(c, load_value);
    SET_PS_ACCUMULATOR(c);
}

void INS_LDA_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_LDA(c, address);
}

void INS_LDA_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_LDA(c, address);
}

void INS_LDA_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_LDA(c, address);
}

void INS_LDA_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_LDA(c, address);
}

void INS_LDA_ABY(CPU c)
{
    word address = ADDR_ABY(c);
    OPER_LDA(c, address);
}

void INS_LDA_INX(CPU c)
{
    word address = ADDR_INX(c);
    OPER_LDA(c, address);
}

void INS_LDA_INY(CPU c)
{
    word address = ADDR_INY(c);
    OPER_LDA(c, address);
}

void INS_LDX_IM(CPU c)
{
    byte load_value = CPUFetchByte(c);
    CPUSetX(c, load_value);
    SET_PS_XREGISTER(c);
}

void INS_LDX_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_LDX(c, address);
}

void INS_LDX_ZPY(CPU c)
{
    byte address = ADDR_ZPY(c);
    OPER_LDX(c, address);
}

void INS_LDX_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_LDX(c, address);
}

void INS_LDX_ABY(CPU c)
{
    word address = ADDR_ABY(c);
    OPER_LDX(c, address);
}

void INS_LDY_IM(CPU c)
{
    byte load_value = CPUFetchByte(c);
    CPUSetY(c, load_value);
    SET_PS_YREGISTER(c);
}

void INS_LDY_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_LDY(c, address);
}

void INS_LDY_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_LDY(c, address);
}

void INS_LDY_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_LDY(c, address);
}

void INS_LDY_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_LDY(c, address);
}

void INS_STA_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_STA(c, address);
}

void INS_STA_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_STA(c, address);
}

void INS_STA_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_STA(c, address);
}

void INS_STA_ABX(CPU c)
{
    word address = ADDR_ABX(c);

    CPUClockTick(c); // See Note 1

    OPER_STA(c, address);
}

void INS_STA_ABY(CPU c)
{
    word address = ADDR_ABY(c);

    CPUClockTick(c); // See Note 1

    OPER_STA(c, address);
}

void INS_STA_INX(CPU c)
{
    word address = ADDR_INX(c);
    OPER_STA(c, address);
}

void INS_STA_INY(CPU c)
{
    word address = ADDR_INY(c);

    CPUClockTick(c); // See Note 1

    OPER_STA(c, address);
}

void INS_STX_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_STX(c, address);
}

void INS_STX_ZPY(CPU c)
{
    byte address = ADDR_ZPY(c);
    OPER_STX(c, address);
}

void INS_STX_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_STX(c, address);
}

void INS_STY_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_STY(c, address);
}

void INS_STY_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_STY(c, address);
}

void INS_STY_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_STY(c, address);
}

void INS_TAX_IMP(CPU c)
{
    byte a_value = CPUGetA(c);
    CPUSetX(c, a_value);
    SET_PS_XREGISTER(c);

    CPUClockTick(c);
}

void INS_TAY_IMP(CPU c)
{
    byte a_value = CPUGetA(c);
    CPUSetY(c, a_value);
    SET_PS_YREGISTER(c);

    CPUClockTick(c);
}

void INS_TXA_IMP(CPU c)
{
    byte x_value = CPUGetX(c);
    CPUSetA(c, x_value);
    SET_PS_ACCUMULATOR(c);

    CPUClockTick(c);
}

void INS_TYA_IMP(CPU c)
{
    byte y_value = CPUGetY(c);
    CPUSetA(c, y_value);
    SET_PS_ACCUMULATOR(c);

    CPUClockTick(c);
}

void INS_TSX_IMP(CPU c)
{
    byte stack_ptr = CPUGetSP(c);
    CPUSetX(c, stack_ptr);
    SET_PS_XREGISTER(c);

    CPUClockTick(c);
}

void INS_TXS_IMP(CPU c)
{
    byte x_value = CPUGetX(c);
    CPUSetSP(c, x_value);

    CPUClockTick(c);
}

void INS_PHA_IMP(CPU c)
{
    byte a_value = CPUGetA(c);
    CPUPushByteToStack(c, a_value);
}

void INS_PHP_IMP(CPU c)
{
    byte status_register = CPUGetStatusRegister(c);
    CPUPushByteToStack(c, status_register);
}

void INS_PLA_IMP(CPU c)
{
    byte value = CPUPopByteFromStack(c);

    CPUClockTick(c); // Why?
    CPUSetA(c, value);
    SET_PS_ACCUMULATOR(c);
}

void INS_PLP_IMP(CPU c)
{
    byte value = CPUPopByteFromStack(c);

    CPUClockTick(c); // Why?
    CPUSetStatusRegister(c, value);
}

void INS_AND_IM(CPU c)
{
    byte mem_value = CPUFetchByte(c);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value & a_value);
    SET_PS_ACCUMULATOR(c);
}

void INS_AND_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_AND(c, address);
}

void INS_AND_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_AND(c, address);
}

void INS_AND_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_AND(c, address);
}

void INS_AND_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_AND(c, address);
}

void INS_AND_ABY(CPU c)
{
    word address = ADDR_ABY(c);
    OPER_AND(c, address);
}

void INS_AND_INX(CPU c)
{
    word address = ADDR_INX(c);
    OPER_AND(c, address);
}

void INS_AND_INY(CPU c)
{
    word address = ADDR_INY(c);
    OPER_AND(c, address);
}

void INS_EOR_IM(CPU c)
{
    byte mem_value = CPUFetchByte(c);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value ^ a_value);
    SET_PS_ACCUMULATOR(c);
}

void INS_EOR_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_EOR(c, address);
}

void INS_EOR_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_EOR(c, address);
}

void INS_EOR_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_EOR(c, address);
}

void INS_EOR_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_EOR(c, address);
}

void INS_EOR_ABY(CPU c)
{
    word address = ADDR_ABY(c);
    OPER_EOR(c, address);
}

void INS_EOR_INX(CPU c)
{
    word address = ADDR_INX(c);
    OPER_EOR(c, address);
}

void INS_EOR_INY(CPU c)
{
    word address = ADDR_INY(c);
    OPER_EOR(c, address);
}

void INS_ORA_IM(CPU c)
{
    byte mem_value = CPUFetchByte(c);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value | a_value);
    SET_PS_ACCUMULATOR(c);
}

void INS_ORA_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_ORA(c, address);
}

void INS_ORA_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_ORA(c, address);
}

void INS_ORA_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_ORA(c, address);
}

void INS_ORA_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_ORA(c, address);
}

void INS_ORA_ABY(CPU c)
{
    word address = ADDR_ABY(c);
    OPER_ORA(c, address);
}

void INS_ORA_INX(CPU c)
{
    word address = ADDR_INX(c);
    OPER_ORA(c, address);
}

void INS_ORA_INY(CPU c)
{
    word address = ADDR_INY(c);
    OPER_ORA(c, address);
}

void INS_BIT_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_BIT(c, address);
}

void INS_BIT_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_BIT(c, address);
}

void INS_ADC_IM(CPU c)
{
    word address = CPUGetPC(c);
    CPUSetPC(c, address + 1);

    OPER_ADC(c, address);
}

void INS_ADC_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_ADC(c, address);
}

void INS_ADC_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_ADC(c, address);
}

void INS_ADC_AB(CPU c)
{
    byte address = ADDR_AB(c);
    OPER_ADC(c, address);
}

void INS_ADC_ABX(CPU c)
{
    byte address = ADDR_ABX(c);
    OPER_ADC(c, address);
}

void INS_ADC_ABY(CPU c)
{
    byte address = ADDR_ABY(c);
    OPER_ADC(c, address);
}

void INS_ADC_INX(CPU c)
{
    byte address = ADDR_INX(c);
    OPER_ADC(c, address);
}

void INS_ADC_INY(CPU c)
{
    byte address = ADDR_INY(c);
    OPER_ADC(c, address);
}

void INS_SBC_IM(CPU c)
{
    word address = CPUGetPC(c);
    CPUIncrementPC(c, 1);
    CPUClockTick(c);

    OPER_SBC(c, address);
}

void INS_SBC_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_SBC(c, address);
}

void INS_SBC_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_SBC(c, address);
}

void INS_SBC_AB(CPU c)
{
    byte address = ADDR_AB(c);
    OPER_SBC(c, address);
}

void INS_SBC_ABX(CPU c)
{
    byte address = ADDR_ABX(c);
    OPER_SBC(c, address);
}

void INS_SBC_ABY(CPU c)
{
    byte address = ADDR_ABY(c);
    OPER_SBC(c, address);
}

void INS_SBC_INX(CPU c)
{
    byte address = ADDR_INX(c);
    OPER_SBC(c, address);
}

void INS_SBC_INY(CPU c)
{
    byte address = ADDR_INY(c);
    OPER_SBC(c, address);
}

void INS_CMP_IM(CPU c)
{
    word address = CPUGetPC(c);
    CPUSetPC(c, address + 1);

    OPER_CMP(c, address);
}

void INS_CMP_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_CMP(c, address);
}

void INS_CMP_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_CMP(c, address);
}

void INS_CMP_AB(CPU c)
{
    byte address = ADDR_AB(c);
    OPER_CMP(c, address);
}

void INS_CMP_ABX(CPU c)
{
    byte address = ADDR_ABX(c);
    OPER_CMP(c, address);
}

void INS_CMP_ABY(CPU c)
{
    byte address = ADDR_ABY(c);
    OPER_CMP(c, address);
}

void INS_CMP_INX(CPU c)
{
    byte address = ADDR_INX(c);
    OPER_CMP(c, address);
}

void INS_CMP_INY(CPU c)
{
    byte address = ADDR_INY(c);
    OPER_CMP(c, address);
}

void INS_CPX_IM(CPU c)
{
    word address = CPUGetPC(c);
    CPUSetPC(c, address + 1);

    OPER_CPX(c, address);
}

void INS_CPX_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_CPX(c, address);
}

void INS_CPX_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_CPX(c, address);
}

void INS_CPY_IM(CPU c)
{
    word address = CPUGetPC(c);
    CPUSetPC(c, address + 1);

    OPER_CPY(c, address);
}

void INS_CPY_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_CPY(c, address);
}

void INS_CPY_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_CPY(c, address);
}

void INS_INC_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_INC(c, address);
}

void INS_INC_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_INC(c, address);
}

void INS_INC_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_INC(c, address);
}

void INS_INC_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_INC(c, address);
}

void INS_DEC_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_DEC(c, address);
}

void INS_DEC_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_DEC(c, address);
}

void INS_DEC_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_DEC(c, address);
}

void INS_DEC_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_DEC(c, address);
}

void INS_INX_IMP(CPU c)
{
    CPUSetX(c, CPUGetX(c) + 1);
    CPUClockTick(c);
    SET_PS_XREGISTER(c);
}

void INS_INY_IMP(CPU c)
{
    CPUSetY(c, CPUGetY(c) + 1);
    CPUClockTick(c);
    SET_PS_YREGISTER(c);
}

void INS_DEX_IMP(CPU c)
{
    CPUSetX(c, CPUGetX(c) - 1);
    CPUClockTick(c);
    SET_PS_XREGISTER(c);
}

void INS_DEY_IMP(CPU c)
{
    CPUSetY(c, CPUGetY(c) - 1);
    CPUClockTick(c);
    SET_PS_YREGISTER(c);
}

void INS_ASL_ACC(CPU c)
{
    byte a_value = CPUGetA(c);

    a_value = a_value << 1;

    CPUSetStatusFlag(c, PS_C, (a_value & 0xFF00) > 0);
    CPUSetStatusFlag(c, PS_N, (a_value & 0x0080));
    CPUSetStatusFlag(c, PS_Z, (a_value == 0));

    CPUSetA(c, a_value);
    CPUClockTick(c);
}

void INS_ASL_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_ASL(c, address);
}

void INS_ASL_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_ASL(c, address);
}

void INS_ASL_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_ASL(c, address);
}

void INS_ASL_ABX(CPU c)
{
    word address = ADDR_AB(c);
    OPER_ASL(c, address);
}

// --- LSR ---

void INS_LSR_ACC(CPU c)
{
    byte a_value = CPUGetA(c);

    CPUSetStatusFlag(c, PS_C, (a_value & 0x0001));

    a_value = a_value >> 1;

    CPUSetStatusFlag(c, PS_N, a_value & 0x0080);
    CPUSetStatusFlag(c, PS_Z, (a_value == 0));

    CPUSetA(c, a_value);
    CPUClockTick(c);
}

void INS_LSR_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_LSR(c, address);
}

void INS_LSR_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_LSR(c, address);
}

void INS_LSR_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_LSR(c, address);
}

void INS_LSR_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_LSR(c, address);
}

// --- ROL ---

void INS_ROL_ACC(CPU c)
{
    word a_value = CPUGetA(c);

    a_value = (a_value << 1) | CPUGetStatusFlag(c, PS_C);

    CPUSetStatusFlag(c, PS_C, (a_value & 0xFF00));
    CPUSetStatusFlag(c, PS_Z, (a_value & 0x00FF == 0x0000));
    CPUSetStatusFlag(c, PS_N, (a_value & 0x0080));

    CPUSetA(c, a_value);
    CPUClockTick(c);
}

void INS_ROL_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_ROL(c, address);
}

void INS_ROL_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_ROL(c, address);
}

void INS_ROL_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_ROL(c, address);
}

void INS_ROL_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_ROL(c, address);
}

// --- ROR ---

void INS_ROR_ACC(CPU c)
{
    word a_value = CPUGetA(c);

    a_value = (a_value >> 1) | (CPUGetStatusFlag(c, PS_C) << 7);

    CPUSetStatusFlag(c, PS_C, (a_value & 0x0001));
    CPUSetStatusFlag(c, PS_Z, (a_value & 0x00FF == 0x0000));
    CPUSetStatusFlag(c, PS_N, (a_value & 0x0080));

    CPUSetA(c, a_value);
    CPUClockTick(c);
}

void INS_ROR_ZP(CPU c)
{
    byte address = ADDR_ZP(c);
    OPER_ROR(c, address);
}

void INS_ROR_ZPX(CPU c)
{
    byte address = ADDR_ZPX(c);
    OPER_ROR(c, address);
}

void INS_ROR_AB(CPU c)
{
    word address = ADDR_AB(c);
    OPER_ROR(c, address);
}

void INS_ROR_ABX(CPU c)
{
    word address = ADDR_ABX(c);
    OPER_ROR(c, address);
}

void INS_JMP_AB(CPU c)
{
    word address = ADDR_AB(c);
    CPUSetPC(c, address);
}

void INS_JMP_IND(CPU c)
{
    word abs_address = ADDR_AB(c);
    word address = CPUReadWord(c, abs_address);
    CPUSetPC(c, address);
}

void INS_JSR_AB(CPU c)
{
    word sr_address = ADDR_AB(c);

    CPUIncrementPC(c, -1);
    word pc_value = CPUGetPC(c);

    CPUPushByteToStack(c, (pc_value >> 8) & 0x00FF);
    CPUPushByteToStack(c, pc_value & 0x00FF);

    CPUSetPC(c, sr_address);
}

void INS_RTS_IMP(CPU c)
{
    word old_pc = CPUPopByteFromStack(c);
    old_pc |= CPUPopByteFromStack(c) << 8;

    CPUSetPC(c, old_pc + 1);
    CPUClockTick(c);
}

void INS_BCC_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (!CPUGetStatusFlag(c, PS_C))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BCS_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (CPUGetStatusFlag(c, PS_C))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BEQ_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (CPUGetStatusFlag(c, PS_Z))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BMI_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (CPUGetStatusFlag(c, PS_N))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BNE_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (!CPUGetStatusFlag(c, PS_Z))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BPL_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (!CPUGetStatusFlag(c, PS_N))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BVC_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (!CPUGetStatusFlag(c, PS_V))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_BVS_REL(CPU c)
{
    word offset = CPUFetchByte(c);

    if (CPUGetStatusFlag(c, PS_V))
    {
        OPER_BRANCH(c, offset);
    }
}

void INS_CLC_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_C, 0);
    CPUClockTick(c);
}

void INS_CLD_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_D, 0);
    CPUClockTick(c);
}

void INS_CLI_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_I, 0);
    CPUClockTick(c);
}

void INS_CLV_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_V, 0);
    CPUClockTick(c);
}

void INS_SEC_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_C, 1);
    CPUClockTick(c);
}

void INS_SED_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_D, 1);
    CPUClockTick(c);
}

void INS_SEI_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_I, 1);
    CPUClockTick(c);
}

void INS_BRK_IMP(CPU c)
{
    CPUSetStatusFlag(c, PS_I, 1);
    word pc_value = CPUGetPC(c);

    CPUPushByteToStack(c, (pc_value >> 8) & 0x00FF);
    CPUPushByteToStack(c, (pc_value & 0x00FF));

    CPUSetStatusFlag(c, PS_B, 1);
    CPUPushByteToStack(c, CPUGetStatusRegister(c));

    pc_value = MemoryReadByte(CPUGetMemory(c), IRQ_VECTOR_START);
    pc_value |= MemoryReadByte(CPUGetMemory(c), IRQ_VECTOR_START + 1) << 8;
}

void INS_RTI_IMP(CPU c)
{
    byte status_flags = CPUPopByteFromStack(c);
    CPUSetStatusRegister(c, status_flags);

    byte prog_counter = CPUPopByteFromStack(c);
    prog_counter |= CPUPopByteFromStack(c) << 8;
    CPUSetPC(c, prog_counter);
}

void INS_NOP_IM(CPU c)
{
    CPUClockTick(c);
}
