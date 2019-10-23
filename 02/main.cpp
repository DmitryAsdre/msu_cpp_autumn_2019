#include <iostream>
#include <cstdlib>
#include "LinearAllocator.hpp"
using namespace std;
int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout << "Unexpected input ";
        return EXIT_FAILURE;
    }
    try
    {
        LinearAllocator allocator(stoi(argv[1]));
        for(int i = 2; i < argc; i++)
        {
            int t = stoi(argv[i]);
            if(t < 0)
                allocator.reset();
            else
            {
                size_t allocSize = t;
                char * tmp = allocator.alloc(allocSize);
                if(tmp == nullptr)
                    cout << "nullptr ";
                else 
                {
                    fill(tmp, tmp + allocSize, 0);
                    cout << allocSize << " ";
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}