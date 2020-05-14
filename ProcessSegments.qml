import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

GrayRectangle {
    id: root
    implicitHeight: 350
    implicitWidth: 600

    property alias model: segmentsView.model
    property int maximumSegmentLimit: 10000
    property alias processColor: colorRec.color

    signal addProcessClicked

    Label {
        id: label
        color: "#cbcbcb"
        text: qsTr("Process")
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
    
    RowLayout
    {
        id: segmentInputLayout
        height: 60
        anchors.top: deepLine.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        Button {
            id: addSegmentButton

            text: qsTr("Add Segment")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: false

            onClicked: {
                segmentsView.model.append({"sid": segmentsView.model.count +1, "limit": limitSpinBox.value, "name": nameTextField.text})
            }
        }

        Item{
            id: element
            Layout.minimumWidth: 150
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Label{
                id: limitLabel
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Limit")
                font.weight: Font.Bold
                font.pixelSize: 17
                color: "#BABABA"
            }

            SpinBox {
                id: limitSpinBox
                anchors.top: limitLabel.bottom
                anchors.topMargin: 0
                font.weight: Font.Medium
                font.pixelSize: 15

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right

                from: 1
                to: root.maximumSegmentLimit

                editable: true
                wheelEnabled: true
            }
        }



        Item {
            id: element1
            Layout.minimumWidth: 150
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true

            Label{
                id: nameLabel
                anchors.top: parent.top
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Name")
                font.weight: Font.Bold
                font.pixelSize: 17
                color: "#BABABA"
            }

            TextField {
                id: nameTextField
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: nameLabel.bottom

                text: qsTr("Segment name")

                font.weight: Font.Medium
                font.capitalization: Font.MixedCase
                font.pixelSize: 15
                font.family: "ROBOTO"
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
    ListView {
        id: segmentsView

        anchors.top: segmentInputLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20

        anchors.bottom: processInputLayout.top
        anchors.bottomMargin: 10

        clip: true
        spacing: 12

        ScrollBar.vertical: ScrollBar{ width: 6}
        delegate: segmentDelegate

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
        id: segmentDelegate

        SegmentDelegate {
            width: segmentsView.width - 7
            sid: model.sid
            limit: model.limit
            name: model.name

            onDeleteClicked: segmentsView.model.remove(index)
        }
    }

    RowLayout{
        id: processInputLayout
        anchors.left: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20

        height: 48
        Button {
            id: clearButton

            text: qsTr("Clear")
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: false

            onClicked: segmentsView.model.clear()
        }

        Button{
            id: addProcessButton
            text: "Add Process"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            onClicked: {
                addProcessClicked()
            }
        }

        Rectangle{
            id: colorRec
            Layout.fillHeight: true
            Layout.bottomMargin: 6
            Layout.topMargin: 6

            Layout.maximumWidth: 7
            Layout.minimumWidth: 5
            Layout.preferredWidth: 6

            color:  Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    colorDialog.open()
                }
            }
        }

    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            root.processColor = colorDialog.color
        }
    }
}

/*##^##
Designer {
    D{i:7;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}D{i:9;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}
D{i:10;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}D{i:8;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}
D{i:12;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}D{i:11;anchors_height:160;anchors_width:110;anchors_x:112;anchors_y:93}
}
##^##*/
