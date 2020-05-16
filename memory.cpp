#include "memory.h"
#include <QDebug>

Memory::Memory(QObject *parent) : QObject(parent), m_memorySegments(*m_memoryModel.segments()), m_lastPid(1), m_memorySize(10000)
{

    m_memorySegments.push_back(Segment(0, 0, 1400, 0, true));
    m_memorySegments.push_back(Segment(1, 1000, 1000, 1401, false));
    m_memorySegments.push_back(Segment(0, 0, 800, 2401, true));
    m_memorySegments.push_back(Segment(2, 1000, 1100, 3201, false));
    m_memorySegments.push_back(Segment(1, 1001, 400, 4301, false));
    m_memorySegments.push_back(Segment(0, 0, 4800, 4701, true));
    m_memorySegments.push_back(Segment(1, 1002, 500, 9501, false));

    for(int i = 0; i < m_memorySegments.count(); ++i)
    {
        m_memorySegments[i].m_color = "lightBlue";
    }
    m_memoryModel.update();
}

SegmentTableModel *Memory::segmentTableModel()
{
    return &m_segmentTableModel;
}

MemoryModel *Memory::memoryModel()
{
    return &m_memoryModel;
}

quint32 Memory::lastPid() const
{
    return m_lastPid;
}


std::pair<bool, Segment> Memory::addProcessSegment(const Segment &segment, Memory::AllocationMethod allocationMethod)
{
    int index_new_seg = findHole(segment.m_limit , allocationMethod);
    if ( index_new_seg  == -1)
    {
        return {false, Segment(0, 0, 0, 0)};
    }

    else
    {
        //insert new segment in list of segments
        m_memorySegments.insert(index_new_seg, segment);

        //update the base of new segment
        m_memorySegments[index_new_seg].m_base =   m_memorySegments[index_new_seg+1].m_base ;

        //update the base and limit of new hole
        m_memorySegments[index_new_seg+1].m_base  =  m_memorySegments[index_new_seg].m_base + m_memorySegments[index_new_seg ].m_limit;
        m_memorySegments[index_new_seg+1].m_limit =  m_memorySegments[index_new_seg +1].m_limit -  m_memorySegments[index_new_seg].m_limit;

        if(m_memorySegments[index_new_seg +1].m_limit < 1)
        {
            m_memorySegments.removeAt(index_new_seg +1);
        }

        return {true, m_memorySegments[index_new_seg]};
    }
}

int Memory::findHole(quint32 limitOfSegment, Memory::AllocationMethod allocationMethod)
{
    uint32_t min = m_memorySize;

    int min_index = -1 ;

    switch (allocationMethod) {
    case AllocationMethod::FIRST_FIT:

        for (int i = 0; i < m_memorySegments.size(); ++i) {
            if (m_memorySegments[i].m_isHole && m_memorySegments[i].m_limit >= limitOfSegment )
            {
                min_index = i ;
                break ;
            }
        }
        break;

    case AllocationMethod::BEST_FIT:
        for (int i = 0; i < m_memorySegments.size(); i++) {
            if (m_memorySegments[i].m_isHole && m_memorySegments[i].m_limit >= limitOfSegment )
            {
                if ( min > m_memorySegments[i].m_limit )
                {
                    min = m_memorySegments[i].m_limit;
                    min_index = i ;
                }
            }
        }
        break;

    case AllocationMethod::WORST_FIT:
        break;

    }
    return min_index;
}

bool Memory::removeSegment(const Segment &segment){

    int index = m_memorySegments.indexOf(segment);
    if(index < 0)
    {
        return false;
    }

    else
    {
        m_memorySegments[index].m_isHole = true;
        m_memorySegments[index].m_sid = 0;
        m_memorySegments[index].m_pid = 0;
        m_memorySegments[index].m_name = "";
        return true ;
    }
}


void Memory::mergeHoles()
{
    for (int i = 0; i < m_memorySegments.size() -1; ){
        if (m_memorySegments[i].m_isHole)
        {
            if( m_memorySegments[i+1].m_isHole)
            {
                m_memorySegments[i].m_limit = m_memorySegments[i].m_limit + m_memorySegments[i+1].m_limit;
                m_memorySegments.removeAt(i +1);
            }

            else
            {
                ++i;
            }
        }

        else
        {
            ++i;
        }
    }
}

bool Memory::addProcess(AllocationMethod allocationMethod, const QColor &color)
{
    auto &segmentTable =  *m_segmentTableModel.segmentList();

    bool success = true;
    int breakIndex = 0;

    std::sort(segmentTable.begin(), segmentTable.end(), [](const Segment &segment1, const Segment &segment2){
        return segment1.m_limit > segment2.m_limit;
    });

    for(int i = 0; i < segmentTable.size(); ++i)
    {
        segmentTable[i].m_color = color;

        auto addedSegmentPair = addProcessSegment(segmentTable[i], allocationMethod);
        if(addedSegmentPair.first)
        {
            segmentTable[i] = addedSegmentPair.second;
        }

        else
        {
            success = false;
            breakIndex = i;
            break;
        }
    }
    if(success)
    {
        m_memoryModel.update();
        ++m_lastPid;
    }

    else
    {
        for(int i = 0; i < breakIndex; ++i)
        {
            removeSegment(segmentTable[i]);
        }
        mergeHoles();
    }
    return success;
}


void Memory::removeProcess(quint32 pid)
{   
    for(const Segment &segment: m_memorySegments)
    {
        if(segment.m_pid == pid)
        {
            removeSegment(segment);
        }
    }
    mergeHoles();

    m_memoryModel.update();
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



uint32_t Memory::memorySize() const
{
    return m_memorySize;
}


void Memory::resizeMemory(const uint32_t &newMemorySize)
{
    if(newMemorySize > m_memorySize)
    {
        if(m_memorySegments.isEmpty())
        {
            m_memorySegments.push_back(Segment(0, newMemorySize, 0, true));
        }
        else
        {
            if(m_memorySegments.last().m_isHole)
            {
                m_memorySegments.last().m_limit += m_memorySize - newMemorySize;
            }
            else
            {
                uint32_t base = m_memorySegments.last().m_base + m_memorySegments.last().m_limit;
                m_memorySegments.push_back(Segment(0, m_memorySize - newMemorySize, base, true));
            }
        }
        m_memorySize = newMemorySize;
    }

    else if(newMemorySize < m_memorySize)
    {
        if(m_memorySegments.back().m_isHole && m_memorySegments.back().m_limit >= m_memorySize - newMemorySize)
        {
            m_memorySegments.back().m_limit -= m_memorySize - newMemorySize;
            m_memorySize = newMemorySize;
        }
    }
}
