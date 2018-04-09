import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQml.StateMachine 1.0 as DSM

ApplicationWindow {
    DSM.StateMachine {
        id: stateMachine
        running: true
        initialState: loginState
        DSM.State {
            id: loginState
            LoginContainer {
                id: loginContainer
            }
            DSM.SignalTransition {
                targetState: mainState
                signal: loginContainer.authenticate
            }
        }
        DSM.State {
            id: mainState
            MainContainer {
                id: mainContainer
            }
        }
    }
}
