#ifndef OPCODES_H
#define OPCODES_H

// --- File Format ---

// #define [OP_NAME] 0x[CODE] // Description (Addressing Mode, CPU Cycles) : FLAGS
// FLAGS : C = Complete, T = Tested , FLAG + * = Has Active TODO Item

// --- Opcode Definitions ---

// NOP : No Operation

#define NOP_IM 0xEA // No Operation (Immediate Mode, 2) :

// LDA : Load Accumulator

#define LDA_IM 0xA9  // Load Accumulator (Immediate Mode, 2) : C, T
#define LDA_ZP 0xA5  // Load Accumulator (Zero Page Mode, 3) : C, T
#define LDA_ZPX 0xB5 // Load Accumulator (Zero Page X Mode, 4) : C, T
#define LDA_AB 0xAD  // Load Accumulator (Absolute Mode, 4) : C, T
#define LDA_ABX 0xBD // Load Accumulator (Absolute X Mode, 4 + 1 if page cross) : C, T
#define LDA_ABY 0xB9 // Load Accumulator (Absolute Y Mode, 4 + 1 if page cross) : C, T
#define LDA_INX 0xA1 // Load Accumulator (Indirect X, 6) : C, T
#define LDA_INY 0xB1 // Load Accumulator (Indirect Y, 5 + 1 if page cross) : C, T

// LDX : Load X Register

#define LDX_IM 0xA2  // Load X Register (Immediate Mode, 2) : C, T
#define LDX_ZP 0xA6  // Load X Register (Zero Page Mode, 3) : C, T
#define LDX_ZPY 0xB6 // Load X Register (Zero Page Y Mode, 4) : C, T
#define LDX_AB 0xAE  // Load X Register (Absolute Mode, 4) : C, T
#define LDX_ABY 0xBE // Load X Register (Absolute Y Mode, 4 + 1 if page cross) : C, T

// LDY : Load Y Register

#define LDY_IM 0xA0  // Load Y Register (Immediate Mode, 2) : C, T
#define LDY_ZP 0xA4  // Load Y Register (Zero Page Mode, 3) : C, T
#define LDY_ZPX 0xB4 // Load Y Register (Zero Page X Mode, 4) : C, T
#define LDY_AB 0xAC  // Load Y Register (Absolute Mode, 4) : C, T
#define LDY_ABX 0xBC // Load Y Register (Absolute X Mode, 4 + 1 if page cross) : C, T

// STA : Store Accumulator

#define STA_ZP 0x85  // Store Accumulator (Zero Page Mode, 3) : C, T
#define STA_ZPX 0x95 // Store Accumulator (Zero Page X Mode, 4) : C, T
#define STA_AB 0x8D  // Store Accumulator (Absolute Mode, 4) : C, T
#define STA_ABX 0x9D // Store Accumulator (Absolute X Mode, 5) : C, T
#define STA_ABY 0x99 // Store Accumulator (Absolute Y Mode, 5) : C, T
#define STA_INX 0x81 // Store Accumulator (Indirect X Mode, 6) : C, T
#define STA_INY 0x91 // Store Accumulator (Indirect Y Mode, 6) : C, T

// STX : Store X Register

#define STX_ZP 0x86  // Store X Register (Zero Page Mode, 3) : C, T
#define STX_ZPY 0x96 // Store X Register (Zero Page Y Mode, 4) : C, T
#define STX_AB 0x8E  // Store X Register (Absolute Mode, 4) : C, T

// STY : Store Y Register

#define STY_ZP 0x84  // Store Y Register (Zero Page Mode, 3) : C, T
#define STY_ZPX 0x94 // Store Y Register (Zero Page Y Mode, 4) : C, T
#define STY_AB 0x8C  // Store Y Register (Absolute Mode, 4) : C, T

// TAX : Transfer Accumulator to X Register

#define TAX_IMP 0xAA // Transfer Accumulator to X Register (Implied, 2) : C, T

// TAY : Transfer Accumulator to Y Register

#define TAY_IMP 0xA8 // Transfer Accumulator to Y Register (Implied, 2) : C, T

// TXA : Transfer X Register to Accumulator

#define TXA_IMP 0x8A // Transfer X Register to Accumulator (Implied, 2) : C, T

// TYA : Transfer Y Register to Accumulator

#define TYA_IMP 0x98 // Transfer Y Register to Accumulator (Implied, 2) : C, T

// TSX : Transfer Stack Pointer to X Register

