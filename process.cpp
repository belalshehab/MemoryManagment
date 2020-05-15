#include "process.h"
#include <list>
#include <algorithm>

Process::Process(long long pid, const QString &name):
    m_pid(pid), m_name(name)
{   
}

void Process::addSegment(const Segment &segment)
{
    m_segmentTable.append(segment);
}

bool Process::removeSegment(const Segment &segment)
{
    return  m_segmentTable.removeOne(segment);
}

void Process::sortTheSegmentTableOnLimit()
{
    std::sort(m_segmentTable.begin(), m_segmentTable.end(), [](const Segment &segment1, const Segment &segment2){
        return segment1.m_limit > segment2.m_limit;
    });
}

void Process::sortTheSegmentTableOnBase()
{
    std::sort(m_segmentTable.begin(), m_segmentTable.end(), [](const Segment &segment1, const Segment &segment2){
        return segment1.m_base < segment2.m_base;
    });
}

QList<Segment> &Process::segmentTable()
{
    return m_segmentTable;
}


QList<Segment> Process::segmentTable() const
{
    return m_segmentTable;
}

int Process::sizeOfSegmentTable() const
{
    return m_segmentTable.count();
}

void Process::setSegmentTable(const QList<Segment> &segmentTable)
{
    m_segmentTable = segmentTable;
}
