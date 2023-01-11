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
    ok,
    error_generic,
    error_create,
    error_read,
    error_write,
    error_invalid_argument,
    error_null_deref,
    error_file_io,
    error_free,
    error_invalid_op_code,
};

#endif