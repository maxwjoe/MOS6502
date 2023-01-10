#ifndef EAGLE_H
#define EAGLE_H

#include "EagleTypes.h"
#include "EagleCollection.h"
#include "EagleMacros.h"

#define DEFAULT_COLLECTION_ARRAY_SIZE 5
#define COLLECTION_ARRAY_GROWTH_FACTOR 2

// Eagle : ADT to interact with the Eagle Testing API
typedef struct eagle *Eagle;

// EagleNew : Creates a new eagle instance
Eagle EagleNew();

// EagleSetVerbose : Sets output level (Verbose is detailed)
int EagleSetVerbose(Eagle e, int is_verbose);

// EagleAddCollection : Adds a new collection and returns a pointer to it
Collection EagleAddCollection(Eagle e, char *collection_name);

// EagleAddTest : Adds a test to a specified collection
int EagleAddTest(Eagle e, char *collection_name, char *test_name, unitTestPtr test);

// EagleRunAll : Runs all tests
int EagleRunAll(Eagle e);

// EagleRunCollection : Runs all tests in a given collection
int EagleRunCollection(Eagle e, char *collection_name);

// EagleFree : Frees all memory associated with an Eagle instance
int EagleFree(Eagle e);

#endif