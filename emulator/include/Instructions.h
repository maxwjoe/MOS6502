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

// --- STX ---

// INS_STX_ZP : Executes STX_ZP
void INS_STX_ZP(CPU c);

// INS_STX_ZPY : Executes STX_ZPY
void INS_STX_ZPY(CPU c);

// INS_STX_AB : Executes STX_AB
void INS_STX_AB(CPU c);

// --- STY ---

// INS_STY_ZP : Executes STY_ZP
void INS_STY_ZP(CPU c);

// INS_STY_ZPX : Executes STY_ZPX
void INS_STY_ZPX(CPU c);

// INS_STY_AB : Executes STY_AB
void INS_STY_AB(CPU c);

// --- TAX ---

// INS_TAX_IMP : Executes TAX_IMP
void INS_TAX_IMP(CPU c);

// --- TAY ---

// INS_TAY_IMP : Executes TAY_IMP
void INS_TAY_IMP(CPU c);

// --- TXA ---

// INS_TXA_IMP : Executes TXA_IMP
void INS_TXA_IMP(CPU c);

// --- TYA ---

// INS_TYA_IMP : Executes TYA_IMP
void INS_TYA_IMP(CPU c);

// --- TSX ---

// INS_TSX_IMP : Executes TSX_IMP
void INS_TSX_IMP(CPU c);

// -- TXS ---

// INS_TXS_IMP : Executes TXS_IMP
void INS_TXS_IMP(CPU c);

// --- PHA ---

// INS_PHA_IMP : Executes PHA_IMP
void INS_PHA_IMP(CPU c);

// --- PHP ---

// INS_PHP_IMP : Executes PHP_IMP
void INS_PHP_IMP(CPU c);

// --- PLA ---

// INS_PLA_IMP : Executes PLA_IMP
void INS_PLA_IMP(CPU c);

// --- PLP ---

// INS_PLP_IMP : Executes PLP_IMP
void INS_PLP_IMP(CPU c);

// --- AND ---

// INS_AND_IM : Executes AND_IM
void INS_AND_IM(CPU c);

// INS_AND_ZP : Executes AND_ZP
void INS_AND_ZP(CPU c);

// INS_AND_ZPX : Executes AND_ZPX
void INS_AND_ZPX(CPU c);

// INS_AND_AB : Executes AND_AB
void INS_AND_AB(CPU c);

// INS_AND_ABX : Executes AND_ABX
void INS_AND_ABX(CPU c);

// INS_AND_ABY : Executes AND_ABY
void INS_AND_ABY(CPU c);

// INS_AND_INX : Executes AND_INX
void INS_AND_INX(CPU c);

// INS_AND_INY : Executes AND_INY
void INS_AND_INY(CPU c);

// --- EOR ---

// INS_EOR_IM : Executes EOR_IM
void INS_EOR_IM(CPU c);

// INS_EOR_ZP : Executes EOR_IM
void INS_EOR_ZP(CPU c);

// INS_EOR_ZPX : Executes EOR_ZPX
void INS_EOR_ZPX(CPU c);

// INS_EOR_AB : Executes EOR_AB
void INS_EOR_AB(CPU c);

// INS_EOR_ABX : Executes EOR_ABX
void INS_EOR_ABX(CPU c);

// INS_EOR_ABY : Executes EOR_ABY
void INS_EOR_ABY(CPU c);

// INS_EOR_INX : Executes EOR_INX
void INS_EOR_INX(CPU c);

// INS_EOR_INY : Executes EOR_INY
void INS_EOR_INY(CPU c);

// --- ORA ---

// INS_ORA_IM : Executes ORA_IM
void INS_ORA_IM(CPU c);

// INS_ORA_ZP : Executes ORA_IM
void INS_ORA_ZP(CPU c);

// INS_ORA_ZPX : Executes ORA_ZPX
void INS_ORA_ZPX(CPU c);

// INS_ORA_AB : Executes ORA_AB
void INS_ORA_AB(CPU c);

// INS_ORA_ABX : Executes ORA_ABX
void INS_ORA_ABX(CPU c);

// INS_ORA_ABY : Executes ORA_ABY
void INS_ORA_ABY(CPU c);

// INS_ORA_INX : Executes ORA_INX
void INS_ORA_INX(CPU c);

// INS_ORA_INY : Executes ORA_INY
void INS_ORA_INY(CPU c);

// --- BIT ---

// INS_BIT_ZP : Executes BIT_ZP
void INS_BIT_ZP(CPU c);

// INS_BIT_AB : Executes BIT_AB
void INS_BIT_AB(CPU c);

// --- ADC ---

// INS_ADC_IM : Executes ADC_IM
void INS_ADC_IM(CPU c);

// INS_ADC_ZP : Executes ADC_ZP
void INS_ADC_ZP(CPU c);

// INS_ADC_ZPX : Executes ADC_ZPX
void INS_ADC_ZPX(CPU c);

// INS_ADC_AB : Executes ADC_AB
void INS_ADC_AB(CPU c);

// INS_ADC_ABX : Executes ADC_ABX
void INS_ADC_ABX(CPU c);

// INS_ADC_ABY : Executes ADC_ABY
void INS_ADC_ABY(CPU c);

// INS_ADC_INX : Executes ADC_INX
void INS_ADC_INX(CPU c);

// INS_ADC_INY : Executes ADC_INY
void INS_ADC_INY(CPU c);

// --- JSR ---

// INS_JSR_AB : Executes JSR_AB
void INS_JSR_AB(CPU c);

// --- NOP ---

// INS_NOP_IM : Executes NOP_IM
void INS_NOP_IM(CPU c);

#endif