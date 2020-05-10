#include "proccess.h"

Proccess::Proccess(long long pid, const QString &name):
    m_pid(pid), m_name(name)
{   
}

void Proccess::addSegment(const Segment &newSegment)
{
    m_segmentTable.append(newSegment);
}

bool Proccess::removeSegment(long long sid)
{
    m_segmentTable.removeOne()
}
