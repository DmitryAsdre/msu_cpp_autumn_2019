#include "Vector.hpp"
#include "BigInt.hpp"
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
    Vector v2(v);
    Vector v3;
    v3 = v;
    cout << v.getSize() << " " << v2.getSize() << " " << v3.getSize() << endl;
    cout << v[100] << " " << v2[100] << " " << v2[100] << endl;
    return 0;
}