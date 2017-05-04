//
// Created by root on 04.05.17.
//

#ifndef EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H
#define EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H

#include <cstddef>

#define CREATE(varName, blockCount, blockSize) PoolAllocator <blockCount, blockSize> varName;


class IHeap
{
public:
    virtual void* Allocate(size_t sizeInByte) = 0;
    virtual void Deallocate(void *) = 0;
    /* Returns remaining # of available bytes */
    virtual size_t Available() const = 0;
};


#endif //EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H
