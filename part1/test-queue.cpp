//lang:Cpp

#include "queue.h"
#include "string.h"
#include <stdio.h>

// If a test fails, print failure, and exit.
void FAIL() {
    fprintf(stderr, "FAILURE\n");
    exit(1);
}

// If a test succeeds, print OK.
void OK(const char* m) {
    fprintf(stderr, "OK: %s\n", m);
}

// Test that some condition is true.
void t_true(bool p) {
    if (!p) FAIL();
}

// Test that some condition is false.
void t_false(bool p) {
    if (p) FAIL();
}

// Test examples defined here.
String* hello;
String* world;

Queue* q;
Queue* sq;

// Initialize the global examples for testing.
// Call uninitialize for each call to initialize.
void intialize() {
    hello = new String("hello");
    world = new String("world");
    q = new Queue();
    sq = new StrQueue();
}

// Unitialize the test examples by deleting them.
void uninitialize() {
    delete hello;
    delete world;
    delete q;
    delete sq;
}

// Run tests on Queue and StrQueue.
void test1() {
    intialize();

    t_true(q->equals(q));
    t_true(sq->equals(sq));

    t_true(q->isEmpty());
    t_true(sq->isEmpty());

    OK("isEmpty");

    t_true(q->size() == 0);
    t_true(sq->size() == 0);

    q->push(hello);
    sq->push(hello);

    t_true(q->size() == 1);
    t_true(sq->size() == 1);

    q->push(world);
    sq->push(world);

    t_true(q->size() == 2);
    t_true(sq->size() == 2);

    OK("size");

    t_true(q->peek()->equals(hello));
    t_true(sq->peek()->equals(hello));

    OK("peek");

    // The two queues should be equal (even though they are different types),
    // because they contain all equal items in the same positions.
    t_true(q->equals(sq));
    t_true(sq->equals(q));

    OK("equals");

    // If the queues are equal, they should have equal hash values.
    t_true(q->hash() == sq->hash());

    OK("hash");

    q->pop();
    sq->pop();

    t_true(q->size() == 1);
    t_true(sq->size() == 1);

    t_true(q->peek()->equals(world));
    t_true(sq->peek()->equals(world));

    q->pop();
    sq->pop();

    t_true(q->size() == 0);
    t_true(sq->size() == 0);

    t_true(q->isEmpty());
    t_true(sq->isEmpty());

    OK("TEST 1");

    uninitialize();
}

// Run more tests on Queue and StrQueue.
void test2() {
    intialize();

    q->push(hello);
    sq->push(hello);

    q->push(world);
    sq->push(world);

    q->clear();
    sq->clear();

    t_true(q->isEmpty());
    t_true(sq->isEmpty());

    OK("clear");

    q->push(hello);

    t_false(q->equals(sq));

    OK("not equal");

    OK("TEST 2");

    uninitialize();
}

// Entrypoint. Call the testing methods above.
int main() {
    test1();
    test2();
}