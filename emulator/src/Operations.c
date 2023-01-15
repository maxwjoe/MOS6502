#include "Operations.h"
#include "EmulatorHelper.h"
#include "CPU6502.h"
#include "stdio.h"

void OPER_LDA(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte load_value = CPUReadByte(c, address);
    CPUSetA(c, load_value);
    SET_PS_ACCUMULATOR(c);
}

void OPER_LDX(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte load_value = CPUReadByte(c, address);
    CPUSetX(c, load_value);
    SET_PS_XREGISTER(c);
}

void OPER_LDY(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte load_value = CPUReadByte(c, address);
    CPUSetY(c, load_value);
    SET_PS_YREGISTER(c);
}

void OPER_STA(CPU c, word address)
{
    byte a_register = CPUGetA(c);
    CPUWriteByte(c, address, a_register);
}

void OPER_STX(CPU c, word address)
{
    byte x_register = CPUGetX(c);
    CPUWriteByte(c, address, x_register);
}

void OPER_STY(CPU c, word address)
{
    byte y_register = CPUGetY(c);
    CPUWriteByte(c, address, y_register);
}

void OPER_AND(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte mem_value = CPUReadByte(c, address);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value & a_value);
    SET_PS_ACCUMULATOR(c);
}

void SET_PS_ACCUMULATOR(CPU c)
{
    byte a_val = CPUGetA(c);
    CPUSetStatusFlag(c, PS_Z, (a_val == 0));
    CPUSetStatusFlag(c, PS_N, (a_val & 0b10000000) > 0);
}

void SET_PS_XREGISTER(CPU c)
{
    byte x_val = CPUGetX(c);
    CPUSetStatusFlag(c, PS_Z, (x_val == 0));
    CPUSetStatusFlag(c, PS_N, (x_val & 0b10000000) > 0);
}

void SET_PS_YREGISTER(CPU c)
{
    byte y_val = CPUGetY(c);
    CPUSetStatusFlag(c, PS_Z, (y_val == 0));
    CPUSetStatusFlag(c, PS_N, (y_val & 0b10000000) > 0);
}
