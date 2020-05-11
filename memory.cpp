#include "memory.h"

Memory::Memory(uint32_t size): m_size(size)
{
    m_segments.push_back(Segment(1, m_size, 0, false));

}

Segment Memory::addSegment(const Segment &segment, Memory::AllocationMethod allocationMethod)
{
    //replace this with your implementation
    return Segment(0, 0);
}

int Memory::findHole(uint32_t size, Memory::AllocationMethod allocationMethode)
{
    //replace this with your implementation
    return -1;
}

bool Memory::removeSegment(const Segment &segment)
{
    //replace this with your implementation
    return false;
}

void Memory::mergeHoles()
{
    //replace this with your implementation
}

bool Memory::addProcess(const Process &process, Memory::AllocationMethod allocationMethode)
{
    //replace this with your implementation
    return false;
}

bool Memory::removeProcess(const Process &process)
{
    //replace this with your implementation
    return false;
}

bool Memory::addHole(const Segment &hole)
{
    //replace this with your implementation
    return false;
}

void Memory::memoryShuffle()
{
    //replace this with your implementation
}
