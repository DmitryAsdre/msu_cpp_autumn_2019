#include "Vector.hpp"
#include <iostream>
using namespace std;
int main()
{
    Vector v;
    for(int i = 0; i < 1025; i++)
        v.push_back(i);
    for(int i = 0; i < v.getSize(); i++)
        cout << v[i] << endl;
    //v.strip();
    cout << v.getLen() << endl;
    return 0;
}