import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

TextField {
    id: root
    property color checkedColor: "#999999"

    placeholderText: enabled ? qsTr("请输入内容") : qsTr("输入不可用")
    font.pixelSize: height / 2
    antialiasing: true
    implicitWidth: 213
    implicitHeight: 42

    background: Rectangle {
        id: background_area
        anchors.fill: root
        anchors.margins: 5
        radius: height / 4
        color: root.enabled ? "white" : "tranparent"
        border.color: root.enabled ? root.checkedColor : "#999999"
        border.width: 1
        //        opacity: root.enabled ? 1 : 0.7
        //        Behavior on anchors.margins {
        //            NumberAnimation {
        //                duration: 250
        //            }
        //        }
        Behavior on border.color {
            ColorAnimation {
                duration: 250
            }
        }
        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }

        layer.enabled: true
        layer.effect: DropShadow {
            id: dropShadow
            transparentBorder: true
            color: "#cccccc"
            samples: 20 /*20*/
        }
    }
    onPressAndHold: selectAll()

    cursorDelegate: Rectangle {
        anchors.verticalCenter: root.verticalCenter
        width: 2
        height: root.height / 2
        color: "#999999"
        visible: root.focus ? root.focus : true

        Timer {
            interval: 300
            repeat: true
            running: root.focus
            onRunningChanged: parent.visible = root.focus ? running : true
            onTriggered: parent.visible = root.focus ? !parent.visible : true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

