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
    CPUFetchByte(c);

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
    CPUFetchByte(c);

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
