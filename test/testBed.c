#include "Eagle.h"

#include "./unit_tests/test_memory.c"
#include "./unit_tests/test_cpu.c"
#include "./unit_tests/test_clock.c"
#include "./unit_tests/test_lda.c"
#include "./unit_tests/test_ldx.c"
#include "./unit_tests/test_ldy.c"

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

    // === RUN ===
    // RUN_COLLECTION(CLOCK_COLLECTION);
    // RUN_COLLECTION(CPU_COLLECTION);
    // RUN_COLLECTION(LDA_COLLECTION);

    RUN_ALL();

    EAGLE_END();
}