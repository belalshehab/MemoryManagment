import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import MemoryManagment 1.0

GrayRectangle {
    id: root
    implicitWidth: 1160
    implicitHeight: 75


    property int algorithm : Memory.FIRST_FIT

    RowLayout {
        id: buttonsColumn
        anchors.rightMargin: 30
        anchors.leftMargin: 30
        spacing: 10
        anchors.fill: parent

        Label {
            id: label

            height: 27
            color: "#bababa"

            text: qsTr("Algorithms:")
            Layout.fillHeight: true
            Layout.fillWidth: false
            verticalAlignment: Text.AlignVCenter
            font.capitalization: Font.MixedCase
            font.weight: Font.Bold
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
        }


        AllocationButton {
            id: firstFit
            text: qsTr("FirstFit")
            Layout.fillHeight: true
            Layout.fillWidth: false
            checked: true
            onClicked: {
                algorithm = Memory.FIRST_FIT
            }
        }

        AllocationButton {
            id: bestFit
            text: qsTr("BestFit")
            Layout.fillHeight: true
            Layout.fillWidth: false
            onClicked: {
                algorithm = MemoryModel.BEST_FIT
            }
        }

        AllocationButton {
            id: worestFit
            text: qsTr("WorestFit")
            Layout.fillHeight: true
            Layout.fillWidth: false

            onClicked: {
                algorithm = Memory.WORST_FIT
            }
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:853}
}
##^##*/
