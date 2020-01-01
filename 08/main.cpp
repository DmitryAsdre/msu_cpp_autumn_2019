#include <iostream>
#include <thread>
#include "Pool.h"
#include <assert.h>

using namespace std;

struct Structure {};

void test_function(const Structure &) {}


void test1() {
    Pool pool(8);
    int s = 12;
    auto task1 = pool.exec([s]() { return s; });
    assert(task1.get() == 12);
}

void test2() {
    Pool pool(8);
    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
}

void test3() {
    Pool pool(8);
    auto task0 = pool.exec(test_function, Structure());
    int s = 1;
    auto task1 = pool.exec([s]() { return s; });
    assert(task1.get() == 1);

    auto task2 = pool.exec([s]() { return s + 1; });
    assert(task2.get() == 2);

    auto task3 = pool.exec([s]() { return s + 2; });
    assert(task3.get() == 3);
}

int main() {
    test1();
    cout << "Test 1 passed" << endl;
    test2();
    cout << "Test 2 passed " << endl;
    test3();
    cout << "Test 3 passed" << endl;
    cout << "All tests passed" << endl;
    return 0;
}
