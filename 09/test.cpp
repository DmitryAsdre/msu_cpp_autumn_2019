#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool check()
{
    ifstream name1("sorted.bin", ios::binary);
    ifstream name2("input", ios::binary);
    size_t counter = 0;
    vector<uint64_t> sorted;
    vector<uint64_t> unsorted;
    while(true)
    {
        uint64_t buf;
        name1.read((char*)&buf, sizeof(uint64_t));
        if(name1.eof())
            break;
        sorted.push_back(buf);
    }
    while(true)
    {
        uint64_t buf;
        name2.read((char*)&buf, sizeof(uint64_t));
        if(name2.eof())
            break;
        unsorted.push_back(buf);
    }
    sort(unsorted.begin(), unsorted.end());
    if(unsorted == sorted)
        return true;
    else 
        return false;
}
int main()
{
    for(int i = 0; i < 10; i++)
    {
        system(("./main " + to_string(i + 5)).c_str());
        if(check())
            cout << "Test passed" << endl;
        else 
            cout << "Test not passed" << endl;
    }
    return 0;
}