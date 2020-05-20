import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

GrayRectangle
{
    id:root
    
    implicitWidth: 300
    implicitHeight: 600

    property alias model: listView.model

    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        
        text: qsTr("Memory")
        anchors.top: parent.top
        anchors.topMargin: 10
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Bold
        font.pixelSize: 25
        
        color: "#bababa"
    }
    
    DeepLine {
        id: deepLine
        anchors.top: label.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    ListView {
        id: listView
        anchors.top: deepLine.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.margins: 20
        
        clip: true
        spacing: 20

        ScrollBar.vertical: ScrollBar{ width: 6}
        delegate: memorySegmentDelegate

        add: Transition {
            NumberAnimation {
                properties: "x"; from: segmentsView.width;
                duration: 150; easing.type: Easing.InCirc
            }
            NumberAnimation { properties: "height"; from: 0;
                duration: 200; easing.type: Easing.InCirc
            }
        }
        remove: Transition {
            NumberAnimation {
                properties: "x"; to: segmentsView.width;
                duration: 150; easing.type: Easing.OutCubic
            }
        }
        removeDisplaced: Transition {
            SequentialAnimation {
                PauseAnimation { duration: 150 }
                NumberAnimation { properties: "y"; duration: 75
                }
            }
        }
    }

    Component{
        id: memorySegmentDelegate

        MemorySegmentDelegate {
            width: listView.width - 10
            segmentPid: model.pid
            limit: model.limit
            base: model.base
            name: model.isHole ? "" : model.name
            color: model.isHole ? "#09ffffff" : model.color

            deleteButtonVisble: segmentPid === 0 ? false :
                                    listView.currentItem.segmentPid === segmentPid ? listView.currentItem.showDelete : false
            onDeleteClicked:
            {
                memory.removeProcess(segmentPid)
            }


            onSegmentClicked:
            {
                if(listView.currentIndex === index)
                {
                    showDelete = !showDelete
                }
                else
                {
                    showDelete = false
                    listView.currentIndex = index
                    showDelete = !showDelete
                }

            }
        }
    }
}
