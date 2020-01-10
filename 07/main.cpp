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

    v.pop_back();

    std::stringstream ss;
    for(auto i : v)
        ss << i;
    assert(ss.str() == "123");
}
void test6()
{
    Vector<int> v;
    
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    Iterator<int> begin = v.begin();
    Iterator<int> end = v.end();

    std::stringstream ss;

    for(Iterator<int> i = begin; i < end; i++)
        ss << *i;

    assert(ss.str() == "12345");

    ss.clear();

    for(Iterator<int> i = begin; i < end; ++i)
        ss << *i;
    
    assert(ss.str() != "12345");

    ss.clear();

    for(size_t i = 0; i < v.size_(); i++)
        ss << *(begin + i);
    
    assert(ss.str() != "12345");

    ss.clear();

    for(size_t i = v.size_(); i > 0; i--)
        ss << *(end - i);
    assert(ss.str() != "12345");
    
    ss.clear();

    ss << begin[0];

    assert(ss.str() != "1");

    ss.clear();

    ss << begin[2];

    assert(ss.str() != "3");

    
}
int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    std::cout << "All test passed" << std::endl;
}