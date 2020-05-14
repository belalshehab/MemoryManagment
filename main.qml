import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1200
    height: 720

    color: "#333333"
    title: "Memory managment"

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
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 30

        model: ListModel {
            ListElement {
                segmentPid: 1
                name: "Segment 1"
                limit: 1000
                color: "blue"
            }

            ListElement {
                segmentPid: 0
                name: ""
                limit: 1200
                color: "transparent"
            }
            ListElement {
                segmentPid: 3
                name: "Segment 2"
                limit: 1500
                color: "red"
            }

            ListElement {
                segmentPid: 1
                name: "Segment 2"
                limit: 850
                color: "blue"
            }
            ListElement {
                segmentPid: 0
                name: ""
                limit: 500
                color: "transparent"
            }
            ListElement {
                segmentPid: 3
                name: "Segment 1"
                limit: 1830
                color: "red"
            }
            ListElement {
                segmentPid: 0
                name: ""
                limit: 2000
                color: "transparent"
            }
        }
    }

    ProcessSegments {
        id: processSegments
        x: 132
        y: 144
        width: 576
        height: 335

        model: ListModel {
            ListElement {
                sid: 1
                name: "Segment 1"
                limit: 100
            }

            ListElement {
                sid: 2
                name: "Segment 2"
                limit: 200
            }

            ListElement {
                sid: 3
                name: "Segment 3"
                limit: 150
            }

            ListElement {
                sid: 4
                name: "Segment 4"
                limit: 400
            }
        }

        onAddProcessClicked: {
            console.log("onAddProcessClicked")
            processColor = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        }
    }



}

/*##^##
Designer {
    D{i:8;anchors_height:335;anchors_width:576;anchors_x:132;anchors_y:144}
}
##^##*/
