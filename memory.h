#ifndef KERNEL_H
#define KERNEL_H

#include "segment_table_model.h"
#include "memory_model.h"

#include <QObject>

class Memory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SegmentTableModel* segmentTableModel READ segmentTableModel NOTIFY segmentTableModelChanged)
    Q_PROPERTY(MemoryModel* memoryModel READ memoryModel NOTIFY memoryModelChanged)

    Q_PROPERTY(quint32 lastPid READ lastPid WRITE setLastPid NOTIFY lastPidChanged)
    Q_PROPERTY(quint32 memorySize READ memorySize WRITE resetMemory NOTIFY memorySizeChanged)

public:
    Q_ENUMS(AllocationMethod)
    enum AllocationMethod{
        FIRST_FIT = 1, BEST_FIT, WORST_FIT
    };
public:
    explicit Memory(QObject *parent = nullptr);

    /**
     * @brief addProcessSegment:
     * 1. search with findHole
     * 2. insert the segment starting from the hole address
     * 3. resize the subsequent hole to be with limit = oldHoleLimit - insertedSegnmentLimit
     * @param segment the segment to be inserted
     * @param allocationMethod the AllocationMethod to be used for selecting which hole
     * @return return true on success, or false if there is no big enough hole
     */
    std::pair<bool, Segment> addProcessSegment(const Segment &segment, AllocationMethod allocationMethod);

    /**
     * @brief findHole return the index of the suitable hole
     * @param limitOfSegment the size of the segment to be allocated
     * @param allocationMethod the AllocationMethod to be used for selecting which hole
     * @return the index of the suitable hole, or -1 if there is no big enough hole
     */
    int findHole(quint32 limitOfSegment, AllocationMethod allocationMethod);


    /**
     * @brief removeSegment:
     * 1. search for the segment to be removed
     * 2. make the segment to be hole
     * 3. merge any neighbor holes
     * @param segment the segment to be removed
     * @return return true if the segment can be found, and false otherwise
     */
    bool removeSegment(const Segment &segment);


    /**
     * @brief iterate on the segments table and merge any consecutive holes by:
     * 1. removing the next hole
     * 2. resize the current hole to be with limit = limit + theRemovedHoleSize
     */
    void mergeHoles();


    /**
     * @brief addProcess:
     * 1. sort the process segmentTable in descending order according to the segment limit
     * 2. run addSegment on each segment
     * 3. if any segment faild to be inserted, stop and remove all the inserted segments
     * 4. add the process to the m_processTable
     * @param process the process to be allocated in memory
     * @param allocationMethod the AllocationMethod to be used for selecting which hole
     * @return true if all segments has ben inserted successfully, false otherwise
     *
     */
    Q_INVOKABLE bool addProcess(AllocationMethod allocationMethod);

    /**
     * @brief removeProcess:
     * 1. remove all sgements of the process
     * 2. call mergeHoles
     * 3. remove the process from m_processTable
     * @param process the process to be removed
     * @return true on success, and false if the process can't be founded
     */
    Q_INVOKABLE void removeProcess(quint32 pid);

    /**
     * @brief addHole:
     * 1. search for the segment to cut
     * 2. creat new process segment with the same base as the previous segment but with limit = hole base - process segment hole
     * 3. insert the hole
     * 4. if the hole  insert new process segment
     * @param hole the hole to be inserted
     * @attention this function is for the memory initialization only
     * @return true on success, and false otherwise
     */
    Q_INVOKABLE bool addHole(quint32 limit, quint32 base);

    /**
     * @brief memoryShuffle place all free locations togther into one large hole
     */
    Q_INVOKABLE void memoryShuffle();

    uint32_t memorySize() const;
    Q_INVOKABLE void resizeMemory(quint32 newMemorySize);
    Q_INVOKABLE void resetMemory(quint32 memorySize = 0);


    SegmentTableModel *segmentTableModel();
    MemoryModel *memoryModel();


    quint32 lastPid() const;
    void setLastPid(const quint32 &lastPid);


signals:
    void segmentTableModelChanged();
    void memoryModelChanged();
    void lastPidChanged();
    void memorySizeChanged();
public slots:

private:
    SegmentTableModel m_segmentTableModel;
    MemoryModel m_memoryModel;

    QList<Segment> &m_memorySegments;

    //memory size in bytes
    quint32 m_memorySize;

    quint32 m_lastPid;
};

#endif // KERNEL_H
