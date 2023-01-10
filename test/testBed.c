#include "Eagle.h"

#include "./unit_tests/test_memory.c"

int main()
{
    EAGLE_INIT();

    // === Memory Collection ===
    ADD_TEST(MEMORY, T_MEMORY_CREATE);
    ADD_TEST(MEMORY, T_MEMORY_FREE);
    ADD_TEST(MEMORY, T_MEMORY_READ_WRITE);
    ADD_TEST(MEMORY, T_MEMORY_BOUNDS_LOWER);
    ADD_TEST(MEMORY, T_MEMORY_BOUNDS_UPPER);

    // === RUN ===
    RUN_COLLECTION(MEMORY);

    EAGLE_END();
}