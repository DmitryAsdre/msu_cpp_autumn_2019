#ifndef LINEAR_ALLOCATOR
#define LINEAR_ALLOCATOR
#include <stddef.h>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string.h>
class LinearAllocator
{
    size_t curPointer;
    size_t maxSize;
    char * buffer;
public:
    LinearAllocator(size_t maxSize);
    ~LinearAllocator();
    char* alloc(size_t size);
    void reset();
};
#endif