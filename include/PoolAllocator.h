//
// Created by root on 04.05.17.
//

#ifndef EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H
#define EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H

#include <cstddef>
#include <cstdint>

#define CREATE(varName, blockCount, blockSize) Allocator <blockCount, blockSize> varName;


class IHeap
{
public:
    virtual void* Allocate(size_t sizeInByte) = 0;
    virtual void Deallocate(void *) = 0;
    /* Returns remaining # of available bytes */
    virtual size_t Available() const = 0;

};


class WorkingHeap : public IHeap
{

public:
    void* Allocate(size_t sizeInByte);
    void Deallocate(void *);
    size_t Available() const;

private:
    size_t amountOfBlocks;
    size_t sizeOfBlocks;
    char* mapOfBlocks;
    bool* mapOfUsedBlocks;
    size_t* mapOfSizes;

    int blocksInUse = 0;


protected:
    WorkingHeap(size_t amountOfBlocks, size_t sizeOfBlocks, char* mapOfBlocks, bool* mapOfUsedBlocks, size_t* mapOfSizes)
    {
        this->amountOfBlocks = amountOfBlocks;
        this->sizeOfBlocks = sizeOfBlocks;
        this->mapOfBlocks = mapOfBlocks;
        this->mapOfUsedBlocks = mapOfUsedBlocks;
        this->mapOfSizes = mapOfSizes;
    }

};

template <size_t const blockcount, size_t const blocksize>
class Allocator : public WorkingHeap
{
private:
    char freeMapOfBlocks[blockcount * blocksize] = {0};
    bool mapOfUsedBlocks[blockcount] = {false};
    size_t mapOfSizes[blockcount] = {0};

public:
    Allocator() : WorkingHeap(blockcount, blocksize, freeMapOfBlocks, mapOfUsedBlocks, mapOfSizes)
    {
        //Constructor has nothing to do
    }

};

#endif //EMBEDDED_SYSTEMS_4_POOLALLOCATOR_H
