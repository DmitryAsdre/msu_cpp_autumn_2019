#include <iostream>
#include <string>
using namespace std;
void f(int i)
{
    if(i == 0)
        throw  std::runtime_error("i == 0");
    else 
        throw runtime_error("i == 0");
}
void f2(int i)
{
    f(i);
}
int main()
{   
    try
    {
        f2(0);
        f2(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}