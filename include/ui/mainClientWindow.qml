import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.3

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
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
       id: buttonSend
       anchors.top: mainInput.top
       anchors.left: mainInput.right
       width: 50
       height: 20
       border.width: 1
       border.color: "yellow"
       Text {
           anchors.centerIn: parent
           text: qsTr("Send")
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
