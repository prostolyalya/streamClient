import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.3
import QtQml.Models 2.15

ApplicationWindow
{
    visible: true
    width: 800
    height: 800
    title: qsTr("Client")
    Text {
        id: mainText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 150
        anchors.topMargin: 30
        text: qsTr("Client")
    }
    TextArea
    {
        anchors.top: mainText.bottom
        anchors.left: mainText.left
        id: mainTextArea
        width: 300
        height: 200
        text: uiController.uiText
    }

    TextArea
    {
        anchors.top: mainTextArea.bottom
        anchors.left: mainTextArea.left
        anchors.topMargin: 20
        id: mainInput
        width: 300
        height: 200
    }
    Rectangle
    {
        anchors.top: mainInput.bottom
        anchors.left: mainInput.left
        anchors.topMargin: 20
        id: clientFiles
        width: 300
        height: 200
        ListView
        {
            anchors.fill: parent
            model: uiController.uiListFiles

//            highlight: Rectangle { color: "lightsteelblue"; radius: 1 }
            focus: true
            delegate: Rectangle{
                width: parent.width
                height: 20
                Text{
                    text: modelData
                }
                MouseArea
                {
                    anchors.fill: parent
                    onDoubleClicked:
                    {
                        uiController.requestFile(modelData)
                    }
                }
            }
        }
    }
    Rectangle
    {
       id: buttonSend
       anchors.top: mainInput.top
       anchors.left: mainInput.right
       width: 80
       height: 20
       border.width: 1
       border.color: "yellow"
       Text {
           anchors.centerIn: parent
           text: qsTr("Send text")
       }
       anchors.rightMargin: 10
       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                uiController.sendText(mainInput.text)
                mainInput.text = ""
            }

       }
    }
    Rectangle
    {
       id: sendFileButton
       anchors.top: buttonSend.bottom
       anchors.left: buttonSend.left
       anchors.topMargin: 20
       width: 80
       height: 20
       border.width: 1
       border.color: "yellow"
       Text {
           anchors.centerIn: parent
           text: qsTr("Send file")
       }
       anchors.rightMargin: 10
       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                fileDialog.open()
                mainInput.text = ""
            }

       }
    }
    Rectangle
    {
       anchors.top: sendFileButton.bottom
       anchors.left: sendFileButton.left
       anchors.topMargin: 200
       anchors.rightMargin: 10
       width: 140
       height: 30
       border.width: 1
       border.color: "yellow"
       Text {
           anchors.centerIn: parent
           text: qsTr("Refresh my files")
       }

       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                uiController.requestFileList()
            }
       }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            uiController.sendFile(fileDialog.fileUrl)
        }
        onRejected: {
            fileDialog.close()
        }
    }

}
