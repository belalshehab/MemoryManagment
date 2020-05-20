import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import MemoryManagment 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1200
    height: 720

    color: "#333333"
    title: "Memory managment"

//    function updateSegmentTable()
//    {
//        if(memoryView.currentPid == 0)
//        {
//            segmentTable.visible = false
//        }
//        else
//        {
//            segmentTable.model.clear();
//            for()
//            segmentTable.model.append()
//        }
//    }

    AllocationMethods {
        id: allocationMethods

        height: 50
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
    }


    MemoryView {
        id: memoryView

        anchors.top: allocationMethods.bottom
        anchors.topMargin: 30
        anchors.bottom: rowLayout.top
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 30

//        onCurrentPidChanged: updateSegmentTable()
        model: memory.memoryModel
    }


    SwipeView {
        id: swipeView
        width: 600
        height: 272
        anchors.top: allocationMethods.bottom
        anchors.topMargin: 30
        interactive: false
        clip: true
        anchors.left: parent.left
        anchors.leftMargin: 176

        MemorySizeInitPage{
            id: memorySizeInitPage

            onNextClicked: {
                memory.resetMemory(memorySize)
                swipeView.currentIndex += 1
            }
        }

        MemoryInitPage{
            id: memoryInitPage
            memorySize: memory.memorySize

            onAddHoleFaild:
            {
                warningPopup.message = qsTr("Can't add this Hole try reducing it's limit or change it's base")
                warningPopup.open()
            }
            onFinishedClicked: {
                swipeView.currentIndex += 1
                memory.segmentTableModel.lastPid = memory.lastPid
            }
        }

        ProcessSegments {
            id: processSegments
            width: 576
            height: 335

            maximumSegmentLimit: memory.memorySize
            model: memory.segmentTableModel



            onAddProcessClicked: {
                model.color = processColor
                if(memory.addProcess(allocationMethods.algorithm))
                {
                    processColor = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                    processSegments.model.clear();
                    processSegments.model.lastPid = memory.lastPid
                }
                else
                {
                    warningPopup.message = qsTr("Can't add this process try to remove some processes first")
                    warningPopup.open();
                }
            }
        }
    }

    WarningPopup
    {
        id: warningPopup
    }

    RowLayout {
        id: rowLayout
        anchors.left: memoryView.left
        anchors.right: memoryView.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        Button {
            id: resetButton
            text: qsTr("Reset Memory")
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                swipeView.currentIndex = 0
            }
        }

        Button {
            id: shuffleButton
            text: qsTr("Memory Shuffle")
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillWidth: true

            onClicked: memory.memoryShuffle()
        }
    }

    SegmentTable {
        id: segmentTable

        anchors.right: swipeView.right
        anchors.left: swipeView.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        height: 260

        currentPid: memoryView.currentPid

        visible: memoryView.currentPid === 0 ? false : true
        model:  memory.memoryModel
    }
}

/*##^##
Designer {
    D{i:11;anchors_width:600;anchors_x:157}
}
##^##*/
