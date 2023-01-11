#ifndef EMULATOR_TYPES_H
#define EMULATOR_TYPES_H

#include "stdint.h"

typedef struct cpu6502 *CPU;

// byte : 8 bits of data
typedef uint8_t byte;

// word : 16 bits of data
typedef uint16_t word;

// cpu_operation : Function pointer to a CPU Operation
typedef void (*cpu_operation)(CPU);

// enum_status : Status definitions for Emulator
enum enum_status
{
    ok,                     // Successful Completion
    error_generic,          // Generic (Catch all) Error
    error_create,           // Failed to create
    error_read,             // Failed to read memory
    error_write,            // Failed to write to memory
    error_invalid_argument, // Invalid parameter passed
    error_null_deref,       // Attempted to dereference a null pointer
    error_file_io,          // Error reading to or writing from a file
    error_free,             // Error attempting to free memory
    error_invalid_op_code,  // Error attempting to execute an unknown CPU Instruction
};

#endif