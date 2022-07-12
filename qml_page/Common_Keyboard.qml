import QtQuick 2.14
import "module_keyboard"

Item {
    id: root
    implicitWidth: 800
    implicitHeight: 480
    signal callKeybroad(var currentText, var mode)
    signal keybroad_Reply(var outputdata, var checkState)
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }
    property bool active: false

    Rectangle {
        //遮蔽层
        anchors.fill: parent
        color: "black"
        opacity: root.active ? 0.8 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
        MouseArea {
            enabled: root.active
            anchors.fill: parent
        }
    }
    onCallKeybroad: {
        switch (mode) {
        case Common_Keyboard.Mode.ALL:
            text_Dialog.text = currentText
            mode_Number.enabled = false
            mode_ALL.enabled = true
            break
        case Common_Keyboard.Mode.Number:
            text_Dialog.text = Math.abs(currentText)
            mode_ALL.enabled = false
            mode_Number.enabled = true
            mode_Number.plus = currentText >= 0
            break
        }
        root.active = true
    }
    onKeybroad_Reply: root.active = false
    enum Mode {
        ALL,
        Number
    }
    Rectangle {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        color: root.rgb(236, 236, 236)
        y: root.active ? 0 : root.height
        Behavior on y {
            NumberAnimation {
                duration: 200
            }
        }
        onYChanged: {
            if (y === 0) {
                text_Dialog.focus = true
            }
        }
        /// Dialog : height = 70(Fixed)
        Result_Button {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5
            height: 50
            width: height
            titleImg: "./module_keyboard/cancel.svg"
            onClicked: root.keybroad_Reply(text_Dialog.text, false)
        }
        Result_Button {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5
            height: 50
            width: height
            titleImg: "./module_keyboard/checkmark.svg"
            onClicked: {
                if (mode_ALL.enabled)
                    root.keybroad_Reply(text_Dialog.text, true)

                if (mode_Number.enabled)
                    root.keybroad_Reply(
                                (mode_Number.plus ? "" : "-") + text_Dialog.text,
                                true)
            }
        }
        Text_Dialog {
            id: text_Dialog
            height: 60
            width: parent.width - 120
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
        }
        ///Input Key & Control Key & Switch Key
        Item {
            id: keyArea
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            height: parent.height - 70
            width: parent.width - 10
            anchors.horizontalCenter: parent.horizontalCenter
            Mode_Number {
                id: mode_Number
                anchors.fill: parent
                onBack_delete: {
                    text_Dialog.remove(text_Dialog.cursorPosition - 1,
                                       text_Dialog.cursorPosition)
                }
                onCursor_released: text_Dialog.focus = true
                onClicked: {
                    text_Dialog.insert(text_Dialog.cursorPosition, value)
                    text_Dialog.focus = true
                }
            }
            Mode_ALL {
                id: mode_ALL
                anchors.fill: parent
                onBack_delete: {
                    text_Dialog.remove(text_Dialog.cursorPosition - 1,
                                       text_Dialog.cursorPosition)
                }
                onCursor_released: {
                    text_Dialog.focus = true
                }
                onCursor_move: {
                    switch (direction) {
                    case Mode_ALL.Direction.Left:
                        text_Dialog.cursorPosition -= 1
                        break
                    case Mode_ALL.Direction.Right:
                        text_Dialog.cursorPosition += 1
                        break
                    }
                }
                onClicked: {
                    text_Dialog.insert(text_Dialog.cursorPosition, value)
                    text_Dialog.focus = true
                }
            }
        }
    }
}
