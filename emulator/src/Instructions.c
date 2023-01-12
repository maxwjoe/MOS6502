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
    OPER_STA(c, address);
}

void INS_STA_ABY(CPU c)
{
    word address = ADDR_ABY(c);
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
    OPER_STA(c, address);
}
