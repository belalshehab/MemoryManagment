#include "segment_table_model.h"


#include <QtDebug>

SegmentTableModel::SegmentTableModel(QObject *parent)
    : QAbstractListModel(parent), m_lastSid(0), m_lastPid(1)
{
    m_roleNames[SidRole] = "sid";
    m_roleNames[PidRole] = "pid";
    m_roleNames[LimitRole] = "limit";
    m_roleNames[BaseRole] = "base";
    m_roleNames[IsHoleRole] = "isHole";
    m_roleNames[NameRole] = "name";
}

void SegmentTableModel::append(quint32 limit, const QString &name)
{
    emit beginInsertRows(QModelIndex(), m_segmentList.count(), m_segmentList.count());
    m_segmentList.append(Segment(++m_lastSid, m_lastPid, limit, 0, false, name));
    emit endInsertRows();

    if(m_segmentList.count() == 1)
    {
        emit isEmptyChanged();
    }
}

void SegmentTableModel::remove(int index)
{
    if(index < 0 || index >= m_segmentList.count())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_segmentList.removeAt(index);
    endRemoveRows();

    if(m_segmentList.isEmpty())
    {
        m_lastSid = 0;
        emit isEmptyChanged();
    }
}

void SegmentTableModel::clear()
{
    beginResetModel();
    m_segmentList.clear();
    endResetModel();
    emit isEmptyChanged();

    m_lastSid = 0;
}

bool SegmentTableModel::isEmpty() const
{
    return m_segmentList.isEmpty();
}


int SegmentTableModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_segmentList.count();
}

QVariant SegmentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case SidRole:
        return m_segmentList[index.row()].m_sid;
    case PidRole:
        return m_segmentList[index.row()].m_pid;
    case LimitRole:
        return m_segmentList[index.row()].m_limit;
    case BaseRole:
        return m_segmentList[index.row()].m_base;
    case IsHoleRole:
        return m_segmentList[index.row()].m_isHole;
    case NameRole:
        return m_segmentList[index.row()].m_name;
    }

    return QVariant();
}

QHash<int, QByteArray> SegmentTableModel::roleNames() const
{
    return m_roleNames;
}

QColor SegmentTableModel::color() const
{
    return m_color;
}

void SegmentTableModel::setColor(const QColor &color)
{
    if(m_color == color)
    {
        return;
    }
    m_color = color;
    emit colorChanged();
}

QList<Segment> *SegmentTableModel::segmentList()
{
    return &m_segmentList;
}

quint32 SegmentTableModel::lastPid() const
{
    return m_lastPid;
}

void SegmentTableModel::setLastPid(const quint32 &lastPid)
{
    if(m_lastPid == lastPid)
    {
        return;
    }

    m_lastPid = lastPid;
    emit lastPidChanged();
}
