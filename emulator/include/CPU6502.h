#ifndef CPU6502_H
#define CPU6502_H

#include "Memory.h"
#include "Clock.h"
#include "EmulatorTypes.h"
#include "EmulatorConfig.h"

typedef struct cpu6502 *CPU;

// === Default Values ===

#define DEFAULT_PROGRAM_COUNTER 0xFFFC
#define DEFAULT_PROCESSOR_STATUS_FLAGS 0x00
#define DEFAULT_STACK_BEGIN 0x0100
#define DEFAULT_STACK_END 0x0100

// === Enumerations ===

// PS_FLAGS : Processor Status Flags
enum PS_FLAGS
{
    PS_C, // Carry
    PS_Z, // Zero
    PS_I, // Interrupt Disable
    PS_D, // Decimal Mode
    PS_B, // Break Command
    PS_V, // Overflow
    PS_N  // Negative
};

// === Object Lifetime ===

// CPUNew : Creates a new CPU Object
CPU CPUNew();

// CPUFree : Frees a CPU Object (Frees connected clock and memory if free_connections == 1)
int CPUFree(CPU c, int free_connections);

// === Memory Operations ===

// CPUConnectMemory : Connects CPU to virtual memory
int CPUConnectMemory(CPU c, Memory m);

// CPUFetchByte : Fetches a byte from memory at PC (1 Cycle), Inc PC)
byte CPUFetchByte(CPU c);

// CPUFetchWord : Fetches a word from memory at PC (2 Cycles, Inc PC)
word CPUFetchWord(CPU c);

// CPUReadByte : Reads a byte from memory at a given address(1 Cycle)
byte CPUReadByte(CPU c, word address);

// CPUWriteByte : Writes a byte to memory at a given address (1 Cycle)
int CPUWriteByte(CPU c, word address, byte data);

// === Clock Operations ===

// CPUConnectClock : Connects CPU to clock
int CPUConnectClock(CPU c, Clock clk);

// === CPU Operations ===

// === Getters and Setters ===

// CPUSetStatusFlag : Sets a CPU Status Flag (Returns 0 on fail)
int CPUSetStatusFlag(CPU C, int flagId, int flagValue);

// CPUGetStatusRegister : Returns the entire status register
byte CPUGetStatusRegister(CPU C);

// CPUSetStatusRegister : Sets the entire status register
int CPUSetStatusRegister(CPU C, byte val);

// CPUGetStatusFlag : Gets a CPU Status Flag (Returns -1 if not valid)
int CPUGetStatusFlag(CPU C, int flagId);

// CPUGetClock : Returns a pointer to the clock
Clock CPUGetClock(CPU C);

// CPUIncrementPC : Increments the program counter by a given value (Can be negative)
void CPUIncrementPC(CPU C, byte val);

// CPUIncrementSP : Increments the stack pointer by a given value (Can be negative)
void CPUIncrementSP(CPU C, byte val);

// CPUSetPC : Sets a value for the program counter
void CPUSetPC(CPU C, word val);

// CPUSetSP : Sets a value for the stack pointer
void CPUSetSP(CPU C, byte val);

// CPSettA : Sets a value for the accumulator
void CPUSetA(CPU C, byte val);

// CPUSetX : Sets a value in the X Register
void CPUSetX(CPU C, byte val);

// CPUSetY : Sets a value in the Y Register
void CPUSetY(CPU C, byte val);

// CPUGetPC : Returns the value of the program counter
word CPUGetPC(CPU C);

// CPUGetSP : Returns the value of the stack pointer
byte CPUGetSP(CPU C);

// CPUGetA : Returns the value of the accumulator
byte CPUGetA(CPU C);

// CPUGetX : Returns the value in the X Register
byte CPUGetX(CPU C);

// CPUGetY : Returns the value in the Y Register
byte CPUGetY(CPU C);

#endif