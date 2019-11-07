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
    len(s)
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
    for(size_t i = size; i >= 1; i--)
    {
        if(data[i - 1] == 0) 
            size--;
        else 
            break;
    }
    if(size == 0)
        size = 1;
    decrease();
}
void Vector::setLen(size_t newLen)
{
    if(len >= newLen)
        return ;
    unsigned int* newData = new unsigned int[newLen];
    if(newData == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(newData, data, size*sizeof(unsigned int));
    delete[] data;
    data = newData;
}
void Vector::setSize(size_t newSize)
{
    if(size >= newSize)
        return ;
    if(len >= newSize)
    {
        std::memset(data + size, 0, newSize - size);
        size = newSize;
    }
    else 
    {
        unsigned int* newData = new unsigned int[newSize];
        if(newData == NULL)
            throw std::runtime_error("cannot alloc memory");
        std::memcpy(newData, data, size*sizeof(unsigned int));
        std::memset(newData + size, 0, newSize - size);
        delete[] data;
        data = newData;
        size = newSize;
        len = newSize;
    }
}
void Vector::decrease()
{
    if(size < len/4 && len > 5)
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