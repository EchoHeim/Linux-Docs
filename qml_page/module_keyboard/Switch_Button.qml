import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property color themeColor: "white"
    property alias iconImg: iconArea.source //整体图标文件
    property double dropShadowOffset: 2
    property double pressDarkFactor: 1.1
    checkable: true
    signal cursor_released

    onDownChanged: {
        if (!down)
            root.cursor_released()
    }

    background: Rectangle {
        anchors.fill: root
        color: "transparent"
        anchors.margins: root.pressed | root.pressAndHold | root.checked ? 7 : 5
        Behavior on anchors.margins {
            NumberAnimation {
                duration: 75
            }
        }
        Rectangle {
            //阴影效果
            id: visualTargrtShadow
            anchors.fill: parent
            color: "#bbbbbb"
            z: 0
            radius: 10
            //            visible: false
            layer.enabled: true
            layer.effect: DropShadow {
                id: dropShadow
                anchors.fill: visualTargrtShadow
                horizontalOffset: root.pressed | root.pressAndHold
                                  | root.checked ? 0 : dropShadowOffset
                Behavior on horizontalOffset {
                    NumberAnimation {
                        duration: 75
                    }
                }
                verticalOffset: root.pressed | root.pressAndHold
                                | root.checked ? 0 : dropShadowOffset
                Behavior on verticalOffset {
                    NumberAnimation {
                        duration: 75
                    }
                }
                radius: root.pressed | root.pressAndHold | root.checked ? 0 : 12
                Behavior on radius {
                    NumberAnimation {
                        duration: 75
                    }
                }
                samples: 25
                color: "#bbbbbb"
                source: visualTargrtShadow
                z: 0
            }
        }
        Rectangle {
            id: visualTargrt
            anchors.fill: parent
            color: root.pressed | root.pressAndHold
                   | root.checked ? Qt.darker(themeColor,
                                              pressDarkFactor) : themeColor
            z: 1
            border.color: root.pressed | root.pressAndHold
                          | root.checked ? "#999999" : "transparent"
            Behavior on border.color {
                ColorAnimation {
                    duration: 75
                }
            }
            radius: 10
            clip: true
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    implicitWidth: visualTargrt.implicitWidth
                    implicitHeight: visualTargrt.implicitHeight
                    width: visualTargrt.width
                    height: visualTargrt.height
                    radius: visualTargrt.radius
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 75
                }
            }
            Rectangle {
                //图标显示区域
                anchors.fill: parent
                anchors.margins: 2
                color: "transparent"
                Image {
                    id: iconArea
                    source: "Shift_lock_2.svg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    anchors.bottomMargin: parent.height / 6
                    anchors.topMargin: parent.height / 6
                    anchors.leftMargin: parent.width / 6
                    anchors.rightMargin: parent.width / 6
                }
            }
        }
    }
}
