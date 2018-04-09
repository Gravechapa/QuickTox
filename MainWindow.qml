import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0

Window {
    visible: true
    width: 480
    height: 640
    id: mainWindow
    title: qsTr("Main")
    property string userid

    TextField {
        text: userid
    }

    TextField {
        id: textMsg
        x: 0
        y: 114
    }
}
