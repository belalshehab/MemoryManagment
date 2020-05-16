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

     explicit Process(quint32 pid, const QString &name = "");


    void addSegment(const Segment &segment);
    bool removeSegment(const Segment &segment);

    void sortTheSegmentTableOnLimit();
    void sortTheSegmentTableOnBase();

    QList<Segment> &segmentTable();
    QList<Segment> segmentTable() const;
    void setSegmentTable(const QList<Segment> &segmentTable);

    int sizeOfSegmentTable() const;

    QColor color() const;
    void setColor(const QColor &color);

    quint32 pid() const;

private:
    quint32 m_pid;
    QString m_name;
    QList<Segment> m_segmentTable;
    QColor m_color;
};

#endif // PROCCESS_H
