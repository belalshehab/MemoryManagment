#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include "segment.h"

#include <QAbstractListModel>
#include <QColor>

class SegmentTableModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    Q_PROPERTY(quint32 lastPid READ lastPid WRITE setLastPid NOTIFY lastPidChanged)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    enum RoleNames {
        SidRole = Qt::UserRole,
        PidRole,
        LimitRole,
        BaseRole,
        IsHoleRole,
        NameRole,
    };

public:
    explicit SegmentTableModel(QObject *parent = nullptr);

    Q_INVOKABLE void append(quint32 limit, const QString &name);


    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();

    bool isEmpty() const;

public:
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    quint32 lastPid() const;
    void setLastPid(const quint32 &lastPid);

    Q_INVOKABLE QList<Segment> *segmentList();

    QColor color() const;
    void setColor(const QColor &color);

signals:
    void isEmptyChanged();
    void lastPidChanged();
    void colorChanged();
protected:
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QList<Segment> m_segmentList;
    quint32 m_lastSid;
    quint32 m_lastPid;
    QHash <int, QByteArray> m_roleNames;

    QColor m_color;
};

#endif // PROCESSMODEL_H
