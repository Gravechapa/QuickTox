import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QuickTox.MainController 1.0

Item {
    visible: true
    anchors.fill: parent
    id: mainWindow

    Text {
        id: selfStatus
        width: 200
        height: 25
        text: qsTr("NONE")
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 12
    }

    TextField {
        id: uId
        text: controller.userid
        clip: false
        anchors.top: selfStatus.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        selectByMouse: true
        readOnly: true
    }

    TextField {
        id: textMsg
        anchors.top: uId.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        readOnly: true
    }

    MainController {
        id: controller
    }

    Connections {
        target: controller
        onMessageReceived: {
            textMsg.text = id;
        }
        onStatusChanged: {
            selfStatus.text = status;
        }
    }

    TextField {
        id: sendText
        placeholderText: qsTr("Input respond to last msg")
        anchors.top: textMsg.bottom
        anchors.topMargin: 67
        anchors.horizontalCenter: parent.horizontalCenter
        Keys.onPressed: {
            if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                send();
            }
        }
    }

    Button {
        id: button
        text: qsTr("Send")
        anchors.top: sendText.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {send()}
    }

    function send()
    {
        controller.sendMsg(sendText.text);
        sendText.text = '';
    }

    ListModel {
        id: friendList
    }

    ListView {
        width: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 480
        anchors.top: parent.top
        anchors.topMargin: 0
        model: friendList
        delegate: Text {
            text: friendName
        }
    }

    Connections {
        target: controller
        onFriendAdded: {
            friendList.append({"friendName": name})
        }
    }
}
