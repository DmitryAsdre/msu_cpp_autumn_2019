#include "Vector.hpp"
Vector::Vector():
    data(NULL),
    size(0),
    len(0)
{}
Vector::Vector(size_t l):
    data(new unsigned int [l]),
    size(0),
    len(l)
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
}
Vector::Vector(const unsigned int* d, size_t s):
    data(new unsigned int[s]),
    size(s),
    len(0)
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(data, d, sizeof(unsigned int)*size);
}
Vector::~Vector()
{
    if(data != NULL)
        delete[] data;
}


size_t Vector::getSize()const
{
    return size;
}
size_t Vector::getLen()const
{
    return len;
}

unsigned int Vector::operator[](size_t i)const
{
    if(i >= size)
        throw std::runtime_error("out of bound");
    return data[i];
}
unsigned int& Vector::operator[](size_t i)
{
    if(i >= size)
        throw std::runtime_error("out of bound");
    return data[i];
}

void Vector::push_back(unsigned int tmp)
{
    if(size == len)
        increase();
    data[size] = tmp;
    size++;
}
void Vector::increase()
{
    unsigned int* new_data = new unsigned int[size*2];
    if(new_data == NULL)
        throw std::runtime_error("cannot alloc mem");
    std::memcpy(new_data, data, size*2*sizeof(unsigned int));
    data = new_data;
    size *= 2;
}