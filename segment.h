#ifndef SEGMENT_H
#define SEGMENT_H

#include <QString>
#include <QObject>

#include <iostream>

struct Segment
{
private:
    Q_GADGET
    Q_PROPERTY(uint32_t sid MEMBER m_sid)
    Q_PROPERTY(uint32_t pid MEMBER m_pid)
    Q_PROPERTY(uint32_t limit MEMBER m_limit)
    Q_PROPERTY(uint32_t base MEMBER m_base)
    Q_PROPERTY(bool isHole MEMBER m_isHole)
    Q_PROPERTY( QString name MEMBER m_name)


public:
    Segment(uint32_t sid, uint32_t pid, uint32_t limit, uint32_t base = 0, bool isHole = false, const QString &name = "");

    bool operator==(const Segment &otherSegment);

    uint32_t m_sid;
    uint32_t m_pid;
    uint32_t m_limit;
    uint32_t m_base;
    bool m_isHole;

    QString m_name;

};

#endif // SEGMENT_H
