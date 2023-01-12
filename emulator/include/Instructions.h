#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "EmulatorTypes.h"

// === ABOUT INSTRUCTIONS ===

// INS_XXX_YYY : Where XXX is the Opcode, YYY is the addressing mode
// INS_XXX_YYY functions are the ones actually executed by the CPU for each opcode
// INS_XXX_XXX() is made up of an addressing function ADDR_XXX() and Operation function OPER_XXX()
// These two functions in combination give a specific version of each operation based on the addressing mode

// === INSTRUCTION DECLARATIONS ===

// --- LDA ---

// INS_LDA_IM : Executes LDA_IM
void INS_LDA_IM(CPU c);

// INS_LDA_ZP : Executes LDA_ZP
void INS_LDA_ZP(CPU c);

// INS_LDA_ZPX : Executes LDA_ZPX
void INS_LDA_ZPX(CPU c);

// INS_LDA_AB : Executes LDA_AB
void INS_LDA_AB(CPU c);

// INS_LDA_ABX : Executes LDA_ABX (TODO: Handle page cross)
void INS_LDA_ABX(CPU c);

// INS_LDA_ABY : Executes LDA_ABY (TODO: Handle page cross)
void INS_LDA_ABY(CPU c);

// INS_LDA_INX : Executes LDA_INX (TODO: Check CPU cycles)
void INS_LDA_INX(CPU c);

// INS_LDA_INY : Executes LDA_INY (TODO: Handle Page Cross)
void INS_LDA_INY(CPU c);

// --- LDX ---

// INS_LDX_IM : Executes LDX_IM
void INS_LDX_IM(CPU c);

// INS_LDX_ZP : Executes LDX_ZP
void INS_LDX_ZP(CPU c);

// INS_LDX_ZPY : Executes LDX_ZPY
void INS_LDX_ZPY(CPU c);

// INS_LDX_AB : Executes LDX_AB
void INS_LDX_AB(CPU c);

// INS_LDX_ABY : Executes LDX_ABY (TODO: Need to handle page crossing)
void INS_LDX_ABY(CPU c);

// --- LDY ---

// INS_LDY_IM : Executes LDY_IM
void INS_LDY_IM(CPU c);

// INS_LDY_ZP : Executes LDY_ZP
void INS_LDY_ZP(CPU c);

// INS_LDY_ZPX : Executes LDY_ZPX
void INS_LDY_ZPX(CPU c);

// INS_LDY_AB : Executes LDY_AB
void INS_LDY_AB(CPU c);

// INS_LDY_ABX : Executes LDY_ABX (TODO: Handle page crossing)
void INS_LDY_ABX(CPU c);

// --- STA ---

// INS_STA_ZP : Executes STA_ZP
void INS_STA_ZP(CPU c);

// INS_STA_ZPX : Executes STA_ZPX
void INS_STA_ZPX(CPU c);

// INS_STA_AB : Executes STA_AB
void INS_STA_AB(CPU c);

// INS_STA_ABX : Executes STA_ABX
void INS_STA_ABX(CPU c);

// INS_STA_ABY : Executes STA_ABY
void INS_STA_ABY(CPU c);

// INS_STA_INX : Executes STA_INX
void INS_STA_INX(CPU c);

// INS_STA_INY : Executes STA_INY
void INS_STA_INY(CPU c);

#endif