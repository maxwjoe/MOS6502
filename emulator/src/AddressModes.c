#include "AddressModes.h"
#include "CPU6502.h"

// TODO: Ensure wrapping is correct for each address mode
// - Eg. Does ZPX for example need to return a word?

byte ADDR_ZP(CPU c)
{
    return CPUFetchByte(c);
}

byte ADDR_ZPX(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    // Note that zp_address stored as byte handles wrap around
    zp_address += CPUGetX(c);
    CPUClockTick(c);

    return zp_address;
}

byte ADDR_ZPY(CPU c)
{
    byte zp_address = CPUFetchByte(c);

    // Note that zp_address stored as byte handles wrap around
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
    word shifted_address = address + CPUGetX(c);

    // Check for and handle page cross after offsetting address
    if ((shifted_address & 0xFF00) != (address & 0xFF00))
    {
        CPUSetCyclePenalty(c, CPUGetCyclePenalty(c) + 1);
    }

    return shifted_address;
}

word ADDR_ABY(CPU c)
{
    word address = CPUFetchWord(c);
    word shifted_address = address + CPUGetY(c);

    // Check for and handle page cross after offsetting address
    if ((shifted_address & 0xFF00) != (address & 0xFF00))
    {
        CPUSetCyclePenalty(c, CPUGetCyclePenalty(c) + 1);
    }

    return shifted_address;
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
    word address = CPUReadWord(c, zp_address);

    word shifted_address = address + CPUGetY(c);

    // Check for and handle page cross after offsetting address
    if ((shifted_address & 0xFF00) != (address & 0xFF00))
    {
        CPUSetCyclePenalty(c, CPUGetCyclePenalty(c) + 1);
    }

    return shifted_address;
}
