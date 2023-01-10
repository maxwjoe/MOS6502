#ifndef MEMORY_H
#define MEMORY_H

// Memory : Represents virtual memory used by CPU

#include "EmulatorTypes.h"

typedef struct memory *Memory;

// MemoryNew : Creates a new memory object
Memory MemoryNew(int capacity_bytes);

// MemoryLoadBinary : Loads a binary from a file into memory
int MemoryLoadBinary(Memory m, char *file_path);

// MemoryHexDump : Dumps a range of data from memory to the console
int MemoryHexDump(Memory m, word lower_addr, word upper_addr);

// MemoryReadByte : Reads a byte of data from memory
byte MemoryReadByte(Memory m, word address);

// MemoryWriteByte : Writes a byte of data to memory
int MemoryWriteByte(Memory m, word address, byte data);

// MemoryWriteAll : Writes to entire address space
int MemoryWriteAll(Memory m, byte data);

// MemoryFree : Frees a memory object
int MemoryFree(Memory m);

#endif