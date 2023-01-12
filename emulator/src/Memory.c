#include "Memory.h"

#include "stdlib.h"
#include "stdio.h"
#include "EmulatorHelper.h"

// s_check_bounds : Checks that given address is within memory bounds
static int s_check_bounds(Memory m, word address);

typedef struct memory
{
    int capacity;
    byte *data;
} *Memory;

Memory MemoryNew(int capacity_bytes)
{
    if (capacity_bytes <= 0)
    {
        LOG_STATUS(error_invalid_argument);
        return NULL;
    }

    Memory m = (Memory)malloc(sizeof(struct memory));

    if (m == NULL)
    {
        LOG_STATUS(error_create);
        return NULL;
    }

    m->capacity = capacity_bytes;
    m->data = (byte *)calloc(m->capacity, sizeof(byte));

    if (m->data == NULL)
    {
        free(m);
        LOG_STATUS(error_create);
        return NULL;
    }

    return m;
}

int MemoryWriteByte(Memory m, word address, byte data)
{
    if (m == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    if (!s_check_bounds(m, address))
    {
        LOG_STATUS(error_write);
        return error_write;
    }

    m->data[address] = data;
    return ok;
}

int MemoryWriteAll(Memory m, byte data)
{
    if (m == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    for (byte i = 0; i < m->capacity; i++)
    {
        m->data[i] = data;
    }

    return ok;
}

int MemoryHexDump(Memory m, word lower_addr, word upper_addr)
{
    if (m == NULL || !s_check_bounds(m, lower_addr) || !s_check_bounds(m, upper_addr) || lower_addr >= upper_addr)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    for (word i = lower_addr; i < upper_addr; i++)
    {
        printf("Addr : 0x%04X\tData : 0x%02X\n", i, m->data[i]);
    }

    return ok;
}

int MemoryLoadBinary(Memory m, char *file_path)
{
    if (m == NULL || file_path == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    FILE *binary_file = fopen(file_path, "rb");

    if (binary_file == NULL)
    {
        LOG_STATUS(error_file_io);
        return error_file_io;
    }

    fread(m->data, m->capacity, 1, binary_file);
    fclose(binary_file);

    return ok;
}

byte MemoryReadByte(Memory m, word address)
{
    if (m == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    if (!s_check_bounds(m, address))
    {
        LOG_STATUS(error_read);
        return error_read;
    }

    return m->data[address];
}

int MemoryFree(Memory m)
{
    if (m == NULL)
    {
        LOG_STATUS(error_invalid_argument);
        return error_invalid_argument;
    }

    if (m->data != NULL)
    {
        free(m->data);
    }
    else
    {
        LOG_STATUS(error_null_deref);
        return error_null_deref;
    }

    free(m);
    return ok;
}

static int s_check_bounds(Memory m, word address)
{
    if (m == NULL)
    {
        return 0;
    }

    return (address >= 0 && address <= m->capacity);
}
