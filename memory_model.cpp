#include "memory_model.h"

MemoryModel::MemoryModel(QObject *parent): QAbstractListModel(parent)
{
    m_roleNames[SidRole] = "sid";
    m_roleNames[PidRole] = "pid";
    m_roleNames[LimitRole] = "limit";
    m_roleNames[BaseRole] = "base";
    m_roleNames[IsHoleRole] = "isHole";
    m_roleNames[NameRole] = "name";
    m_roleNames[ColorRole] = "color";
}


QVariant MemoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case SidRole:
        return m_memorySegments[index.row()].m_sid;
    case PidRole:
        return m_memorySegments[index.row()].m_pid;
    case LimitRole:
        return m_memorySegments[index.row()].m_limit;
    case BaseRole:
        return m_memorySegments[index.row()].m_base;
    case IsHoleRole:
        return m_memorySegments[index.row()].m_isHole;
    case NameRole:
        return m_memorySegments[index.row()].m_name;
    case ColorRole:
        return m_memorySegments[index.row()].m_color;
    }

    return QVariant();
}

void MemoryModel::update()
{
    beginResetModel();
    endResetModel();
}

void MemoryModel::insert(int index, const Segment &segment)
{
    if(index < 0 || index > m_memorySegments.count())
        return;

    beginInsertRows(QModelIndex(), index, index);
    m_memorySegments.insert(index, segment);
    emit endInsertRows();
}

int MemoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_memorySegments.count();
}

QHash<int, QByteArray> MemoryModel::roleNames() const
{
    return m_roleNames;
}

QList<Segment> *MemoryModel::segments()
{
    return &m_memorySegments;
}
