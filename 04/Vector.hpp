#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <cstring>
class Vector
{
    private:
        unsigned int* data;
        size_t size;
        size_t len;
    private:
        void increase();
        void decrease();
    public:
        Vector();
        Vector(size_t l);
        Vector(const unsigned int* d, size_t s);

        ~Vector();
        
        size_t getSize()const;
        size_t getLen()const;
        void push_back(unsigned int tmp);
        void strip();
        unsigned int operator [](size_t i)const;
        unsigned int& operator [](size_t i);
};
#endif