import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    minimumWidth: 480
    minimumHeight: 640
    id: mainWindow
    title: qsTr("QuickTox")
    Loader { id: mainLoader
             source: "LoginContainer.qml"
             anchors.fill: parent
    }
}
