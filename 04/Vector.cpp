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
Vector::Vector(const Vector& v):
    data(new unsigned int [v.getLen()]),
    size(v.getSize()),
    len(v.getLen())
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(data, v.data, size*sizeof(unsigned int));
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
    increase();
    data[size] = tmp;
    size++;
}
void Vector::increase()
{
    if(size == len)
    {
        len = !len ? 1 : len;
        len *= 2;
        unsigned int* newData = new unsigned int[len];
        if(newData == NULL)
            throw std::runtime_error("cannot alloc memory");
        std::memcpy(newData, data, size*sizeof(unsigned int));
        delete[] data;
        data = newData;
    }
}
void Vector::strip()
{
    if(size == 0)
        return;
    for(size_t i = size - 1; i >= 0; i--)
    {
        if(data[i] == 0) 
            size--;
        else 
            break;
    }
    decrease();
}
void Vector::decrease()
{
    if(size < len/4 && len > 2)
    {
        unsigned int* newData = new unsigned int [len/2];
        if(newData == NULL)
            throw std::runtime_error("cannot alloc memory");
        len /= 2;
        std::memcpy(newData, data, size*sizeof(unsigned int));
        delete[] data;
        data = newData;
    }
}
Vector& Vector::operator=(const Vector& copy)
{
    if(data != NULL)
        delete[] data;
    len = copy.len;
    size = copy.size;
    data = new unsigned int[len];
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(data, copy.data, size*sizeof(unsigned int));
}