#define TSX_IMP 0xBA // Transfer Stack Pointer to X Register (Implied, 2) : C, T

// TXS : Transfer X Register to Stack Pointer

#define TXS_IMP 0x9A // Transfer X Register to Stack Pointer (Implied, 2) : C, T

// PHA : Push Accumulator

#define PHA_IMP 0x48 // Push Accumulator to Stack (Implied, 3) : C, T

// PHP : Push Processor Status

#define PHP_IMP 0x08 // Push Processor Status to Stack (Implied, 3) : C, T

// PLA : Pull Accumulator

#define PLA_IMP 0x68 // Pull value from stack and store in accumulator (Implied, 4) : C, T

// PLP : Pull Processor Status

#define PLP_IMP 0x28 // Pull value from stack and store as processor status (Implied, 4) : C, T

// AND : Logical AND on Accumulator

#define AND_IM 0x29  // Logical AND on Accumulator (Immediate Mode, 2) : C, T
#define AND_ZP 0x25  // Logical AND on Accumulator (Zero Page Mode, 3) : C, T
#define AND_ZPX 0x35 // Logical AND on Accumulator (Zero Page X Mode, 4) : C, T
#define AND_AB 0x2D  // Logical AND on Accumulator (Absolute Mode, 4) : C, T
#define AND_ABX 0x3D // Logical AND on Accumulator (Absolute X Mode, 4 + 1 if Page Cross) : C, T
#define AND_ABY 0x39 // Logical AND on Accumulator (Absolute Y Mode, 4 + 1 if Page Cross) : C, T
#define AND_INX 0x21 // Logical AND on Accumulator (Indirect X Mode, 6) : C, T
#define AND_INY 0x31 // Logical AND on Accumulator (Indirect Y Mode, 5 + 1 if Page Cross) : C, T

// EOR : Exclusive OR (XOR) on Accumulator

#define EOR_IM 0x49  // Logical XOR on Accumulator (Immediate Mode, 2) : C, T
#define EOR_ZP 0x45  // Logical XOR on Accumulator (Zero Page Mode, 3) : C, T
#define EOR_ZPX 0x55 // Logical XOR on Accumulator (Zero Page X Mode, 4) : C, T
#define EOR_AB 0x4D  // Logical XOR on Accumulator (Absolute Mode, 4) : C, T
#define EOR_ABX 0x5D // Logical XOR on Accumulator (Absolute X Mode, 4 + 1 if Page Cross) : C, T
#define EOR_ABY 0x59 // Logical XOR on Accumulator (Absolute Y Mode, 4 + 1 if Page Cross) : C, T
#define EOR_INX 0x41 // Logical XOR on Accumulator (Indirect X Mode, 6) : C, T
#define EOR_INY 0x51 // Logical XOR on Accumulator (Indirect Y Mode, 5 + 1 if Page Cross) : C, T

// ORA : Inclusive OR (OR) on Accumulator

#define ORA_IM 0x09  // Logical OR on Accumulator (Immediate Mode, 2) : C, T
#define ORA_ZP 0x05  // Logical OR on Accumulator (Zero Page Mode, 3) : C, T
#define ORA_ZPX 0x15 // Logical OR on Accumulator (Zero Page X Mode, 4) : C, T
#define ORA_AB 0x0D  // Logical OR on Accumulator (Absolute Mode, 4) : C, T
#define ORA_ABX 0x1D // Logical OR on Accumulator (Absolute X Mode, 4 + 1 if Page Cross) : C, T
#define ORA_ABY 0x19 // Logical OR on Accumulator (Absolute Y Mode, 4 + 1 if Page Cross) : C, T
#define ORA_INX 0x01 // Logical OR on Accumulator (Indirect X Mode, 6) : C, T
#define ORA_INY 0x11 // Logical OR on Accumulator (Indirect Y Mode, 5 + 1 if Page Cross) : C, T

// BIT : Bit Test

#define BIT_ZP 0x24 // Bit Test (Zero Page Mode, 3) : C, T
#define BIT_AB 0x2C // Bit Test (Absolute Mode, 4) : C, T

// ADC : Add With Carry

