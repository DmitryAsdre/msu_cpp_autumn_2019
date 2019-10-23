#include "LinearAllocator.hpp"
LinearAllocator::~LinearAllocator()
{
    if(buffer != nullptr)
        std::free(buffer);
}
LinearAllocator::LinearAllocator(size_t maxSizeT):
    curPointer(0),
    maxSize(maxSizeT),
    buffer(nullptr)
{
    buffer = (char *)std::malloc(maxSizeT*sizeof(char));
    if(buffer == nullptr)
        throw std::runtime_error("cannot alloc memory");
}
char * LinearAllocator::alloc(size_t size)
{
    if(curPointer + size > maxSize)
        return nullptr;
    char * tmp = buffer + curPointer;
    curPointer += size;
    return tmp;
}
void LinearAllocator::reset()
{
    curPointer = 0;
    memset(buffer,0, maxSize*sizeof(char));
}