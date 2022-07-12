import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property color themeColor: "#2a2424"
    property alias titleImg: titleArea.source //标题文字矢量图片
    property alias titleText: titleLabel.text //标题文字内容
    property alias fontColor: titleLabel.color
    property alias fontFamily: titleLabel.font.family
    property double dropShadowOffset: 0
    property double pressDarkFactor: 1.1
    property bool shadowEnable: true
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
            visible: shadowEnable
            anchors.fill: parent
            anchors.margins: 1
            color: !(root.pressed | root.pressAndHold) ? "transparent" : "#65e7ff"
            Behavior on color {
                ColorAnimation {
                    duration: 75
                }
            }
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
                radius: !(root.pressed | root.pressAndHold) ? 0 : 24
                Behavior on radius {
                    NumberAnimation {
                        duration: 75
                    }
                }
                samples: 25
                color: "#65e7ff"
                source: visualTargrtShadow
                //                z: 0
            }
        }
        Rectangle {
            id: visualTargrt
            anchors.fill: parent
            //            color: root.pressed | root.pressAndHold ? Qt.darker(
            //                                                          themeColor,
            //                                                          pressDarkFactor) : themeColor
            color: root.pressed | root.pressAndHold ? themeColor : "transparent"
            border.color: root.pressed | root.pressAndHold ? "#65e7ff" : "transparent"
            Rectangle {
                height: 1
                width: parent.width
                anchors.bottom: parent.bottom
                color: root.checked ? "#65e7ff" : "transparent"
                Behavior on color {
                    ColorAnimation {
                        duration: 75
                    }
                }
            }
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
            Item {
                //文本显示区域
                id: textArea
                anchors.fill: parent
                anchors.margins: 2
                //                color: "transparent"
                Image {
                    id: titleArea
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    //                    anchors.horizontalCenter: visualTargrt.horizontalCenter
                    //                    anchors.bottom: visualTargrt.bottom
                    //                    width: visualTargrt.width - 4
                    //                    height: visualTargrt.height / 5 - 4
                    opacity: status === Image.Null ? 0 : 1
                    //            opacity: 0
                }
                Label {
                    id: titleLabel
                    anchors.fill: parent
                    font.pixelSize: height / 3 * 2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 1
                    //                    anchors.horizontalCenter: visualTargrt.horizontalCenter
                    //                    anchors.bottom: visualTargrt.bottom
                    //                    width: visualTargrt.width - 4
                    //                    height: visualTargrt.height / 5 - 4
                    //                                    text: "测试"
                    opacity: text.length <= 0 ? 0 : (titleArea.status !== Image.Null ? 0 : 1)
                    color: "white"
                }
            }
        }
    }
}
