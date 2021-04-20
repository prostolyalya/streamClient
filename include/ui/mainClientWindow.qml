import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import QtMultimedia 5.12
import QtQuick.Dialogs 1.3

ApplicationWindow
{
    visible: true
    width: 800
    height: 1000
    title: qsTr("Client")
    property bool isPrivate : true
    Text {
        id: mainText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.topMargin: 10
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
        anchors.topMargin: 30
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
        anchors.topMargin: 30
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
        anchors.bottom: publicFiles.top
        anchors.left: publicFiles.left
        text: qsTr("Public files:")
    }
    Rectangle
    {
        id: publicFiles
        anchors.top: clientFiles.bottom
        anchors.left: clientFiles.left
        anchors.topMargin: 40
        width: 500
        height: 200
        color: "#D9DDDC"
        border.width: 1
        border.color: "black"
        ListView
        {
            anchors.fill: parent
            model: uiController.uiListPublicFiles
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
       width: 150
       height: 20
       color: "yellow"
       border.width: 1
       border.color: "black"
       Text {
           anchors.centerIn: parent
           text: qsTr("Send private file")
       }
       anchors.rightMargin: 10
       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                isPrivate = true
                fileDialog.open()
                mainInputText.text = ""
            }

       }
    }
    Rectangle
    {
       id: sendFileButton2
       anchors.top: sendFileButton.bottom
       anchors.left: sendFileButton.left
       anchors.topMargin: 20
       width: 150
       height: 20
       color: "yellow"
       border.width: 1
       border.color: "black"
       Text {
           anchors.centerIn: parent
           text: qsTr("Send public file")
       }
       anchors.rightMargin: 10
       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                isPrivate = false
                fileDialog.open()
                mainInputText.text = ""
            }

       }
    }
    Rectangle
    {
       id: buttonRefresh
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
    Rectangle
    {
       anchors.top: buttonRefresh.bottom
       anchors.left: buttonRefresh.left
       anchors.topMargin: 5
       width: 100
       height: 30
       color: "yellow"
       border.width: 1
       border.color: "black"
       Text {
           anchors.centerIn: parent
           text: qsTr("->")
       }

       MouseArea
       {
            anchors.fill: parent
            onClicked:
            {
                videoWindow.show()
            }
       }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            uiController.sendFile(fileDialog.fileUrl, isPrivate)
        }
        onRejected: {
            fileDialog.close()
        }
    }
    ApplicationWindow {
        id: videoWindow
        width : 1000
        height : 800
        color: "black"
        Rectangle
        {
            id: buttonChose
           anchors.top: parent.top
           anchors.left: parent.left
           anchors.topMargin: 5
           anchors.leftMargin: 5
           width: 50
           height: 50
           color: "yellow"
           border.width: 1
           border.color: "black"
           z:3
           Text {
               anchors.centerIn: parent
               text: qsTr("-")
           }

           MouseArea
           {
                anchors.fill: parent
                onClicked:
                {
                    fileDialogVideo.open()
                }
           }
        }
        Video {
            id: video
            anchors.fill: parent
            z:2
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
                    video.playbackState === MediaPlayer.PlayingState ? buttonChose.visible = false: buttonChose.visible = true
                }
            }

            focus: true
            Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video.seek(video.position - 5000)
            Keys.onRightPressed: video.seek(video.position + 5000)
        }
        FileDialog {
            id: fileDialogVideo
            title: "Please choose a file"
            onAccepted: {
                console.log("You chose: " + fileDialogVideo.fileUrl)
                video.source = "file://" + fileDialogVideo.fileUrl
            }
            onRejected: {
                fileDialogVideo.close()
            }
        }
    }
}


