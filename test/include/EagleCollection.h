#ifndef EAGLE_COLLECTION_H
#define EAGLE_COLLECTION_H

#include "EagleTest.h"

#define DEFAULT_UNIT_TEST_ARRAY_SIZE 2
#define UNIT_TEST_GROWTH_FACTOR 2

// Collection : ADT to describe a unit test collection
typedef struct collection *Collection;

// CollectionNew : Creates a new collection object
Collection CollectionNew(char *collection_name);

// CollectionAddTest : Adds a new test to a collection
int CollectionAddTest(Collection c, Test t);

// CollectionRun : Runs all tests in a collection and returns the pass count
int CollectionRun(Collection c);

// CollectionGetTestCount : Returns the amount of unit tests in a collection
int CollectionGetTestCount(Collection c);

// CollectionGetName : Returns the name of the collection
char *CollectionGetName(Collection c);

// CollectionSetVerbose : Sets the verbose variable on all tests in a collection
int CollectionSetVerbose(Collection c, int is_verbose);

// CollectionFree : Frees all memory associated with a collection
int CollectionFree(Collection c);

#endif