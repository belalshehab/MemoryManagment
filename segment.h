#ifndef SEGMENT_H
#define SEGMENT_H

#include <QString>
#include <QObject>

#include <iostream>

struct Segment
{
    Segment(uint32_t sid, uint32_t pid, uint32_t limit, uint32_t base = 0, bool isHole = false, const QString &name = "");

    bool operator==(const Segment &otherSegment);

    uint32_t m_sid;
    uint32_t m_limit;  
    uint32_t m_base;
    bool m_isHole;

    QString m_name;
    uint32_t m_pid;
};

#endif // SEGMENT_H
