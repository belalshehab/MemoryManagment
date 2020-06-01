import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    implicitWidth: 100
    implicitHeight: 100


    property int segmentPid
    property int limit
    property int base
    property real heightScale
    property alias name: segmentNameLabel.text
    property alias color: rec.color

    property bool showDelete: false
    property alias deleteButtonVisble: deleteButton.visible
    signal segmentClicked
    signal deleteClicked

    height: (limit / heightScale) < 40 ? 40 : limit / heightScale

    Rectangle{
        id: rec
        anchors.leftMargin: 100
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(root.segmentPid > 0)
                {
                    segmentClicked()
                }
            }
        }


        Label {
            id: segmentNameLabel
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Segment Name")

            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

    }
    RoundButton{
        id: deleteButton

        anchors.verticalCenter: parent.verticalCenter

        radius: 60


        text: "X"
        anchors.left: parent.left
        anchors.leftMargin: 0

        display: AbstractButton.TextOnly
        font.weight: Font.Bold
        font.pixelSize: 10
        font.family: "ROBOTO"

        visible: false

        onClicked:
        {
            deleteClicked()
        }
    }

    Label {
        id: segmentBaseLabel

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.rightMargin: 5
        anchors.right: rec.left


        text: root.base

        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
    }

    Label {
        id: segmentEndLabel

        anchors.bottom: parent.bottom
        anchors.left: parent.left

        anchors.rightMargin: 5
        anchors.right: rec.left

        text: root.limit + root.base -1

        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
    }

}


