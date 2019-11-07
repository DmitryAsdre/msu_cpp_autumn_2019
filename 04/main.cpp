#include "Vector.hpp"
#include "BigInt.hpp"
#include <iostream>
#include <limits.h>
using namespace std;
int main()
{
    BigInt b(1);
    BigInt b1(1);
    while(b != -100)
    {
        --b;
        cout << b << endl;;
    }
    return 0;
}