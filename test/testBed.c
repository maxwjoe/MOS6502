#include "Eagle.h"

#include "./unit_tests/test_memory.c"
#include "./unit_tests/test_cpu.c"
#include "./unit_tests/test_clock.c"
#include "./unit_tests/test_lda.c"
#include "./unit_tests/test_ldx.c"
#include "./unit_tests/test_ldy.c"
#include "./unit_tests/test_store_reg.c"
#include "./unit_tests/test_stack_trans.c"
#include "./unit_tests/test_logical.c"
#include "./unit_tests/test_arithmetic.c"

int main()
{
    EAGLE_INIT();

    // === Memory Collection ===
    ADD_TEST(MEMORY_COLLECTION, T_MEMORY_CREATE);
    ADD_TEST(MEMORY_COLLECTION, T_MEMORY_FREE);
    ADD_TEST(MEMORY_COLLECTION, T_MEMORY_READ_WRITE);
    ADD_TEST(MEMORY_COLLECTION, T_MEMORY_BOUNDS_LOWER);
    ADD_TEST(MEMORY_COLLECTION, T_MEMORY_BOUNDS_UPPER);

    // === Clock Collection ===
    ADD_TEST(CLOCK_COLLECTION, T_CLOCK_CREATE);
    ADD_TEST(CLOCK_COLLECTION, T_CLOCK_FREE);

    // === CPU Collection ===
    ADD_TEST(CPU_COLLECTION, T_CPU_CREATE);
    ADD_TEST(CPU_COLLECTION, T_CPU_FREE_ONLY);
    ADD_TEST(CPU_COLLECTION, T_CPU_FREE_WITH_MEMORY_AND_CLOCK);
    ADD_TEST(CPU_COLLECTION, T_CPU_FETCH_BYTE);
    ADD_TEST(CPU_COLLECTION, T_CPU_FETCH_WORD);
    ADD_TEST(CPU_COLLECTION, T_CPU_READ_BYTE);
    ADD_TEST(CPU_COLLECTION, T_CPU_READ_WORD);
    ADD_TEST(CPU_COLLECTION, T_CPU_WRITE_BYTE);
    ADD_TEST(CPU_COLLECTION, T_CPU_SET_AND_READ_STATUS_REG);
    ADD_TEST(CPU_COLLECTION, T_CPU_SET_AND_READ_FLAGS);

    // === LDA Collection ===
    ADD_TEST(LDA_COLLECTION, T_LDA_IM);
    ADD_TEST(LDA_COLLECTION, T_LDA_ZP);
    ADD_TEST(LDA_COLLECTION, T_LDA_ZPX);
    ADD_TEST(LDA_COLLECTION, T_LDA_AB);
    ADD_TEST(LDA_COLLECTION, T_LDA_ABX_NO_CROSS);
    ADD_TEST(LDA_COLLECTION, T_LDA_ABX_WITH_CROSS);
    ADD_TEST(LDA_COLLECTION, T_LDA_ABY_NO_CROSS);
    ADD_TEST(LDA_COLLECTION, T_LDA_INX);
    ADD_TEST(LDA_COLLECTION, T_LDA_INY_NO_CROSS);
    ADD_TEST(LDA_COLLECTION, T_LDA_INY_WITH_CROSS);

    // === LDX Collection ===
    ADD_TEST(LDX_COLLECTION, T_LDX_IM);
    ADD_TEST(LDX_COLLECTION, T_LDX_ZP);
    ADD_TEST(LDX_COLLECTION, T_LDX_ZPY);
    ADD_TEST(LDX_COLLECTION, T_LDX_AB);
    ADD_TEST(LDX_COLLECTION, T_LDX_ABY_NO_CROSS);
    ADD_TEST(LDX_COLLECTION, T_LDX_ABY_WITH_CROSS);

    // === LDY Collection ===
    ADD_TEST(LDY_COLLECTION, T_LDY_IM);
    ADD_TEST(LDY_COLLECTION, T_LDY_ZP);
    ADD_TEST(LDY_COLLECTION, T_LDY_ZPX);
    ADD_TEST(LDY_COLLECTION, T_LDY_AB);
    ADD_TEST(LDY_COLLECTION, T_LDY_ABX_NO_CROSS);
    ADD_TEST(LDY_COLLECTION, T_LDY_ABX_WITH_CROSS);

    // === STORE_REGISTER Collection ===
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_ZP);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_ZPX);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_AB);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_ABX);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_ABY);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_INX);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STA_INY);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STX_ZP);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STX_ZPY);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STX_AB);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STY_ZP);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STY_ZPX);
    ADD_TEST(STORE_REGISTER_COLLECTION, T_STY_AB);

    // === TRANSFER_REG_STACK Collection ===
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TAX_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TAY_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TXA_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TYA_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TSX_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_TXS_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_PUSH_POP_STACK);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_PHA_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_PHP_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_PLA_IMP);
    ADD_TEST(TRANSFER_REG_STACK_COLLECTION, T_PLP_IMP);

    // === LOGICAL Collection ===
    ADD_TEST(LOGICAL_COLLECTION, T_AND_IM);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ZP);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ZPX);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_AB);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ABX_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ABX_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ABY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_ABY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_INX);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_INY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_AND_INY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_IM);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ZP);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ZPX);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_AB);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ABX_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ABX_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ABY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_ABY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_INX);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_INY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_EOR_INY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_IM);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ZP);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ZPX);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_AB);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ABX_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ABX_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ABY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_ABY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_INX);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_INY_NO_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_ORA_INY_WITH_CROSS);
    ADD_TEST(LOGICAL_COLLECTION, T_BIT_ZP);
    ADD_TEST(LOGICAL_COLLECTION, T_BIT_AB);

    // === ARITHMETIC Collection ===
    ADD_TEST(ARITHMETIC_COLLECTION, T_ADC_IM);
    ADD_TEST(ARITHMETIC_COLLECTION, T_ADC_ZP);
    ADD_TEST(ARITHMETIC_COLLECTION, T_ADC_ZPX);
    // TODO: Complete this

    // === RUN ===
    RUN_ALL();

    EAGLE_END();
}