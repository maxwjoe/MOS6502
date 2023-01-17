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

// INS_LDA_ABX : Executes LDA_ABX
void INS_LDA_ABX(CPU c);

// INS_LDA_ABY : Executes LDA_ABY
void INS_LDA_ABY(CPU c);

// INS_LDA_INX : Executes LDA_INX
void INS_LDA_INX(CPU c);

// INS_LDA_INY : Executes LDA_INY
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

// INS_LDX_ABY : Executes LDX_ABY
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

// INS_LDY_ABX : Executes LDY_ABX
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

// --- SBC ---

// INS_SBC_IM : Executes SBC_IM
void INS_SBC_IM(CPU c);

// INS_SBC_ZP : Executes SBC_ZP
void INS_SBC_ZP(CPU c);

// INS_SBC_ZPX : Executes SBC_ZPX
void INS_SBC_ZPX(CPU c);

// INS_SBC_AB : Executes SBC_AB
void INS_SBC_AB(CPU c);

// INS_SBC_ABX : Executes SBC_ABX
void INS_SBC_ABX(CPU c);

// INS_SBC_ABY : Executes SBC_ABY
void INS_SBC_ABY(CPU c);

// INS_SBC_INX : Executes SBC_INX
void INS_SBC_INX(CPU c);

// INS_SBC_INY : Executes SBC_INY
void INS_SBC_INY(CPU c);

// --- CMP ---

// INS_CMP_IM : Executes CMP_IM
void INS_CMP_IM(CPU c);

// INS_CMP_ZP : Executes CMP_ZP
void INS_CMP_ZP(CPU c);

// INS_CMP_ZPX : Executes CMP_ZPX
void INS_CMP_ZPX(CPU c);

// INS_CMP_AB : Executes CMP_AB
void INS_CMP_AB(CPU c);

// INS_CMP_ABX : Executes CMP_ABX
void INS_CMP_ABX(CPU c);

// INS_CMP_ABY : Executes CMP_ABY
void INS_CMP_ABY(CPU c);

// INS_CMP_INX : Executes CMP_INX
void INS_CMP_INX(CPU c);

// INS_CMP_INY : Executes CMP_INY
void INS_CMP_INY(CPU c);

// --- CPX ---

// INS_CPX_IM : Executes CPX_IM
void INS_CPX_IM(CPU c);

// INS_CPX_ZP : Executes CPX_ZP
void INS_CPX_ZP(CPU c);

// INS_CPX_AB : Executes CPX_AB
void INS_CPX_AB(CPU c);

// --- CPY ---

// INS_CPY_IM : Executes CPY_IM
void INS_CPY_IM(CPU c);

// INS_CPY_ZP : Executes CPY_ZP
void INS_CPY_ZP(CPU c);

// INS_CPY_AB : Executes CPY_AB
void INS_CPY_AB(CPU c);

// --- INC ---

// INS_INC_ZP : Executes INC_ZP
void INS_INC_ZP(CPU c);

// INS_INC_ZPX : Executes INC_ZPX
void INS_INC_ZPX(CPU c);

// INS_INC_AB : Executes INC_AB
void INS_INC_AB(CPU c);

// INS_INC_ABX : Executes INC_ABX
void INS_INC_ABX(CPU c);

// -- DEC ---

// INS_DEC_ZP : Executes DEC_ZP
void INS_DEC_ZP(CPU c);

// INS_DEC_ZPX : Executes DEC_ZPX
void INS_DEC_ZPX(CPU c);

// INS_DEC_AB : Executes DEC_AB
void INS_DEC_AB(CPU c);

// INS_DEC_ABX : Executes DEC_ABX
void INS_DEC_ABX(CPU c);

// --- INX ---

// INS_INX_IMP : Executes INX_IMP
void INS_INX_IMP(CPU c);

// --- INY ---

// INS_INY_IMP : Executes INY_IMP
void INS_INY_IMP(CPU c);

// --- DEX ---

// INS_DEX_IMP : Executes DEX_IMP
void INS_DEX_IMP(CPU c);

// --- DEY ---

// INS_DEY_IMP : Executes DEY_IMP
void INS_DEY_IMP(CPU c);

// --- ASL ---

// INS_ASL_ACC : Executes ASL_ACC
void INS_ASL_ACC(CPU c);

// INS_ASL_ZP : Executes ASL_ZP
void INS_ASL_ZP(CPU c);

// INS_ASL_ZPX : Executes ASL_ZPX
void INS_ASL_ZPX(CPU c);

// INS_ASL_AB : Executes ASL_AB
void INS_ASL_AB(CPU c);

// INS_ASL_ABX : Executes ASL_ABX
void INS_ASL_ABX(CPU c);

// --- LSR ---

// INS_LSR_ACC : Executes LSR_ACC
void INS_LSR_ACC(CPU c);

// INS_LSR_ZP : Executes LSR_ZP
void INS_LSR_ZP(CPU c);

// INS_LSR_ZPX : Executes LSR_ZPX
void INS_LSR_ZPX(CPU c);

// INS_LSR_AB : Executes LSR_AB
void INS_LSR_AB(CPU c);

// INS_LSR_ABX : Executes LSR_ABX
void INS_LSR_ABX(CPU c);

// --- ROL ---

// INS_ROL_ACC : Executes ROL_ACC
void INS_ROL_ACC(CPU c);

// INS_ROL_ZP : Executes ROL_ZP
void INS_ROL_ZP(CPU c);

// INS_ROL_ZPX : Executes ROL_ZPX
void INS_ROL_ZPX(CPU c);

// INS_ROL_AB : Executes ROL_AB
void INS_ROL_AB(CPU c);

// INS_ROL_ABX : Executes ROL_ABX
void INS_ROL_ABX(CPU c);

// --- ROR ---

// INS_ROR_ACC : Executes ROR_ACC
void INS_ROR_ACC(CPU c);

// INS_ROR_ZP : Executes ROR_ZP
void INS_ROR_ZP(CPU c);

// INS_ROR_ZPX : Executes ROR_ZPX
void INS_ROR_ZPX(CPU c);

// INS_ROR_AB : Executes ROR_AB
void INS_ROR_AB(CPU c);

// INS_ROR_ABX : Executes ROR_ABX
void INS_ROR_ABX(CPU c);

// --- JMP ---

// INS_JMP_AB : Executes JMP_AB
void INS_JMP_AB(CPU c);

// INS_JMP_IND : Executes JMP_IND
void INS_JMP_IND(CPU c);

// --- JSR ---

// INS_JSR_AB : Executes JSR_AB
void INS_JSR_AB(CPU c);

// --- RTS ---

// INS_RTS_IMP : Executes RTS_IMP
void INS_RTS_IMP(CPU c);

// --- NOP ---

// INS_NOP_IM : Executes NOP_IM
void INS_NOP_IM(CPU c);

#endif