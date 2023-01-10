#include "Eagle.h"

#include "./unit_tests/test_memory.c"
#include "./unit_tests/test_cpu.c"
#include "./unit_tests/test_clock.c"

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

    // === CPU Collection ===
    ADD_TEST(CPU_COLLECTION, T_CPU_CREATE);
    ADD_TEST(CPU_COLLECTION, T_CPU_FREE_ONLY);
    ADD_TEST(CPU_COLLECTION, T_CPU_FREE_WITH_MEMORY_AND_CLOCK);

    // === RUN ===
    RUN_COLLECTION(CPU_COLLECTION);

    EAGLE_END();
}