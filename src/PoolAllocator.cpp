//
// Created by root on 04.05.17.
//

#include "../include/PoolAllocator.h"

void* WorkingHeap::Allocate (size_t sizeInByte){

    if((sizeInByte < 1) || (sizeInByte <= sizeOfBlocks*amountOfBlocks))
    {
        return nullptr;
    }
    size_t blocks = (sizeInByte + sizeOfBlocks -1) / sizeOfBlocks;
    bool foundFreeSpace = false;
    int freeSpace = -1;


    /*
     * TODO: find bug
     */
    for(unsigned int positionOfBlocks = 0; positionOfBlocks <= (amountOfBlocks - blocks); positionOfBlocks++)
    {
        if(!mapOfUsedBlocks[positionOfBlocks])
        {
            for(unsigned int i = 1; i < blocks; i++)
            {
                if(mapOfUsedBlocks[positionOfBlocks + i])
                {
                    positionOfBlocks += i;
                }else
                {
                    foundFreeSpace = true;
                    break;
                }
            }
            if(foundFreeSpace)
            {
                freeSpace = positionOfBlocks;
                break;
            }
        }
    }

    if(freeSpace < 0)
    {
        return nullptr;
    }

    blocksInUse += blocks;

    for (unsigned int i = 0; i < blocks; i++)
    {
        mapOfUsedBlocks[freeSpace + i] = true;
    }

    mapOfSizes[freeSpace] = blocks;


    return (void*) &mapOfBlocks[freeSpace * sizeOfBlocks];

}


void WorkingHeap::Deallocate(void* deallocatePointer) {

    int pOB = -1;

    for(unsigned int positionOfBlock = 0; positionOfBlock < amountOfBlocks; positionOfBlock++)
    {
        if(&mapOfBlocks[positionOfBlock * sizeOfBlocks] == deallocatePointer){
            pOB = positionOfBlock;
            break;
        }
    }

    if(pOB >= 0)
    {
        int blocks = mapOfSizes[pOB];
        for(int i = 0; i < blocks; i++)
        {
            mapOfUsedBlocks[pOB + i] = false;
            mapOfBlocks[(pOB + i) * sizeOfBlocks] = 0;
        }

        blocksInUse -= blocks;
        mapOfSizes[pOB] = 0;
    }

}


size_t WorkingHeap::Available() const{

    return (amountOfBlocks - blocksInUse) * sizeOfBlocks;

}