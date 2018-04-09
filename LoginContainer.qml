import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import qatox.LoginController 1.0

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
    }

    Button {
        id: login
        text: qsTr("Login")
        width: 180
        height: 50
        anchors.centerIn: parent
        onClicked: {
            if (controller.userName.length == 0) {
                return;
            }

            controller.authenticate();
            authenticated();
            mainLoader.source = "MainContainer.qml"
        }
    }

    LoginController {
        id: controller
    }

    signal authenticated
}
