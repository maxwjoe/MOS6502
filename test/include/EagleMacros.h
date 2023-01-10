#ifndef EAGLE_LOG_H
#define EAGLE_LOG

#include "Eagle.h"
#include "stdio.h"

// === ABSTRACTION ===

// EAGLE_INIT : Initialises Eagle
#define EAGLE_INIT() Eagle __EAGLE_PTR__ = EagleNew()

// EAGLE_SET_VERBOSE : Sets whether output is detailed or not
#define EAGLE_SET_VERBOSE(__IS_VERBOSE__) EagleSetVerbose(__EAGLE_PTR__, __IS_VERBOSE__)

// TEST : Create a new unit test
#define TEST(__TEST_NAME__) void __TEST_NAME__(Test __EAGLE_TEST_ADT_PTR__)

// ADD_TEST : Adds a test to the given collection
#define ADD_TEST(__COLLECTION_NAME__, __TEST_NAME__) EagleAddTest(__EAGLE_PTR__, #__COLLECTION_NAME__, #__TEST_NAME__, &__TEST_NAME__)

// RUN_ALL : Runs all tests
#define RUN_ALL() EagleRunAll(__EAGLE_PTR__)

// RUN_COLLECTION : Runs all tests in a collection
#define RUN_COLLECTION(__COLLECTION_NAME__) EagleRunCollection(__EAGLE_PTR__, #__COLLECTION_NAME__)

// EAGLE_END : Cleanup
#define EAGLE_END() EagleFree(__EAGLE_PTR__)

// === ASSERTION ===

// CHECK_TRUE : Checks if the given condition is true
#define CHECK_TRUE(__BOOLEAN_EXPRESSION__) TestSetCondition(__EAGLE_TEST_ADT_PTR__, ConditionNew(#__BOOLEAN_EXPRESSION__, __BOOLEAN_EXPRESSION__))

// CHECK_FALSE : Checks if the given condition is false
#define CHECK_FALSE(__BOOLEAN_EXPRESSION__) CHECK_TRUE(!(__BOOLEAN_EXPRESSION__))

// CHECK_GREATER : Checks if A is Strictly Greater than B
#define CHECK_GREATER(__VARIABLE_A__, __VARIABLE_B__) CHECK_TRUE((__VARIABLE_A__ > __VARIABLE_B__))

// CHECK_LESS : Checks if A is Strictly Less than than B
#define CHECK_LESS(__VARIABLE_A__, __VARIABLE_B__) CHECK_TRUE((__VARIABLE_A__ < __VARIABLE_B__))

// CHECK_EQ : Checks if two values are equal
#define CHECK_EQ(__VARIABLE_A__, __VARIABLE_B__) CHECK_TRUE((__VARIABLE_A__ == __VARIABLE_B__))

// CHECK_NEQ : Checks if two variables are not equal
#define CHECK_NEQ(__VARIABLE_A__, __VARIABLE_B__) CHECK_TRUE((__VARIABLE_A__ != __VARIABLE_B__))

// === LOGGING ===

#define LOG_RED(X) printf("\e[0;31m%s\x1b[0m", X);
#define LOG_GREEN(X) printf("\e[0;32m%s\x1b[0m", X);

#endif