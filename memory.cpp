#include "memory.h"


Memory::Memory(uint32_t size): m_memorySize(size)
{
    //    m_segments.push_back(Segment(1, m_memorySize, 0, false));

    m_segments.push_back(Segment(0, 0, 1400, 0, true));
    m_segments.push_back(Segment(1, 1, 1000, 1401, false));
    m_segments.push_back(Segment(0, 0, 800, 2401, true));
    m_segments.push_back(Segment(2, 1, 1100, 3201, false));
    m_segments.push_back(Segment(1, 2, 400, 4301, false));
    m_segments.push_back(Segment(0, 0, 4800, 4701, true));
    m_segments.push_back(Segment(1, 4, 500, 9501, false));
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
        m_segments.insert(index_new_seg, segment);

        //update the base of new segment
        m_segments[index_new_seg ].m_base =   m_segments[index_new_seg+1].m_base ;

        //update the base and limit of new hole
        m_segments[index_new_seg+1].m_base  =  m_segments[index_new_seg].m_base + m_segments[index_new_seg ].m_limit;
        m_segments[index_new_seg+1].m_limit =  m_segments[index_new_seg +1].m_limit -  m_segments[index_new_seg].m_limit;

        if(m_segments[index_new_seg +1].m_limit < 1)
        {
            m_segments.removeAt(index_new_seg +1);
        }

        return {true, m_segments[index_new_seg]};
    }
}


int Memory::findHole(uint32_t limitOfSegment, Memory::AllocationMethod allocationMethod)
{
    uint32_t min = m_memorySize;

    int min_index = -1 ;

    switch (allocationMethod) {
    case AllocationMethod::FIRST_FIT:

        for (int i = 0; i < m_segments.size(); ++i) {
            if (m_segments[i].m_isHole && m_segments[i].m_limit >= limitOfSegment )
            {
                min_index = i ;
                break ;
            }
        }
        break;

    case AllocationMethod::BEST_FIT:
        for (int i = 0; i < m_segments.size(); i++) {
            if (m_segments[i].m_isHole && m_segments[i].m_limit >= limitOfSegment )
            {
                if ( min > m_segments[i].m_limit )
                {
                    min = m_segments[i].m_limit;
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

    int index = m_segments.indexOf(segment);
    if(index < 0)
    {
        return false;
    }

    else
    {
        m_segments[index].m_isHole = true;
        return true ;
    }
}


void Memory::mergeHoles()
{   
    for (int i = 0; i < m_segments.size() -1; ){
        if (m_segments[i].m_isHole)
        {
            if( m_segments[i+1].m_isHole)
            {
                m_segments[i].m_limit = m_segments[i].m_limit + m_segments[i+1].m_limit;
                m_segments.removeAt(i +1);
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


bool Memory::addProcess(Process process, Memory::AllocationMethod allocationMethode)
{
    bool success = true;
    int breakIndex = 0;

    process.sortTheSegmentTableOnLimit();
    QList<Segment> &segmentTable = process.segmentTable();

    for(int i = 0; i < segmentTable.size(); ++i)
    {
        auto addedSegmentPair = addProcessSegment(segmentTable[i], allocationMethode);
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
        process.setSegmentTable(segmentTable);
        m_processTable.push_back(process);
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


void Memory::removeProcess(Process process)
{
    QList<Segment> &segmentTable = process.segmentTable();

    for(const Segment &segment: segmentTable)
    {
        removeSegment(segment);
    }

    mergeHoles();
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
