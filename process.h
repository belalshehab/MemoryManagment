#ifndef PROCCESS_H
#define PROCCESS_H

#include "segment.h"

#include <QString>
#include <QList>

#include <iostream>

class Proccess
{
public:
    Proccess(long long m_pid, const QString &m_name = "");

    void addSegment(const Segment &newSegment);
    bool removeSegment(long long sid);
private:
    long long m_pid;
    QString m_name;
    QList<Segment> m_segmentTable;
};

#endif // PROCCESS_H
