import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
    id: root
    implicitWidth: 730
    implicitHeight: 480
    signal back_delete
    //    signal cursor_move(var direction)
    signal cursor_released
    signal clicked(var value)
    property bool plus: true
    //    enum Direction {
    //        Left,
    //        Right
    //    }
    visible: enabled
    GridLayout {
        id: panel
        width: parent.width - 110
        height: parent.height
        rows: 4
        columns: 4
        anchors.centerIn: parent
        rowSpacing: 5
        columnSpacing: 5
        // +
        Switch_Button {
            id: plus
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 2
            checked: root.plus
            enabled: !root.plus
            onClicked: {
                root.plus = true
            }
            iconImg: "./plus.svg"
        }
        // 1-3
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "1"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "2"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "3"
            onTouched: root.clicked(titleText)
        }
        // 4-6
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "4"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "5"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "6"
            onTouched: root.clicked(titleText)
        }
        // -
        Switch_Button {
            id: minus
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rowSpan: 2
            iconImg: "./minus.svg"
            checked: !root.plus
            enabled: root.plus
            onClicked: {
                root.plus = false
            }
        }
        // 7-9
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "7"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "8"
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "9"
            onTouched: root.clicked(titleText)
        }
        // .0 delete
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "."
            onTouched: root.clicked(titleText)
        }
        General_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleText: "0"
            onTouched: root.clicked(titleText)
        }
        Cursor_Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            iconImg: "./back_delete.svg"
            onClicked: root.back_delete()
            onCursor_released: root.cursor_released()
        }
    }
}
