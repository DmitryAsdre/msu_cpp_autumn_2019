#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;
template <class T>
string to_str(T&& conv)
{
    stringstream ss;
    ss << conv;
    return ss.str(); 
}
template<class... argsT>
string format(const std::string& data, argsT&&... args)
{
    stringstream o;
    if(data.find("{}") !=  string::npos)
        throw runtime_error("void brackets");
    vector<string> params = {to_str(forward<argsT>(args))... };
    size_t begin = 0;
    size_t end = 0;
    while(true)
    {
        size_t end_old = end;
        begin = data.find("{", end);
        end = data.find("}", end);
        if(begin == string::npos || end == string::npos)
        {
            if(begin == string::npos && end == string::npos)
            {
                o << data.substr(end_old, data.length() - end_old);
                break;
            }
            else 
                throw std::runtime_error("brackets fail");
        }
        string inside = data.substr(begin + 1, end - begin - 1);
        o << data.substr(end_old, begin - end_old);
        int r = stoi(inside);
        if(r >= params.size())
            throw runtime_error("params out of index");
        o << params[r];
        end += 1;
    }
    return o.str();
}
void test1()
{
    try
    {
        assert(format("{0} + {0} = {1}", "one", 2) == "one + one = 2");
        assert(format("{0} + {1} = {1}", "one", 2) == "one + 2 = 2");
        assert(format("{1} + {1} = {1}", "one", 2) == "2 + 2 = 2");
        cout << "Test 1 passed" << endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << endl;
        cout << "Test 1 not passed" << endl;
    }
}
void test2()
{
    try
    {
        assert(format("{0}text", "1") == "1text");
        assert(format("{0}random things", "1") == "1random things");
        cout << "Test 2 passed " << endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << endl;
        cout << "Test 2 not passed" << endl;
    }
}
void test3()
{
    try
    {
        format("{", 1);
        cout << "Test 3 not passed" << endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << endl;
        cout << "Test 3 passed" << endl;
    }   
}
void test4()
{
    try
    {
        format("{}", 1);
        cout << "Test 4 not passed" << endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << endl;
        cout  <<"Test 4 passed" << endl;
    }
}
int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}