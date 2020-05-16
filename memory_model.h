#ifndef MEMORY_H
#define MEMORY_H

#include "segment.h"

#include <QAbstractListModel>
#include <QList>

#include <iostream>

class MemoryModel: public QAbstractListModel
{
    Q_OBJECT

    enum RoleNames {
        SidRole = Qt::UserRole,
        PidRole,
        LimitRole,
        BaseRole,
        IsHoleRole,
        NameRole,
        ColorRole,
    };

public:
    Q_ENUMS(AllocationMethod)
    enum AllocationMethod{
        FIRST_FIT = 1, BEST_FIT, WORST_FIT
    };
public:
    explicit MemoryModel(QObject *parent = nullptr);

    void update();

    void insert(int index, const Segment &segment);

    // GUI basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<Segment> *segments();

private:
protected:
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QList<Segment> m_memorySegments;
    QHash <int, QByteArray> m_roleNames;
};

#endif // MEMORY_H
