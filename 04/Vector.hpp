#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>
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
        Vector(const Vector& v);
        Vector(const unsigned int* d, size_t s);

        ~Vector();
        
        size_t getSize()const;
        size_t getLen()const;
        void push_back(unsigned int tmp);
        void strip();
        void setLen(size_t newLen);
        void setSize(size_t newSize);
        unsigned int operator[](size_t i)const;
        unsigned int& operator[](size_t i);

        Vector& operator =(const Vector& copy);
};
#endif