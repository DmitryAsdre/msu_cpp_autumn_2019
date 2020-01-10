#include <iostream>
#include "vector.h"
#include <sstream>
#include <assert.h>

void test1()
{
    Vector<int> v(2);
    std::stringstream ss;
    for(auto &x : v)
        ss << x;
    assert(ss.str() == "00");
}

void test2()
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::stringstream ss;
    for(auto& x : v)
        ss << x;
    assert(ss.str() == "0123");
    v.clear();
    assert(v.size_() == 0);
}

void test3()
{
    Vector<int> v(5);
    v.resize(7);
    assert(v.size_() == 7);
}

void test4() {
    Vector<int> v(5);
    std::stringstream s;
    for (auto it = v.begin(); it != v.end(); ++it) {
        s << *it;
    }
    assert(s.str() == "00000");
}
void test5()
{
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    int tmp;
    tmp = v.pop_back();

    std::stringstream ss;
    for(auto i : v)
        ss << i;
    assert(ss.str() == "123" && tmp == 4);
}
int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "All test passed" << std::endl;
}