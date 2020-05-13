#include "memory.h"


Memory::Memory(uint32_t size): m_size(size)
{
    m_segments.push_back(Segment(1, m_size, 0, false));

}

Segment Memory::addSegment(const Segment &segment, Memory::AllocationMethod allocationMethod)
{
    int index_new_seg = findHole(segment.m_limit , allocationMethod);
    if ( index_new_seg  == -1)

    {
         return Segment(0,0,-1);
    }

    else {

      //insert new segment in list of segments
     int totel_num_segments = m_segments.size() +1;

     for ( int i = totel_num_segments  ; i >= index_new_seg +1 ; i--)
        m_segments[i] = m_segments[i+1];

     m_segments[index_new_seg ] = segment;

     //update the base of new segment
     m_segments[index_new_seg ].m_base =   m_segments[index_new_seg+1].m_base ;
     m_segments[index_new_seg ].m_isHole = ! m_segments[index_new_seg+1].m_isHole;

     //update the base and limit of new hole
     m_segments[index_new_seg+1].m_base  =  m_segments[index_new_seg].m_base + m_segments[index_new_seg ].m_limit + 1 ;
     m_segments[index_new_seg+1].m_limit =  m_segments[index_new_seg].m_limit -  m_segments[index_new_seg ].m_limit ;

    return Segment(0 , m_segments[index_new_seg ].m_limit ,m_segments[index_new_seg ].m_base,m_segments[index_new_seg ].m_isHole);//what do you want in id
     }
}


int Memory::findHole(uint32_t size, Memory::AllocationMethod allocationMethod)
{
    uint32_t min = uint32_t(m_segments.size());
    int min_index = -1 ;

    switch (allocationMethod) {
    case 1 :

    for (int i = 0; i < m_segments.size(); i++) {
        if (m_segments[i].m_isHole && m_segments[i].m_limit >= size )
           {
                min_index = i ;
                break ;
           }
    }
        break;

     case 2 :
        for (int i = 0; i < m_segments.size(); i++) {
            if (m_segments[i].m_isHole && m_segments[i].m_limit >= size )
            {
                if ( min > m_segments[i].m_limit )
                    min = m_segments[i].m_limit;
                    min_index = i ;
                    break;
            }
                    }
        break;

      case 3 :
        break;

    }
    return min_index;
}


//bool Memory::removeSegment(Segment &segment)
//{
//    if ( !segment.m_isHole )
//    {
//        segment.m_isHole = true ;
//        return true ;
//    }
//    else {
//        return false;
//    }
//}

bool Memory::removeSegment(const Segment &segment){

    for (int i = 0; i<= m_segments.size();i++){
        if (m_segments[i] == segment && !segment.m_isHole )
        {
            m_segments[i].m_isHole = true ;
            return true ;
        }
    }
    return false ;
}



void Memory::mergeHoles()
{
    //replace this with your implementation

    for (int i = 0; i<= m_segments.size();i++){
        if (m_segments[i].m_isHole)
        {
            if( m_segments[i+1].m_isHole)
            {
             m_segments[i].m_limit = m_segments[i].m_limit + m_segments[i+1].m_limit;
             m_segments[i+1].m_limit = 0;
             Memory::mergeHoles();
            }

            }

        }

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
