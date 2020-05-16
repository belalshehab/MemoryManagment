#include "segment.h"
#include <QDebug>


Segment::Segment(quint32 sid, quint32 pid, quint32 limit, quint32 base, bool isHole, const QString &name):
    m_sid(sid), m_pid(pid), m_limit(limit), m_base(base), m_isHole(isHole)
{
    m_name = name.isEmpty() ? QString("P%0-S%1").arg(m_pid).arg(m_sid) : name;
}

bool Segment::operator==(const Segment &otherSegment)
{
    return m_pid == otherSegment.m_pid && m_sid == otherSegment.m_sid;
}
