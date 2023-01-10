#ifndef EAGLE_TEST_H
#define EAGLE_TEST_H

#include "EagleTypes.h"
#include "EagleCondition.h"

#define DEFAULT_VERBOSE_VALUE 1
#define DEFAULT_CONDITION_TABLE_CAPACITY 10
#define CONDITION_TABLE_GROWTH_FACTOR 2

// Test : ADT to represent a unit test
typedef struct test *Test;

// TestNew : Creates a new test
Test TestNew(char *name, unitTestPtr test);

// TestRun : Runs a test and returns an integer describing the result
int TestRun(Test t);

// TestSetCondition : Sets a condition into the test's condition table
int TestSetCondition(Test t, Condition c);

// TestSetVerbose : Sets whether a test is verbose (detailed output)
void TestSetVerbose(Test t, int is_verbose);

// TestFree : Frees memory associated with a test (Incl. Condition Table)
int TestFree(Test t);

#endif