#include "AddressModes.h"
#include "CPU6502.h"

byte ADDR_ZP(CPU c)
{
    return CPUFetchByte(c);
}

byte ADDR_ZPX(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    zp_address += CPUGetX(c);
    CPUClockTick(c);

    return zp_address;
}

byte ADDR_ZPY(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    zp_address += CPUGetY(c);
    CPUClockTick(c);

    return zp_address;
}

word ADDR_AB(CPU c)
{
    return CPUFetchWord(c);
}

word ADDR_ABX(CPU c)
{
    word address = CPUFetchWord(c);
    address += CPUGetX(c);

    return address;
}

word ADDR_ABY(CPU c)
{
    word address = CPUFetchWord(c);
    address += CPUGetY(c);

    return address;
}

word ADDR_INX(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    zp_address += CPUGetX(c);
    CPUClockTick(c);

    word load_address = CPUReadWord(c, zp_address);

    return load_address;
}

word ADDR_INY(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    zp_address += CPUGetY(c);
    CPUClockTick(c);

    word load_address = CPUReadWord(c, zp_address);

    return load_address;
}
