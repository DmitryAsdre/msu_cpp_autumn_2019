#include "BigInt.hpp"
#include <iostream>
#include <limits.h>
#include <cstdlib>
using namespace std;
int main()
{
    try
    {
        BigInt a("0");
        BigInt b(0);
        cout << (a == b) << endl;
        cout << a + b << endl;
        cout << a - b << endl;
        cout << a + 1 << endl;
        cout << a - 1 << endl;
        a += 100;
        b -= 100;
        cout << a << endl;
        cout << b << endl;
        --a;
        ++b;
        cout << a << endl;
        cout << b << endl;
        a = -a;
        cout << a << endl;
        a = "1000";
        b = "-1000";
        cout << a << " " << b << endl;
        cout << a + b << endl;
        a = "100034343";
        b = "-100034343";
        cout << a + b << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return EXIT_SUCCESS;
}