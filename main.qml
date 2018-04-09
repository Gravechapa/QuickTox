import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQml.StateMachine 1.0 as DSM

ApplicationWindow {
    visible: true
    minimumWidth: 480
    minimumHeight: 640
    id: mainWindow
    title: qsTr("qatox")
    Loader { id: mainLoader
             source: "LoginContainer.qml"
             anchors.fill: parent
    }
}
