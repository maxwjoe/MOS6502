# 6502 Emulator

![Screenshot_20230120_170544](https://user-images.githubusercontent.com/76637128/213815231-8b18b029-d371-46bd-b7f1-49b6f50b4942.png)

## About

The 6502 is an 8-bit microprocessor developed by MOS Technology in the 1970s. It appeared in many consumer electronics such as the Atari 2600, Commodore 64, Nintendo Entertainment System (NES) and the Apple II. The processor was designed to be a faster, cheaper and simpler version of the Motorolla 6800. The processor is simple by today's standards, making it a great target for emulation. The goal of this project was to gain an understanding of low level computing and an appreciation of the work that goes into emulating physical devices in software. 

## Basic Setup

Three components are required for the emulation to work. These are the CPU, memory and clock. These have been separated into separate components to better represent the real hardware and to improve the modularity of the codebase. This approach will allow further expansion of the emulatior to include other hardware components in the future. Setting up the emulator involves creating the components, setting the clock mode and connecting them to the CPU. 

```C
    // Create Hardware Objects
    CPU c = CPUNew();
    Memory m = MemoryNew(0xFFFF);
    Clock clk = ClockNew();
    ClockSetMode(clk, CM_STEP_NO_LIMIT);
    
    // Connect CPU to external hardware
    CPUConnectClock(c, clk);
    CPUConnectMemory(c, m);
```

Here the clock has been set to CM_STEP_NO_LIMIT, this means that the clock will wait for a keypress before advancing and that there is no cycle limit. Clock modes are described below. 

* CM_STEP_NO_LIMIT : Waits for keypress to step clock, no cycle limit
* CM_STEP_LIMIT : Waits for keypress to step clock, has cycle limit
* CM_FREQ_NO_LIMIT : Clock ticks at given frequency, no cycle limit
* CM_FREQ_LIMIT : Clock ticks at given frequency, has cycle limit

The cycle limit can be added to the clock through the Clock's API, details on this are in Clock.h in the emulator/include folder.

## Programming Memory

When creating a memory object, the entire addressable range is set to 0xEA which is the opcode for a no operation. By default, the CPU will just cycle and nothing meaningful will happen. To do something useful, the memory must be programmed. This can be done in two ways, by manually entering machine instructions in code, or by loading a 6502 binary from a file. This emulator provides a simple API for doing both.

### Manual Programming Example

Below is a simple example of how you would manually write a program into the memory. This method involves directly writing machine code.

```C
  // Load 0x05 into the A Register
  MemoryWriteByte(m, 0x4000, LDA_IM);
  MemoryWriteByte(m, 0x4001, 0x05);
  
  // Jump to address 0xBBAA in memory
  MemoryWriteByte(m, 0x4002, JMP_AB);
  MemoryWriteByte(m, 0x4003, 0xAA);
  MemoryWriteByte(m, 0x4004, 0xBB);
  
  // Load 0xC4 into the X Register
  MemoryWriteByte(m, 0xBBAA, LDX_IM);
  MemoryWriteByte(m, 0xBBAB, 0xC4);

```

### Program from Compiled Binary Example

A much more efficient programming method is to use a compiled 6502 binary. This enables you to write your program in assembly (or a higher level language if you wish). As long as it can be compiled to a 6502 readable binary. The Memory ADT provides a function that will open the binary and load it into the CPU's memory. 

```C

  MemoryLoadBinary(m, PATH_TO_FILE);

```

### CPU Read/Write/Fetch vs Memory Read/Write

When programming the memory, be sure to only use the Memory ADT functions. The CPU functions such as CPUReadByte(), CPUFetchByte(), CPUWriteByte(), CPUPushToStack(), CPUPopFromStack(), etc... will modify the CPU's internal state as they are designed to be called whilst the CPU is running. More specifically, something like CPUPushToStack() will modify the stack pointer, program counter and cost CPU cycles. So be sure to use the Memory functions as they only write to memory and cost nothing. Using CPU functions here will cause unexpected behaviour. 


## Executing a Program

After programming is complete, simply call CPUExecute(c) to run the CPU on the connected memory. If you are using a clock mode with a cycle limit, be sure to set the tick_limit variable with the Clock's API first otherwise it will exit straight away. 

```C

    ClockSetTickLimit(clk, 5);

    byte x_reg = 0x22;
    CPUSetX(c, x_reg);

    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER, LDA_ABX);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 1, 0xFF);
    MemoryWriteByte(m, DEFAULT_PROGRAM_COUNTER + 2, 0x22);
    MemoryWriteByte(m, 0x22FF + x_reg, 0x89);
    
    CPUExecute(c);

```

## Interrupts and Resets

The CPU API includes functions that allow you to make an interrupt request, non-maskable interrupt and reset the CPU. These functions are not callable during execution at the moment as there is no need for them given that the CPU has no asynchronous hardware connected. However, in future there could be, so they have been included. 

## Supported Opcodes

This emulator supports all official 6502 CPU Operations in all addressing modes. A complete list of supported operations can be found in emulator/include/Opcodes.h. Unofficial instructions are not yet supported, if the CPU encounters an unknown instruction it will exit the emulation. This may be updated in the future. 

## Unit Tests and Issues

The tests folder includes all unit tests used for this emulator. There are some known bugs which are being worked on, these are in the issues section of this repo. The testing was conducted using Eagle, which was written specifically to test this project. Eagle's repository can be found here https://github.com/maxwjoe/Eagle 

## Compatibility 

The emulator itself has no external dependencies outside of the C standard library. However, the unit tests require the Eagle testing framework to be installed and the frontend GUI uses ncurses, which is included in most linux distributions. This emulator was developed in a linux environment and has not been tested for MacOS or Windows. The core emulator itself should be good to go on most operating systems, although the makefile may need modification as it currently builds to a static libraray (.a file), this file extension is different for MacOS and Windows. 








