import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

GrayRectangle {
    id: root
    implicitHeight: 350
    implicitWidth: 600

    property alias model: segmentsView.model

    property int currentPid: 0


    Label {
        id: label
        color: "#cbcbcb"
        text: currentPid === 0 ? qsTr("Segment table") : qsTr("Segment table of process " + currentPid)
        font.weight: Font.Bold
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 25
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
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
    Item {
        id: titles
        height: 30
        anchors.top: deepLine.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        RowLayout{
            id: rowLayout
            anchors.fill: parent

            Label {
                id: sidLabel
                Layout.maximumWidth: 100
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: true

                font.pixelSize: 15
                color: "#fffffff0"
                text: "SID"
            }

            Rectangle{
                Layout.preferredWidth: 1
                Layout.preferredHeight: -1
                Layout.bottomMargin: 5
                Layout.topMargin: 5
                Layout.fillHeight: true
                Layout.maximumWidth: 1
                Layout.minimumWidth: 1
                color: "#BFBFBF"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                opacity: 0.5
            }

            Label {
                id: limitLabel
                Layout.maximumWidth: 200
                Layout.minimumWidth: 150
                Layout.preferredWidth: 150
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                font.pixelSize: 15
                color: "#fffffff0"
                text: "Limit"
            }

            Rectangle{
                Layout.preferredWidth: 1
                Layout.preferredHeight: -1
                Layout.bottomMargin: 5
                Layout.topMargin: 5
                Layout.fillHeight: true
                Layout.maximumWidth: 1
                Layout.minimumWidth: 1
                color: "#BFBFBF"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                opacity: 0.5
            }

            Label {
                id: baseLabel
                Layout.maximumWidth: 200
                Layout.minimumWidth: 150
                Layout.preferredWidth: 150
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                font.pixelSize: 15
                color: "#fffffff0"
                text: "Base"
            }

            Rectangle{
                Layout.preferredWidth: 1
                Layout.preferredHeight: -1
                Layout.bottomMargin: 5
                Layout.topMargin: 5
                Layout.fillHeight: true
                Layout.maximumWidth: 1
                Layout.minimumWidth: 1
                color: "#BFBFBF"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                opacity: 0.5
            }

            Label {
                id: nameLabel
                Layout.maximumWidth: 300
                Layout.minimumWidth: 200
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true


                fontSizeMode: Text.HorizontalFit
                wrapMode: Text.NoWrap
                clip: true
                font.pixelSize: 15

                color: "#fffffff0"
                text: "Name"
            }
        }
//        DeepLine{
//            anchors.bottom: parent.bottom
//            width: parent.width
//        }
    }

    ListView {
        id: segmentsView
        anchors.topMargin: 0
        anchors.top: titles.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20

        clip: true
//        spacing: 5

        ScrollBar.vertical: ScrollBar{ width: 6}
        delegate: segmentDelegate
    }

    Component{
        id: segmentDelegate

        SegmentDelegate {
            width: segmentsView.width
            sid: model.sid
            limit: model.limit
            name: model.name
            base: model.base
            isDeletable: false

            visible: currentPid === 0 ? false : model.pid === currentPid ? true : false
            height: visible ? 30 : 0
        }
    }

}
