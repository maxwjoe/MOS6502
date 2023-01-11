#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "EmulatorTypes.h"

// === ABOUT OPERATIONS ===

// OPER_XXX : given an address, OPER functions carry out the logic of each opcode
// OPER_XXX functions are not directly executed by the CPU, they are called inside of INS_XXX_YYY

// === OPERATION DECLARATIONS ===

// OPER_LDA : Implements LDA Instruction
void OPER_LDA(CPU c, word address);

// OPER_LDX : Implements LDX Instruction
void OPER_LDX(CPU c, word address);

// OPER_LDY : Implements LDY Instruction
void OPER_LDY(CPU c, word address);

// OPER_STA : Implements STA Instruction
void OPER_STA(CPU c, word address);

// OPER_STX : Implements STX Instruction
void OPER_STX(CPU c, word address);

// OPER_STY : Implements STY Instruction
void OPER_STY(CPU c, word address);

// OPER_AND : Implements AND Instruction
void OPER_AND(CPU c, word address);

// OPER_EOR : Implements EOR Instruction
void OPER_EOR(CPU c, word address);

// OPER_ORA : Implements ORA Instruction
void OPER_ORA(CPU c, word address);

// OPER_BIT : Implements BIT Instruction
void OPER_BIT(CPU c, word address);

// OPER_ADC : Implements ADC Instruction
void OPER_ADC(CPU c, word address);

// OPER_SBC : Implements SBC Instruction
void OPER_SBC(CPU c, word address);

// === Status Register Functions ===

// SET_PS_ACCUMULATOR : Sets the processor status flags based on value in accumulator
void SET_PS_ACCUMULATOR(CPU c);

#endif
