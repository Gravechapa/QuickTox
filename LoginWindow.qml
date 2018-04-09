import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import qatox.LoginController 1.0

Window {
    visible: true
    width: 480
    height: 640
    id: loginWindow
    title: qsTr("Login")

    TextField {
        id: userName
        width: 180
        height: 40
        anchors.bottom: login.top
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("User name")
    }

    Button {
        id: login
        text: qsTr("Login")
        width: 180
        height: 50
        anchors.centerIn: parent
        onClicked: {
            var rez = controller.authenticate();
            var component = Qt.createComponent("MainWindow.qml");
            var win = component.createObject();
            win.userid = rez;
            win.show();
            loginWindow.close();
        }
    }

    LoginController {
        id: controller
    }
}
