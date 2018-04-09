import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import qatox.MainController 1.0

Item {
    visible: true
    anchors.fill: parent
    id: mainWindow

    TextField {
        x: 22
        y: 220
        text: controller.userid
        selectByMouse: true
    }

    TextField {
        id: textMsg
        x: 22
        y: 300
    }

    MainController {
        id: controller
    }

    Connections {
        target: controller
        onMessageReceived: {
            textMsg.text = id;
        }
    }
}
