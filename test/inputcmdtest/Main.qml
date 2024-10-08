// import QtQuick 2.15
// import QtQuick.Controls 2.15

// ApplicationWindow {
//     id:root
//     visible: true
//     width: 640
//     height: 480
//     title: qsTr("Mouse Area Example")
//     property var eventType: {
//         "UNKNOW":0,
//         "MOUSE_LEFT_CLICKED":1,
//         "MOUSE_LEFT_DOUBLE_CLICKED": 2,
//         "MOUSE_LEFT_PRESS_AND_HOLD": 3,
//         "MOUSE_RIGHT_CLICKED": 4,
//         "MOUSE_RIGHT_DOUBLE_CLICKED": 5,
//         "MOUSE_RIGHT_PRESS_AND_HOLD": 6,
//         "MOUSE_MIDDLE_CLICKED": 7,
//         "MOUSE_MIDDLE_DOUBLE_CLICKED": 8,
//         "MOUSE_MIDDLE_PRESS_AND_HOLD": 9,
//         "KEY_PRESSED": 20,
//         "KEY_RELEASED": 21,
//         "KEY_PRESSED_AND_HOLD": 22
//     }

//     Rectangle {
//         id: mouseAreaRect
//         width: 200
//         height: 200
//         color: "lightblue"

//         MouseArea {
//             id: mouseArea
//             anchors.fill: parent
//             onClicked: {
//                 console.log("Mouse clicked at:", mouse.x, mouse.y)
//                 TcpLink.sendMouseEvent(root.eventType.MOUSE_LEFT_CLICKED, mouse.x, mouse.y)
//             }
//             onDoubleClicked: {
//                 console.log("Mouse double clicked at:", mouse.x, mouse.y)
//             }
//             onPressAndHold: {
//                 console.log("Mouse pressed and held at:", mouse.x, mouse.y)
//             }
//             Keys.onPressed: {
//                 console.log("Key pressed:", event.text, event.key, event.nativeScanCode, event.modifiers, event.nativeModifiers)
//                 TcpLink.sendKeyEvent(root.eventType.KEY_PRESSED, event.key, event.text)
//             }
//             Keys.onReleased: {
//                 // console.log("Key released:", event.text, event.key)
//             }
//         }
//     }

//     // // 为了捕获键盘事件，我们需要一个焦点项
//     // FocusScope {
//     //     anchors.fill: parent
//     //     focus: true

//     //     Keys.onPressed: {
//     //         console.log("Key pressed:", event.text, event.key, event.nativeScanCode, event.modifiers, event.nativeModifiers)
//     //         TcpLink.sendKeyEvent(root.eventType.KEY_PRESSED, event.key, event.text)
//     //     }
//     //     Keys.onReleased: {
//     //         // console.log("Key released:", event.text, event.key)
//     //     }
//     // }
// }

import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Key Capture Example")
    property var eventType: {
        "UNKNOW":0,
        "MOUSE_LEFT_CLICKED":1,
        "MOUSE_LEFT_DOUBLE_CLICKED": 2,
        "MOUSE_LEFT_PRESS_AND_HOLD": 3,
        "MOUSE_RIGHT_CLICKED": 4,
        "MOUSE_RIGHT_DOUBLE_CLICKED": 5,
        "MOUSE_RIGHT_PRESS_AND_HOLD": 6,
        "MOUSE_MIDDLE_CLICKED": 7,
        "MOUSE_MIDDLE_DOUBLE_CLICKED": 8,
        "MOUSE_MIDDLE_PRESS_AND_HOLD": 9,
        "KEY_PRESSED": 20,
        "KEY_RELEASED": 21,
        "KEY_PRESSED_AND_HOLD": 22
    }
    TextInput {
        id: textInput
        anchors.centerIn: parent
        width: 200
        height: 40
        // focus: true

        Keys.onPressed: {
            // 在这里发送键值，例如通过信号或调用函数
            console.log("Key pressed:", event.text, event.key, event.nativeScanCode, event.modifiers, event.nativeModifiers)
            TcpLink.sendKeyEvent(root.eventType.KEY_PRESSED, event.key, event.text)
        }
        Keys.onReleased: {
            // console.log("Key released:", event.text, event.key)
            TcpLink.sendKeyEvent(root.eventType.KEY_RELEASED, event.key, event.text)
        }
    }
}
