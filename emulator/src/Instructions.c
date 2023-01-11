#include "Instructions.h"
#include "AddressModes.h"
#include "Operations.h"
#include "CPU6502.h"

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

void INS_LDA_ZPY(CPU c)
{
    byte address = ADDR_ZPY(c);
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
    word address = ADDR_INX(c);
    OPER_LDA(c, address);
}
