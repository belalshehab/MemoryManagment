#include "memory.h"

Memory::Memory(QObject *parent): QAbstractListModel(parent), m_size(0)
{

}

Segment Memory::addSegment(const Segment &segment, Memory::AllocationMethod allocationMethod)
{
    //replace this with your implementation
    return Segment(0, 0, 0);
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

int Memory::rowCount(const QModelIndex &parent) const
{
    return m_segments.count();
}

QVariant Memory::data(const QModelIndex &index, int role) const
{
    //    if (!index.isValid())
    return QVariant();
}

QHash<int, QByteArray> Memory::roleNames() const
{
    return QHash<int, QByteArray>();
}


uint32_t Memory::size() const
{
    return m_size;
}

void Memory::resize(const uint32_t &size)
{
    if(m_segments.isEmpty())
    {
        m_segments.push_back(Segment(0, size, 0, true));
    }
    else
    {
        if(m_segments.last().m_isHole)
        {
            m_segments.last().m_limit += m_size - size;
        }
        else
        {
            uint32_t base = m_segments.last().m_base + m_segments.last().m_limit +1;
            m_segments.push_back(Segment(0, m_size - size, base, true));
        }
    }
}
