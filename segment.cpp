#include "segment.h"


Segment::Segment(long long sid, uint32_t base, uint32_t limit, const QString &name):
    sid(sid), base(base), limit(limit), name{name}
{
}