#define ADC_IM 0x69  // Add With Carry (Immediate Mode, 2) : C
#define ADC_ZP 0x65  // Add With Carry (Zero Page Mode, 3) : C
#define ADC_ZPX 0x75 // Add With Carry (Zero Page X Mode, 4) : C
#define ADC_AB 0x6D  // Add With Carry (Absolute Mode, 4) : C
#define ADC_ABX 0x7D // Add With Carry (Absolute X Mode, 4 + 1 if Page Cross) : C
#define ADC_ABY 0x79 // Add With Carry (Absolute Y Mode, 4 + 1 if Page Cross) : C
#define ADC_INX 0x61 // Add With Carry (Indirect X Mode, 6) : C
#define ADC_INY 0x71 // Add With Carry (Indirect Y Mode, 5 + 1 if Page Cross) : C

// SBC : Subtract With Carry

#define SBC_IM 0xE9  // Subtract With Carry (Immediate Mode, 2) : C
#define SBC_ZP 0xE5  // Subtract With Carry (Zero Page Mode, 3) : C
#define SBC_ZPX 0xF5 // Subtract With Carry (Zero Page X Mode, 4) : C
#define SBC_AB 0xED  // Subtract With Carry (Absolute Mode, 4) : C
#define SBC_ABX 0xFD // Subtract With Carry (Absolute X Mode, 4 + 1 if Page Cross) : C
#define SBC_ABY 0xF9 // Subtract With Carry (Absolute Y Mode, 4 + 1 if Page Cross) : C
#define SBC_INX 0xE1 // Subtract With Carry (Indirect X Mode, 6) : C
#define SBC_INY 0xF1 // Subtract With Carry (Indirect Y Mode, 5 + 1 if Page Cross) : C

// CMP : Compare Accumulator

#define CMP_IM 0xC9  // Compare Accumulator (Immediate Mode, 2) : C
#define CMP_ZP 0xC5  // Compare Accumulator (Zero Page Mode, 3) : C
#define CMP_ZPX 0xD5 // Compare Accumulator (Zero Page X Mode, 4) : C
#define CMP_AB 0xCD  // Compare Accumulator (Absolute Mode, 4) : C
#define CMP_ABX 0xDD // Compare Accumulator (Absolute X Mode, 4 + 1 if Page Cross) : C
#define CMP_ABY 0xD9 // Compare Accumulator (Absolute Y Mode, 4 + 1 if Page Cross) : C
#define CMP_INX 0xC1 // Compare Accumulator (Indirect X Mode, 6) : C
#define CMP_INY 0xD1 // Compare Accumulator (Indirect Y Mode, 5 + 1 if Page Cross) : C

// CPX : Compare X Register

#define CPX_IM 0xE0 // Compare X Register (Immediate Mode, 2) : C
#define CPX_ZP 0xE4 // Compare X Register (Zero Page Mode, 3) : C
#define CPX_AB 0xEC // Compare X Register (Absolute Mode, 4) : C

// CPY : Compare Y Register

#define CPY_IM 0xC0 // Compare Y Register (Immediate Mode, 2) : C
#define CPY_ZP 0xC4 // Compare Y Register (Zero Page Mode, 3) : C
#define CPY_AB 0xCC // Compare Y Register (Absolute Mode, 4) : C

// INC : Increment Memory

#define INC_ZP 0xE6  // Increment value held at a given memory location (Zero Page Mode, 5) :
#define INC_ZPX 0xF6 // Increment value held at a given memory location (Zero Page X Mode, 6) :
#define INC_AB 0xEE  // Increment value held at a given memory location (Absolute Mode, 6) :
#define INC_ABX 0xFE // Increment value held at a given memory location (Absolute X Mode, 7) :

// INX : Increment X Register

#define INX_IMP 0xE8 // Increments the X Register (Implied Mode, 2)

// INY : Increment Y Register

#define INY_IMP 0xC8 // Increments the Y Register (Implied Mode, 2)

// DEC : Decrement Memory

#define DEC_ZP 0xC6  // Decrement value held at a given memory location (Zero Page Mode, 5) :
#define DEC_ZPX 0xD6 // Decrement value held at a given memory location (Zero Page X Mode, 6) :
#define DEC_AB 0xCE  // Decrement value held at a given memory location (Absolute Mode, 6) :
#define DEC_ABX 0xDE // Decrement value held at a given memory location (Absolute X Mode, 7) :

// DEX : Decrement X Register

#define DEX_IMP 0xCA // Decrement the X Register (Implied Mode, 2)

// DEY : Decrement X Register

#define DEY_IMP 0x88 // Decrement the Y Register (Implied Mode, 2)

// JSR : Jump to Subroutine

#define JSR_AB 0x20 // Jump to subroutine (Absolute Mode, 6) :

#endif