import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    implicitWidth: 800
    implicitHeight: 480
    color: "transparent"
    signal back
    property bool active: false
    onBack: root.active = false
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
            onClicked: {
                root.back()
            }
        }
    }
    Rectangle {
        y: root.active ? 0 : -dialog.height - 2
        Behavior on y {
            NumberAnimation {
                duration: 150
            }
        }
        id: dialog
        color: "transparent"
        width: parent.width
        height: 80
        anchors.horizontalCenter: parent.horizontalCenter
        //        clip: true
        //        radius: 10
        //        layer.enabled: true
        //        layer.effect: OpacityMask {
        //            maskSource: Rectangle {
        //                implicitWidth: dialog.implicitWidth
        //                implicitHeight: dialog.implicitHeight
        //                width: dialog.width
        //                height: dialog.height
        //                radius: dialog.radius
        //            }
        //        }
        Exit_Button {
            width: parent.width / 2
            height: 60
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            onClicked: {
                Qt.quit()
            }
        }
    }
}
