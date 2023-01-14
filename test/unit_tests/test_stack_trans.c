#include "Eagle.h"
#include "CPU6502.h"
#include "common_macros.h"

TEST(T_TAX_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x88);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TAX_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte x_val = CPUGetX(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(x_val, 0x88);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_TAY_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetA(c, 0x00);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TAY_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte y_val = CPUGetY(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(y_val, 0x00);
    CHECK_FALSE(F_N);
    CHECK_TRUE(F_Z);

    CPUFree(c, 1);
}

TEST(T_TXA_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetX(c, 0x01);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TXA_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_val = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(a_val, 0x01);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_TYA_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetY(c, 0xFF);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TYA_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte a_val = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(a_val, 0xFF);
    CHECK_TRUE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_TSX_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetSP(c, 0x44);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TSX_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte x_val = CPUGetX(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(x_val, 0x44);
    CHECK_FALSE(F_N);
    CHECK_FALSE(F_Z);

    CPUFree(c, 1);
}

TEST(T_TXS_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 2);

    CPUSetX(c, 0x65);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, TXS_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte stk_ptr = CPUGetSP(c);

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(stk_ptr, 0x65);

    CPUFree(c, 1);
}

TEST(T_PUSH_POP_STACK)
{
    SETUP_HW();

    CPUSetSP(c, 0x44);
    CPUPushByteToStack(c, 0x32);

    byte sp_dec = CPUGetSP(c);
    CHECK_EQ(sp_dec, 0x43);

    byte pulled_byte = CPUPopByteFromStack(c);
    CHECK_EQ(pulled_byte, 0x32);

    byte sp_inc = CPUGetSP(c);
    CHECK_EQ(sp_inc, 0x44);

    CPUFree(c, 1);
}

TEST(T_PHA_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetA(c, 0x87);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, PHA_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte data_written = CPUPopByteFromStack(c);

    CHECK_EQ(data_written, 0x87);

    CPUFree(c, 1);
}

TEST(T_PHP_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 3);

    CPUSetStatusRegister(c, 0x43);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, PHP_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte data_written = CPUPopByteFromStack(c);

    CHECK_EQ(data_written, 0x43);

    CPUFree(c, 1);
}

TEST(T_PLA_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetSP(c, 0x66);
    MemoryWriteByte(m, DEFAULT_STACK_BEGIN + 0x66 + 1, 0x89);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, PLA_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte data_pulled = CPUGetA(c);
    GET_ALL_FLAGS();

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(data_pulled, 0x89);
    CHECK_FALSE(F_Z);
    CHECK_TRUE(F_N);

    CPUFree(c, 1);
}

TEST(T_PLP_IMP)
{
    SETUP_HW();

    ClockSetTickLimit(clk, 4);

    CPUSetSP(c, 0xFF);

    // Checks that stack can wrap around
    MemoryWriteByte(m, DEFAULT_STACK_BEGIN + 0x00, 0x99);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, PLP_IMP);

    int execution_status = CPUExecute(c);
    int cycles_remaining = ClockGetTickLimit(clk);

    byte data_pulled = CPUGetStatusRegister(c);

    CHECK_EQ(execution_status, ok);
    CHECK_EQ(cycles_remaining, 0);
    CHECK_EQ(data_pulled, 0x99);

    CPUFree(c, 1);
}
