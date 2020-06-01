import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


GrayRectangle {
    id: root
    implicitWidth: 600
    implicitHeight: 250

    property int memorySize
    signal finishedClicked
    signal addHoleFaild


    Label {
        id: label
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Memory Initialization")
        font.weight: Font.Bold
        font.pixelSize: 25
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

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

    RowLayout
    {
        id: segmentInputLayout
        height: 60
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        Button {
            id: addHoleButton

            text: qsTr("Add Hole")
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            onClicked: {
               if(!memory.addHole(limitSpinBox.value, baseSpinBox.value))
               {
                   addHoleFaild()
               }
            }

        }

        TitledSpinBox
        {
            id: limitSpinBox

            Layout.fillWidth: true
            Layout.minimumWidth: 150
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true

            from: 1
            to: root.memorySize

            text: qsTr("Limit")
        }

        TitledSpinBox
        {
            id: baseSpinBox

            Layout.fillWidth: true
            Layout.minimumWidth: 150
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true

            from: 1
            to: root.memorySize

            text: qsTr("Base")
        }
    }

    Button {
        id: finishedButton
        x: 271
        y: 176
        text: qsTr("Finished")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        display: AbstractButton.TextOnly

        onClicked: finishedClicked()
    }
}
