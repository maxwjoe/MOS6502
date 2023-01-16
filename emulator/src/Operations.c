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

void OPER_EOR(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte mem_value = CPUReadByte(c, address);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value ^ a_value);
    SET_PS_ACCUMULATOR(c);
}

void OPER_ORA(CPU c, word address)
{
    CYCLE_PENALTY(c);

    byte mem_value = CPUReadByte(c, address);
    byte a_value = CPUGetA(c);

    CPUSetA(c, mem_value | a_value);
    SET_PS_ACCUMULATOR(c);
}

void OPER_BIT(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);
    byte a_value = CPUGetA(c);
    word and_value = mem_value & a_value;

    CPUSetStatusFlag(c, PS_Z, (and_value & 0x00FF) == 0x00);
    CPUSetStatusFlag(c, PS_N, mem_value & (1 << 7));
    CPUSetStatusFlag(c, PS_V, mem_value & (1 << 6));
}

void OPER_ADC(CPU c, word address)
{
    word mem_value = CPUReadByte(c, address);

    // Will perform 16 bit addition (unlike hardware) to simplify logic
    word a_value = (word)CPUGetA(c);
    word sum = a_value + mem_value + CPUGetStatusFlag(c, PS_C);

    // Load first 8 bits of the sum into the accumulator
    CPUSetA(c, (byte)(sum & 0x00FF));

    // Set Flags (Using previous value of accumulator)
    SET_PS_ADC(c, a_value, mem_value, sum);
}

void OPER_SBC(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);

    // Like ADC : Perform 16 bit operation to simplify logic

    // Take 2's Complement of value from memory to invert
    mem_value ^= 0x00FF;

    // Addition
    word a_value = (word)CPUGetA(c);
    word sum = a_value + mem_value + CPUGetStatusFlag(c, PS_C);

    // Load first 8 bits of sum into accumulator
    CPUSetA(c, (sum & 0x00FF));

    // Set Flags (Using previous value of accumulator)
    SET_PS_SBC(c, a_value, mem_value, sum);
}

void OPER_CMP(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);
    byte a_value = CPUGetA(c);

    byte cmp_res = a_value - mem_value;

    CPUSetStatusFlag(c, PS_C, (a_value >= mem_value));
    CPUSetStatusFlag(c, PS_Z, a_value == mem_value);
    CPUSetStatusFlag(c, PS_N, (cmp_res & 0x0080));
}

void OPER_CPX(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);
    byte x_value = CPUGetX(c);

    byte cmp_res = x_value - mem_value;

    CPUSetStatusFlag(c, PS_C, (x_value >= mem_value));
    CPUSetStatusFlag(c, PS_Z, x_value == mem_value);
    CPUSetStatusFlag(c, PS_N, (cmp_res & 0x0080));
}

void OPER_CPY(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);
    byte y_value = CPUGetY(c);

    byte cmp_res = y_value - mem_value;

    CPUSetStatusFlag(c, PS_C, (y_value >= mem_value));
    CPUSetStatusFlag(c, PS_Z, y_value == mem_value);
    CPUSetStatusFlag(c, PS_N, (cmp_res & 0x0080));
}

void OPER_INC(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);

    mem_value++;
    CPUClockTick(c);

    CPUWriteByte(c, address, mem_value);

    SET_PS_MEM_OP(c, mem_value);
}

void OPER_DEC(CPU c, word address)
{
    byte mem_value = CPUReadByte(c, address);

    mem_value--;
    CPUClockTick(c);

    CPUWriteByte(c, address, mem_value);

    SET_PS_MEM_OP(c, mem_value);
}

void SET_PS_ADC(CPU c, word a_value, word value_to_add, word sum)
{
    // Assumption : This function is called using the accumulator value
    // from before the operation has occurred

    // Set carry flag if sum outside of 8-bit range
    CPUSetStatusFlag(c, PS_C, (sum > 0x00FF));

    // Set zero flag based on lowest 8-bits of 16-bit sum
    CPUSetStatusFlag(c, PS_Z, !(sum & 0x00FF));

    // Set signed overflow flag
    // 0x0080 : Mask for the most significant bit (8 bits)
    // Let A be MSB a_value, M be MSB value_to_add and R be the MSB result
    // Constructing a truth table and reducing to a boolean expression
    // | A | M | R | Output = V |
    // Output Rule : ~(A^M) & (A^R)

    int has_overflow = (~(a_value ^ value_to_add) & (a_value ^ sum)) & 0x0080;
    CPUSetStatusFlag(c, PS_V, has_overflow);

    // Set negative flag (MSB of 8-bit sum)
    CPUSetStatusFlag(c, PS_N, (sum & 0x0080));
}

void SET_PS_SBC(CPU c, word a_value, word value_to_add, word sum)
{
    // Assumption : This function is called using the accumulator value
    // from before the operation has occurred

    CPUSetStatusFlag(c, PS_C, (sum & 0xFF00));
    CPUSetStatusFlag(c, PS_Z, !(sum & 0x00FF));

    int has_overflow = ((a_value ^ sum) & (a_value ^ value_to_add)) & 0x0080;

    CPUSetStatusFlag(c, PS_V, has_overflow);
    CPUSetStatusFlag(c, PS_N, (sum & 0x0080));
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

void SET_PS_MEM_OP(CPU c, byte value)
{
    CPUSetStatusFlag(c, PS_Z, (value == 0));
    CPUSetStatusFlag(c, PS_N, (value & 0x0080));
}
