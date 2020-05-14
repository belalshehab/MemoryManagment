#ifndef PROCCESS_H
#define PROCCESS_H

#include "segment.h"

#include <QString>
#include <QList>
#include <QColor>

#include <iostream>

class Process
{
public:

    Process(long long pid, const QString &name = "");


    void addSegment(const Segment &segment);
    bool removeSegment(const Segment &segment);

    void sortTheSegmentTableOnLimit();

    void sortTheSegmentTableOnBase();

    QList<Segment> segmentTable() const;
    void setSegmentTable(const QList<Segment> &segmentTable);

    int sizeOfSegmentTable() const;




private:
    long long m_pid;
    QString m_name;
    QList<Segment> m_segmentTable;
    QColor m_color;
};

#endif // PROCCESS_H
