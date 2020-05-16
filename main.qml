import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import MemoryManagment 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1200
    height: 720

    color: "#333333"
    title: "Memory managment"

    AllocationMethods {
        id: allocationMethods

        height: 50
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
    }


    MemoryView {
        id: memoryView

        anchors.top: allocationMethods.bottom
        anchors.topMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 30

        model: memory.memoryModel
    }



    ProcessSegments {
        id: processSegments
        x: 132
        y: 144
        width: 576
        height: 335

        model: memory.segmentTableModel


        onAddProcessClicked: {
            model.color = processColor
            if(memory.addProcess(allocationMethods.algorithm))
            {
                processColor = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                processSegments.model.clear();
                processSegments.model.lastPid = memory.lastPid
            }
            else
            {
                warningPopup.open();
                console.log("Can't add process");
            }

        }
    }

   WarningPopup
   {
       id: warningPopup


   }
}
