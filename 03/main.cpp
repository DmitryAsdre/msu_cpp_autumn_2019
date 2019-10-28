#include <iostream>
#include <cstdlib>
#include "Matrix.hpp"
using namespace std;
int main()
{
    try
    {
        Matrix m(12, 10, 100);
        cout << "Rows - " << m.getRows() << " Columns-" << m.getColumns() << endl;
        for(int i = 0; i < m.getRows(); i++)
        {
            for(int j = 0; j < m.getColumns(); j++)
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