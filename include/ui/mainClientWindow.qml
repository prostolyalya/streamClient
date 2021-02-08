import QtQuick 2.12
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
import QtQml.Models 2.15

ApplicationWindow
{
    visible: true
    width: 800
    height: 800
    title: qsTr("Client")
    Component.onCompleted: startWindow.close()
    Text {
        id: mainText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.topMargin: 30
        text: qsTr("Information:")
    }
    Rectangle
    {
        id: mainTextArea
        anchors.top: mainText.bottom
        anchors.left: mainText.left
        width: 500
        height: 200
        border.color: "black"
        border.width: 1
        color: "#D9DDDC"
        Flickable
        {
            anchors.fill: parent
            TextArea.flickable: TextArea
            {
                text: uiController.uiText
                color: "#311432"
                wrapMode: TextArea.Wrap
            }
            ScrollBar.vertical: ScrollBar { }
        }
    }
    Rectangle
    {
        id: mainInput
        anchors.top: mainTextArea.bottom
        anchors.left: mainTextArea.left
        anchors.topMargin: 40
        width: 300
        height: 200
        border.color: "black"
        border.width: 1
        color: "#D9DDDC"
        Flickable
        {
            anchors.fill: parent
            TextArea.flickable: TextArea
            {
                id: mainInputText
                color: "#311432"
                wrapMode: TextArea.Wrap
            }
            ScrollBar.vertical: ScrollBar { }
        }
    }
    Text {
        anchors.bottom: mainInput.top
        anchors.left: mainInput.left
        text: qsTr("Message:")
    }
    Rectangle
    {
        id: clientFiles
        anchors.top: mainInput.bottom
        anchors.left: mainInput.left
        anchors.topMargin: 40
        width: 500
        height: 200
        color: "#D9DDDC"
        border.width: 1
        border.color: "black"
        ListView
        {
            anchors.fill: parent
            model: uiController.uiListFiles
            focus: true
            delegate: Rectangle{
                width: parent.width
                height: 20
                border.color: "black"
                color: "#95C8D8"
                Text{
                    text: modelData
                    anchors.centerIn: parent
                    color: "#311432"
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
    Text {
        anchors.bottom: clientFiles.top
        anchors.left: clientFiles.left
        text: qsTr("Files:")
    }
    Rectangle
    {
       id: buttonSendText
       anchors.top: mainInput.top
       anchors.left: mainInput.right
       anchors.leftMargin: 5
       width: 80
       height: 20
       color: "yellow"
       border.width: 1
       border.color: "black"
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
                uiController.sendText(mainInputText.text)
                mainInputText.text = ""
            }

       }
    }
    Rectangle
    {
       id: sendFileButton
       anchors.top: buttonSendText.bottom
       anchors.left: buttonSendText.left
       anchors.topMargin: 20
       width: 80
       height: 20
       color: "yellow"
       border.width: 1
       border.color: "black"
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
                mainInputText.text = ""
            }

       }
    }
    Rectangle
    {
       anchors.top: clientFiles.top
       anchors.left: clientFiles.right
       anchors.leftMargin: 5
       width: 140
       height: 30
       color: "yellow"
       border.width: 1
       border.color: "black"
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
        onAccepted: {
            console.log("You chose: " + fileDialog.currentFile)
            uiController.sendFile(fileDialog.currentFile)
        }
        onRejected: {
            fileDialog.close()
        }
    }

}
