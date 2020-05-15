#include <iostream>
#include "memory.h"

int main()
{
    Memory memory(10000);


    //    std::cout << memory.findHole(800, Memory::AllocationMethod::FIRST_FIT) << std::endl;

    //    std::cout << memory.findHole(1800, Memory::AllocationMethod::FIRST_FIT) << std::endl;

    //    std::cout << memory.findHole(800, Memory::AllocationMethod::BEST_FIT) << std::endl;

    //    std::cout << memory.findHole(1800, Memory::AllocationMethod::BEST_FIT) << std::endl;

    //    std::cout << memory.findHole(6000, Memory::AllocationMethod::BEST_FIT) << std::endl;


    //    Segment s(1, 3, 800);

    //    auto segmentPair = memory.addProcessSegment(s, Memory::AllocationMethod::BEST_FIT);
    //    std::cout << segmentPair.first << ", " << segmentPair.second.m_base << std::endl;


    //    s = Segment(2, 3, 1800);

    //    segmentPair = memory.addProcessSegment(s, Memory::AllocationMethod::FIRST_FIT);
    //    std::cout << segmentPair.first << ", " << segmentPair.second.m_base << std::endl;


    //    s = Segment(3, 3, 800);

    //    segmentPair = memory.addProcessSegment(s, Memory::AllocationMethod::BEST_FIT);
    //    std::cout << segmentPair.first << ", " << segmentPair.second.m_base << std::endl;

    //    s = Segment(4, 3, 1800);

    //    segmentPair = memory.addProcessSegment(s, Memory::AllocationMethod::BEST_FIT);
    //    std::cout << segmentPair.first << ", " << segmentPair.second.m_base << std::endl;

    //    s = Segment(5, 3, 6000);

    //    segmentPair = memory.addProcessSegment(s, Memory::AllocationMethod::BEST_FIT);
    //    std::cout << segmentPair.first << ", " << segmentPair.second.m_base << std::endl;

    //    std::cout << memory.removeSegment(Segment(2, 1, 0)) << std::endl;
    //    std::cout << memory.removeSegment(Segment(5, 1, 0)) << std::endl;

    //    std::cout << memory.removeSegment(Segment(1, 4, 0)) << std::endl;

    //    memory.mergeHoles();

    //    std::cout << memory.removeSegment(Segment(1, 4, 0)) << std::endl;

    Process p1(1);
    p1.addSegment(Segment(1, 5, 1800));
    p1.addSegment(Segment(2, 5, 1000));
    p1.addSegment(Segment(3, 5, 2000));

    Process p2(2);
    p2.addSegment(Segment(1, 6, 900));
    p2.addSegment(Segment(2, 6, 900));

    bool success = memory.addProcess(p1, Memory::AllocationMethod::FIRST_FIT);
    std::cout << success << std::endl;
    success = memory.addProcess(p2, Memory::AllocationMethod::FIRST_FIT);

    return 0;
}

