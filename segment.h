#ifndef SEGMENT_H
#define SEGMENT_H

#include <QString>
#include <QObject>
#include <QColor>

#include <iostream>

struct Segment
{
private:
    Q_GADGET

    Q_PROPERTY(quint32 sid MEMBER m_sid)
    Q_PROPERTY(quint32 pid MEMBER m_pid)
    Q_PROPERTY(quint32 limit MEMBER m_limit)
    Q_PROPERTY(quint32 base MEMBER m_base)
    Q_PROPERTY(bool isHole MEMBER m_isHole)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(QColor color MEMBER m_color)


public:
    Segment(quint32 sid, quint32 pid, quint32 limit, quint32 base = 0, bool isHole = false, const QString &name = "");

    bool operator==(const Segment &otherSegment);

    quint32 m_sid;
    quint32 m_pid;
    quint32 m_limit;
    quint32 m_base;
    bool m_isHole;

    QString m_name;

    QColor m_color;
};

#endif // SEGMENT_H
