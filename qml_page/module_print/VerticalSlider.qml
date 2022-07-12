import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Slider {
    id: root
    implicitHeight: 500
    implicitWidth: 100
    stepSize: 1
    property bool inside: true
    property color checkedColor: "#65e7ff"
    orientation: Qt.Vertical
    background: Item {
        anchors.fill: root
        Rectangle {
            id: rect_background
            anchors.centerIn: parent
            width: root.inside ? (root.availableWidth / 5) : (root.availableWidth / 3 + 2)
            height: root.availableHeight
            color: "transparent"
            border.color: "white"
            radius: width / 2
        }
        Rectangle {
            id: rect_visual
            anchors.bottom: rect_background.bottom
            anchors.horizontalCenter: rect_background.horizontalCenter
            height: root.height - (root.handle.y + root.handle.height / 2) + (root.inside ? 0 : -4)
            Behavior on height {
                NumberAnimation {
                    duration: 10
                }
            }
            anchors.bottomMargin: root.inside ? 0 : 2
            width: rect_background.width + (root.inside ? 2 : -4)
            color: "transparent"
            radius: width / 2
        }
    }
    handle: Rectangle {
        x: root.leftPadding + root.availableWidth / 2 - width / 2
        y: root.topPadding + root.visualPosition * (root.availableHeight - height)
        Behavior on y {
            NumberAnimation {
                duration: 10
            }
        }

        color: root.pressed ? Qt.darker(root.checkedColor,
                                        1.2) : root.checkedColor
        border.color: "white"
        border.width: (width - root.availableWidth / 5) / 2
        implicitWidth: root.availableWidth / 3
        implicitHeight: width
        radius: implicitHeight
        transformOrigin: Item.Center
        Label {
            text: root.value.toFixed(2)
            width: root.availableWidth / 3
            anchors.right: parent.left
            anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: root.availableWidth / 5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            color: "#65e7ff"
        }
    }
}
