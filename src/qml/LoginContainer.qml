import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QuickTox.LoginController 1.0

Item {
    visible: true
    anchors.fill: parent
    id: loginContainer
    TextField {
        id: userName
        width: 180
        height: 40
        anchors.bottom: login.top
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("User name")
        onTextChanged: controller.userName = text
        Keys.onPressed: {
            if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                input();
            }
        }
    }

    Button {
        id: login
        text: qsTr("Login")
        width: 180
        height: 50
        anchors.centerIn: parent
        onClicked: {input();}
    }

    LoginController {
        id: controller
    }

    function input() {
        if (controller.userName.length == 0) {
            return;
        }

        controller.authenticate();
        mainLoader.source = "MainContainer.qml"
    }
}
