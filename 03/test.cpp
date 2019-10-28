#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include "Matrix.hpp"
using namespace std;
int main()
{
    string str;
    try
    {
        Matrix m(10, 20, 1);
        assert(m.getColumns() == 20);
        assert(m.getRows() == 10);
        cout << "Test 1 passed" << endl;
        m *= 2;
        for(int i = 0; i < m.getRows(); i++)
        {
            for(int j = 0; j < m.getColumns(); j++)
            {
                assert(m[i][j] == 2);
            }
        }
        cout << "Test 2 passed" << endl;
        try
        {
            m[1][112];
        }
        catch(const std::exception& e0)
        {
            if(e0.what() == string("out of range"))
                cout << "Test 3 passed" << endl;
            else 
                cout << "Test 3 not passed" << endl;
        }
        for(int i = 0; i < m.getRows(); i++)
        {
            for(int j = 0; j < m.getColumns(); j++)
                m[i][j] = i*m.getColumns() + j;
        }
        for(int i = 0; i < m.getRows(); i++)
        {
            for(int j = 0; j < m.getColumns(); j++)
            {
                assert(m[i][j] == i*m.getColumns() + j);
            }
        }
        cout << "Test 4 passed" << endl;
        Matrix m2(m);
        if(m2 == m)
            cout << "Test 5 passed" << endl;
        else
            cout << "Test 5 not passed" << endl;
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        cout << "Hello world" << endl;
        exit(EXIT_FAILURE);
    }  
    cout << " end " << endl;
    return 0;
}