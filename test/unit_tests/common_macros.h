#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

// SETUP_HW : Sets up CPU, Clock and Memory
#define SETUP_HW()                \
    CPU c = CPUNew();             \
    Memory m = MemoryNew(0xFFFF); \
    Clock clk = ClockNew();       \
    CPUConnectMemory(c, m);       \
    CPUConnectClock(c, clk)

// GET_ALL_FLAGS : Gets all CPU Flags
#define GET_ALL_FLAGS()                  \
    int F_N = CPUGetStatusFlag(c, PS_N); \
    int F_V = CPUGetStatusFlag(c, PS_V); \
    int F_Z = CPUGetStatusFlag(c, PS_Z); \
    int F_B = CPUGetStatusFlag(c, PS_B); \
    int F_C = CPUGetStatusFlag(c, PS_C); \
    int F_I = CPUGetStatusFlag(c, PS_I); \
    int F_D = CPUGetStatusFlag(c, PS_D)

#endif