#include <iostream>
#include <string>
#include <fstream>
#include "Serializer.hpp"
using namespace std;
int main()
{
    try
    {    
        Data data{1, true, 2};

        std::stringstream stream;

        Serializer s(stream);
        s.save<Data>(data);
        if(stream.str() != "1 true 2 ")
            throw std::runtime_error("error");
        Data data_{11, false, 0};
        Deserializer d(stream);

        d.load(data_);
        if(data.a != data_.a || data.b != data_.b || data.c != data_.c)
            throw std::runtime_error("error");
        cout << "Working correct " << endl;
    }
    catch(std::exception e)
    {
        cout << e.what() << endl;
    }
    return 0;
}