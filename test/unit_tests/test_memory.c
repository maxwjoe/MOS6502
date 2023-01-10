#include "Memory.h"
#include "Eagle.h"

TEST(T_MEMORY_CREATE)
{
    Memory m = MemoryNew(0xFFFF);

    CHECK_TRUE(m != NULL);

    MemoryFree(m);
}

TEST(T_MEMORY_FREE)
{
    Memory m = MemoryNew(0xFFFF);

    int status_code = MemoryFree(m);

    CHECK_EQ(status_code, ok);
}

TEST(T_MEMORY_READ_WRITE)
{
    Memory m = MemoryNew(0xFFFF);

    int status_code = MemoryWriteByte(m, 0xAAAA, 0x55);
    byte data_written = MemoryReadByte(m, 0xAAAA);

    CHECK_EQ(data_written, 0x55);
    CHECK_EQ(status_code, ok);

    MemoryFree(m);
}

TEST(T_MEMORY_BOUNDS_UPPER)
{
    Memory m = MemoryNew(0xFFFF);

    int status_code = MemoryWriteByte(m, 0xFFFF, 0x13);
    byte data_written = MemoryReadByte(m, 0xFFFF);

    CHECK_EQ(data_written, 0x13);
    CHECK_EQ(status_code, ok);

    MemoryFree(m);
}

TEST(T_MEMORY_BOUNDS_LOWER)
{
    Memory m = MemoryNew(0xFFFF);

    int status_code = MemoryWriteByte(m, 0x0000, 0x15);
    byte data_written = MemoryReadByte(m, 0x0000);

    CHECK_EQ(data_written, 0x15);
    CHECK_EQ(status_code, ok);

    MemoryFree(m);
}
