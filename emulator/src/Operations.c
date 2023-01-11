#include "Operations.h"
#include "CPU6502.h"

void OPER_LDA(CPU c, word address)
{
    byte load_value = CPUReadByte(c, address);
    CPUSetA(c, load_value);
    SET_PS_ACCUMULATOR(c);
}

void SET_PS_ACCUMULATOR(CPU c)
{
    byte a_val = CPUGetA(c);
    CPUSetStatusFlag(c, PS_Z, (a_val == 0));
    CPUSetStatusFlag(c, PS_N, (a_val & 0b10000000) > 0);
}
