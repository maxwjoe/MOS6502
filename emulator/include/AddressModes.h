#ifndef ADDRESS_MODES_H
#define ADDRESS_MODES_H

#include "EmulatorTypes.h"

// ADDR_XXX : Functions return address to operate on in memory

// --- XXX : Available addressing modes on 6502 ---

// IMP : Implied Mode (Register to Register operations, Not included here as it does not have address logic)
// IM : Immediate Mode (Uses value at program counter for operations, Not included here as it does have address logic)
// ZP : Zero Page Mode (Loads the byte at program counter [0xXX], 16-bit address 0x00XX on zero page)
// ZPX : Same as ZP Mode but offset by X Register value
// ZPY : Same as ZP Mode but offset by Y Register value
// AB : Absolute Mode (Loads a 16-bit word from program counter as memory address)
// ABX : Same as AB but offset by X Register value
// ABY : Same as AB but offset by Y Register value
// INX : Indirect X (Loads ZP Address, offsets by X register, reads at this address and uses data as operation address)
// INY : Indirect Y (Loads ZP Address, offsets by Y register, reads at this address and uses data as operation address)

// --- Addressing Mode Declarations ---

// ADDR_ZP : Zero Page Addressing Mode (1 CPU Cycle)
byte ADDR_ZP(CPU c);

// ADDR_ZPX : Zero Page X Addressing Mode (2 CPU Cycles)
byte ADDR_ZPX(CPU c);

// ADDR_ZPY : Zero Page Y Addressing Mode (2 CPU Cycles)
byte ADDR_ZPY(CPU c);

// ADDR_AB : Absolute Addressing Mode (2 CPU Cycles)
word ADDR_AB(CPU c);

// ADDR_ABX : Absolute X Addressing Mode (2 CPU Cycles)
word ADDR_ABX(CPU c);

// ADDR_ABY : Absolute Y Addressing Mode (2 CPU Cycles)
word ADDR_ABY(CPU c);

/*
Note on INX and INY modes :
INX -> Indexed Indirect , X Register
INY -> Indirect Indexed , Y Register
They are technically different methods, however since they are unique
to each register they use the same IN_ abbreviation
*/

// ADDR_INX : Indexed Indirect X Addressing Mode (4 CPU Cycles)
word ADDR_INX(CPU c);

// ADDR_INY : Indirect Indexed Y Addressing Mode (4 CPU Cycles)
word ADDR_INY(CPU c);

#endif