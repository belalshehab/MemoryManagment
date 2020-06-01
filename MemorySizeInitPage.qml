import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

GrayRectangle {
    id: root

    implicitWidth: 300
    implicitHeight: 250

    property alias memorySize: titledSpinBox.value

    signal nextClicked
    Label {
        id: label
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("Enter the memory size")

        font.weight: Font.Bold
        font.pixelSize: 25

        color: "#cbcbcb"
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

    ColumnLayout {
        id: columnLayout
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: deepLine.bottom
        anchors.topMargin: 20

        TitledSpinBox {
            id: titledSpinBox
            text: "Memory Size"
            Layout.preferredWidth: 160
            Layout.preferredHeight: 65
            Layout.minimumHeight: 65
            Layout.minimumWidth: 120
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            to: 10000000
        }

        Button {
            id: nextButton
            text: qsTr("Next")
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom

            onClicked: nextClicked()
        }
    }



}

/*##^##
Designer {
    D{i:3;anchors_height:130;anchors_width:170}
}
##^##*/
