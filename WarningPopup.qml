import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Popup {
    id: root

    anchors.centerIn: parent
    implicitWidth: 400
    implicitHeight: 300

    background: GrayRectangle{

    }

    modal: true
    dim: true

    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Can't add this process try remove some processes first")

        font.pixelSize: 15
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: button
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("OK")
        display: AbstractButton.TextOnly

        onClicked: root.close()
    }
}
