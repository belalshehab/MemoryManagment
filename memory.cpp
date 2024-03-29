#include "memory.h"
#include <QDebug>

Memory::Memory(QObject *parent) : QObject(parent), m_memorySegments(*m_memoryModel.segments())
{

    resetMemory(1);

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

void Memory::setLastPid(const quint32 &lastPid)
{
    if(m_lastPid == lastPid)
        return;

    m_lastPid = lastPid;
    emit lastPidChanged();
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
    uint32_t max = 0 ;
    int segmentIndex = -1 ;

    switch (allocationMethod) {
    case AllocationMethod::FIRST_FIT:

        for (int i = 0; i < m_memorySegments.size(); ++i) {
            if (m_memorySegments[i].m_isHole && m_memorySegments[i].m_limit >= limitOfSegment )
            {
                segmentIndex = i ;
                break ;
            }
        }
        break;

    case AllocationMethod::BEST_FIT:
        for (int i = 0; i < m_memorySegments.size(); i++) {
            if (m_memorySegments[i].m_isHole && m_memorySegments[i].m_limit >= limitOfSegment )
            {
                if (m_memorySegments[i].m_limit < min)
                {
                    min = m_memorySegments[i].m_limit;
                    segmentIndex = i ;
                }
            }
        }
        break;

    case AllocationMethod::WORST_FIT:
        for (int i = 0; i < m_memorySegments.size(); i++) {
            if (m_memorySegments[i].m_isHole && m_memorySegments[i].m_limit >= limitOfSegment )
            {
                if (m_memorySegments[i].m_limit > max)
                {
                    max = m_memorySegments[i].m_limit;
                    segmentIndex = i ;
                }
            }
        }
        break;
    }
    return segmentIndex;
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

bool Memory::addProcess(AllocationMethod allocationMethod)
{
    auto &segmentTable =  *m_segmentTableModel.segmentList();

    QColor color = m_segmentTableModel.color();
    bool success = true;
    int breakIndex = 0;

    std::sort(segmentTable.begin(), segmentTable.end(), [](const Segment &segment1, const Segment &segment2){
        return segment1.m_limit > segment2.m_limit;
    });

    for(int i = 0; i < segmentTable.size(); ++i)
    {
        segmentTable[i].m_color = color;
        segmentTable[i].m_pid = m_lastPid;
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

bool Memory::addHole(quint32 limit, quint32 base)
{
    for(int i = 0; i < m_memorySegments.count(); ++i)
    {
        Segment &s = m_memorySegments[i];
        if(!s.m_isHole)
        {
            if(base >= s.m_base && (s.m_base + s.m_limit) > base)
            {
                if((base + limit) <= (s.m_base + s.m_limit))
                {
                    m_memorySegments.insert(i+1, Segment(0, 0, limit, base, true));

                    if(base + limit < s.m_base + s.m_limit)
                    {
                        m_memorySegments.insert(i+2, Segment(1, m_lastPid++, (s.m_base + s.m_limit) - (base + limit), base + limit));
                        m_memorySegments[i+2].m_color = "lightBlue";
                    }

                    if(base == s.m_base)
                    {
                        m_memorySegments.removeAt(i);
                    }
                    else
                    {
                        s.m_limit = base - s.m_base;
                    }
                    mergeHoles();
                    m_memoryModel.update();
                    return true;
                }
            }
        }
    }
    return false;
}

void Memory::memoryShuffle()
{    
    m_memorySegments.erase(std::remove_if(m_memorySegments.begin(), m_memorySegments.end(), [](const Segment &segment){
        return segment.m_isHole;
    }), m_memorySegments.end());

    for(int i = 0; i < m_memorySegments.count(); ++i)
    {
        if(i == 0)
        {
            m_memorySegments[i].m_base = 1;
        }
        else
        {
            m_memorySegments[i].m_base = m_memorySegments[i -1].m_base + m_memorySegments[i -1].m_limit;
        }
    }
    uint32_t end = m_memorySegments.back().m_base + m_memorySegments.back().m_limit;

    if (end <= m_memorySize)
    {
        m_memorySegments.push_back(Segment(0, 0, m_memorySize - end +1, end, true));
    }
    m_memoryModel.update();
}



uint32_t Memory::memorySize() const
{
    return m_memorySize;
}


void Memory::resizeMemory(quint32 newMemorySize)
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

    emit memorySizeChanged();
}

void Memory::resetMemory(quint32 memorySize)
{
    if(memorySize > 0)
    {
        m_memorySize = memorySize;
        emit memorySizeChanged();
    }
    m_lastPid = 1;
    m_memorySegments.clear();
    m_memorySegments.push_back(Segment(1, m_lastPid++, m_memorySize, 1, false));
    m_memorySegments.back().m_color = "lightBlue";
    m_memoryModel.update();
}
