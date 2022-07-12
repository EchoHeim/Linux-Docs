import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
    id: root
    implicitWidth: 730
    implicitHeight: 480
    signal back_delete
    signal cursor_move(var direction)
    signal cursor_released
    signal clicked(var value)
    enum Direction {
        Left,
        Right
    }
    visible: enabled
    GridLayout {
        id: panel
        width: parent.width
        height: parent.height
        rows: 5
        columns: 12
        anchors.centerIn: parent
        rowSpacing: 5
        // Row 1
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "!" : "1"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "@" : "2"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "#" : "3"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "¥" : "$") : "4"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "%" : "5"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "…" : "^") : "6"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "&" : "7"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "*" : "8"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "(" : "9"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? ")" : "0"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "_" : "=") : (key_Caps.checked ? "-" : "+")
            onTouched: root.clicked(titleText)
        }
        Cursor_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            iconImg: "./back_delete.svg"
            onClicked: root.back_delete()
            onCursor_released: root.cursor_released()
        }
        // Row 2
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "Q" : "q"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "W" : "w"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "E" : "e"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "R" : "r"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "T" : "t"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "Y" : "y"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "U" : "u"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "I" : "i"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "O" : "o"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "P" : "p"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "【" : "「") : (key_Caps.checked ? "{" : "[")
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "】" : "」") : (key_Caps.checked ? "}" : "]")
            onTouched: root.clicked(titleText)
        }
        // Row 3
        Switch_Button {
            id: key_Caps
            Layout.fillWidth: true
            Layout.fillHeight: true
            iconImg: "./Caps_lock.svg"
            onCursor_released: root.cursor_released()
        }
        General_Button {
            highlighted: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "A" : "a"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "S" : "s"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "D" : "d"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "F" : "f"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "G" : "g"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "H" : "h"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "J" : "j"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "K" : "k"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "L" : "l"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "'" : "\""
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? (key_Caps.checked ? "`" : "、") : (key_Caps.checked ? "\\" : "|")
            onTouched: root.clicked(titleText)
        }
        // Row 4
        Switch_Button {
            id: key_Shift
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            iconImg: "./Shift_lock.svg"
            onCursor_released: root.cursor_released()
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "Z" : "z"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "X" : "x"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "C" : "c"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "V" : "v"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "B" : "b"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "N" : "n"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "M" : "m"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "《" : "<"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "》" : ">"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "?" : "/"
            onTouched: root.clicked(titleText)
        }
        // Row 5
        Cursor_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            iconImg: "./left.svg"
            onClicked: root.cursor_move(Mode_ALL.Direction.Left)
            onCursor_released: root.cursor_released()
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Caps.checked ? "·" : "~"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleImg: "./space.svg"
            Layout.columnSpan: 5
            onTouched: root.clicked(" ")
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? "," : "."
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: key_Shift.checked ? ":" : ";"
            onTouched: root.clicked(titleText)
        }
        Cursor_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            iconImg: "./right.svg"
            onClicked: root.cursor_move(Mode_ALL.Direction.Right)
            onCursor_released: root.cursor_released()
        }
    }
}
