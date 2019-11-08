#include <iostream>
#include <string>
#include <cstdlib>
#include "BigInt.hpp"
using namespace std;
int main(int argc, char** argv)
{
    if(argc != 4 && argc != 3)
    {
        cout << "unexpected input" << endl;
        return EXIT_FAILURE;
    }
    try
    {
        if(argc == 4)
        {
            BigInt a(argv[1]);
            BigInt b(argv[3]);
            string lexem(argv[2]);
            if(lexem == "+")
                cout << a + b << endl;
            else if(lexem == "-")
                cout << a - b << endl;
            else if(lexem == ">")
                cout << (a > b) << endl;
            else if(lexem == "<")
                cout << (a < b) << endl;
            else if(lexem == "!=")
                cout << (a != b) << endl;
            else if(lexem == "+=")
                cout << (a += b) << endl;
            else if(lexem == "-=")
                cout << (a -= b) << endl;
            else if(lexem == ">=")
                cout << (a >= b) << endl;
            else if(lexem == "<=")
                cout << (a <= b) << endl;
            else if(lexem == "==")
                cout << (a == b) << endl;
            else
            {
                cout << "unknown lexem" << endl;
            }
        }
        else 
        {
            BigInt a(argv[2]);
            string lexem(argv[1]);
            if(lexem == "--")
                cout << --a << endl;
            else if(lexem == "++")
                cout << ++a << endl;
            else if(lexem == "-")
                cout << -a << endl;
            else 
                cout << "unknown lexem " << endl;
            
        }        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}