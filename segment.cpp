#include "segment.h"


Segment::Segment(uint32_t sid, uint32_t pid, uint32_t limit, uint32_t base, bool isHole, const QString &name):
    m_sid(sid), m_limit(limit), m_base(base), m_isHole(isHole), m_pid(pid)
{
    m_name = name.isEmpty() ? ("S" + QString::number(sid)) : name;
}

bool Segment::operator==(const Segment &otherSegment)
{
    return m_pid == otherSegment.m_pid && m_sid == otherSegment.m_sid;
}
