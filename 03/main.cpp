#include <iostream>
#include <cstdlib>
#include "Matrix.hpp"
using namespace std;
int main()
{
    try
    {
        Matrix m(12, 10, 100);
        cout << m.getRows() << " " << m.getColumns() << endl;
        m /= 100;
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
                m[i][j] = i*12 + j;
        }
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}