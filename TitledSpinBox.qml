import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Item{
    id: root
    property alias text: label.text
    property alias from: spinBox.from
    property alias to: spinBox.to
    property alias stepSize: spinBox.stepSize
    property alias value: spinBox.value
    Label{
        id: label
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Bold
        font.pixelSize: 17
        color: "#BABABA"
    }
    
    SpinBox {
        id: spinBox
        anchors.top: label.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        from: 1

        editable: true
        wheelEnabled: true

        font.weight: Font.Medium
        font.pixelSize: 15
    }
}
