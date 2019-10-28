#include <iostream>
#include <cstdlib>
#include "Matrix.hpp"
using namespace std;
int main()
{
    try
    {
        Matrix m(12, 10, 100);
        m *= 10;
        cout << m << endl;
        m += 10;
        cout << m << endl;
        m -= 1000;
        cout << m << endl;
        m /= 10;
        cout << m << endl;
    }   
    catch(exception& e)
    {
        cout << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}