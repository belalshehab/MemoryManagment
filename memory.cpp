#include "memory.h"

Memory::Memory(uint32_t size): m_size(size)
{
    m_segments.push_back(Segment(1, m_size, 0, false));

}
