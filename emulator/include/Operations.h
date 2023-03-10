#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "EmulatorTypes.h"

// === ABOUT OPERATIONS ===

// OPER_XXX : given an address, OPER functions carry out the logic of each opcode
// OPER_XXX functions are not directly executed by the CPU, they are called inside of INS_XXX_YYY

// Note : Not all operations are here as some do not have multiple addressing modes, or are just very simple (eg. JMP)
// in this case they are directly implemented in the Instructions.c file

// === OPERATION DECLARATIONS ===

// OPER_LDA : Implements LDA Instruction (1 Cycle)
void OPER_LDA(CPU c, word address);

// OPER_LDX : Implements LDX Instruction (1 Cycle)
void OPER_LDX(CPU c, word address);

// OPER_LDY : Implements LDY Instruction (1 Cycle)
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

// OPER_CMP : Implements CMP Instruction
void OPER_CMP(CPU c, word address);

// OPER_CPX : Implements CPX Instruction
void OPER_CPX(CPU c, word address);

// OPER_CPY : Implements CPY Instruction
void OPER_CPY(CPU c, word address);

// OPER_INC : Implements INC Instruction
void OPER_INC(CPU c, word address);

// OPER_DEC : Implements DEC Instruction
void OPER_DEC(CPU c, word address);

// OPER_ASL : Implements ASL Instruction
void OPER_ASL(CPU c, word address);

// OPER_LSR : Implements LSR Instruction
void OPER_LSR(CPU c, word address);

// OPER_ROL : Implements ROL Instruction
void OPER_ROL(CPU c, word address);

// OPER_ROR : Implements ROR Instruction
void OPER_ROR(CPU c, word address);

// OPER_BRANCH : Implements Generic Branching
void OPER_BRANCH(CPU c, word rel_offset);

// === Status Register Functions ===

// SET_PS_ACCUMULATOR : Sets the processor status flags based on value in accumulator
void SET_PS_ACCUMULATOR(CPU c);

// SET_PS_XREGISTER : Sets the processor status flags based on value in the X Register
void SET_PS_XREGISTER(CPU c);

// SET_PS_YREGISTER : Sets the processor status flags based on value in the Y Register
void SET_PS_YREGISTER(CPU c);

// SET_PS_ADC : Sets the processor status flags based on Add with carry operation
void SET_PS_ADC(CPU c, word a_value, word value_to_add, word sum);

// SET_PS_SBC : Sets the processor status flags based on Subtract with carry operation
void SET_PS_SBC(CPU c, word a_value, word value_to_add, word sum);

// SET_PS_MEM_OP : Sets the processor status flags based on modified value in memory (INC and DEC ops)
void SET_PS_MEM_OP(CPU c, byte value);

#endif
