import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item{
    id: root
    implicitHeight: 30
    implicitWidth: 600
    
    property int sid
    property int limit
    property string name
    
    signal deleteClicked

    RowLayout{
        id: rowLayout
        anchors.fill: parent
        RoundButton{
            id: deleteButton

            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            Layout.maximumHeight: 35
            Layout.maximumWidth: 35
            Layout.minimumHeight: 25
            Layout.minimumWidth: 25

            text: "X"

            display: AbstractButton.TextOnly
            font.weight: Font.Bold
            font.pixelSize: 10
            font.family: "ROBOTO"


            onClicked:
            {
                deleteClicked()
            }
        }

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

            text: qsTr("S" + sid)
            font.pixelSize: 15
            color: "#fffffff0"
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
            text: qsTr(limit + " Bytes")
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

            text: qsTr(name)

            fontSizeMode: Text.HorizontalFit
            wrapMode: Text.NoWrap
            clip: true
            font.pixelSize: 15

            color: "#fffffff0"
        }
    }
    DeepLine{
        anchors.bottom: parent.bottom
        width: parent.width
    }
}
