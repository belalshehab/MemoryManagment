import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    implicitWidth: 100
    implicitHeight: 100


    property int segmentPid
    property int limit
    property alias name: segmentNameLabel.text
    property alias color: rec.color

    signal deleteClicked

    //    height: limit /10

    Rectangle{
        id: rec
        anchors.leftMargin: 100
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(root.segmentPid > 0)
                {
                    deleteButton.visible = !deleteButton.visible
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
            console.log("deleteClicked")
            deleteClicked()
        }
    }

    Label {
        id: segmentLimitLabel

        anchors.bottom: parent.bottom
        anchors.left: parent.left


        text: root.limit
        anchors.right: rec.left
        anchors.rightMargin: 0

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
