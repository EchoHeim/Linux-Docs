import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property color themeColor: "white"
    property alias titleImg: titleArea.source //标题文字矢量图片
    property alias titleText: titleLabel.text //标题文字内容
    property alias iconImg: iconArea.source //整体图标文件
    property alias fontColor: titleLabel.color
    property alias fontFamily: titleLabel.font.family
    property double dropShadowOffset: 0
    property double pressDarkFactor: 1.1
    property bool shadowEnable: false
    property bool rotate: false
    background: Rectangle {
        anchors.fill: root
        color: "transparent"
        //        anchors.margins: root.pressed | root.pressAndHold ? 7 : 5
        anchors.margins: 5
        Behavior on anchors.margins {
            NumberAnimation {
                duration: 75
            }
        }
        Rectangle {
            //阴影效果
            id: visualTargrtShadow
            anchors.fill: parent
            color: "gray"
            z: 0
            radius: 10
            visible: root.shadowEnable
            //            visible: false
            layer.enabled: root.shadowEnable
            layer.effect: DropShadow {
                id: dropShadow
                anchors.fill: visualTargrtShadow
                horizontalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
                Behavior on horizontalOffset {
                    NumberAnimation {
                        duration: 75
                    }
                }
                verticalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
                Behavior on verticalOffset {
                    NumberAnimation {
                        duration: 75
                    }
                }
                radius: root.pressed | root.pressAndHold ? 0 : 12
                Behavior on radius {
                    NumberAnimation {
                        duration: 75
                    }
                }
                samples: 25
                color: "#cccccc"
                source: visualTargrtShadow
                //                z: 0
            }
        }
        Rectangle {
            id: visualTargrt
            anchors.fill: parent
            color: root.pressed
                   | root.pressAndHold ? Qt.darker(
                                             themeColor,
                                             (root.shadowEnable ? pressDarkFactor : 1)) : themeColor
            z: 1
            border.color: root.pressed | root.pressAndHold ? (root.shadowEnable ? "#999999" : "transparent") : "transparent"
            Behavior on border.color {
                ColorAnimation {
                    duration: 75
                }
            }
            radius: 10
            //            clip: true
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
                //文本显示区域
                id: textArea
                width: parent.width
                height: parent.height / 5
                anchors.horizontalCenter: parent.horizontalCenter
                //                anchors.bottomMargin: 2
                anchors.bottom: parent.bottom
                color: "transparent"
                opacity: titleArea.opacity === 0
                         && titleLabel.opacity === 0 ? 0 : 1
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
                    //                text: "测试"
                    opacity: text.length <= 0 ? 0 : (titleArea.status !== Image.Null ? 0 : 1)
                }
            }
            Item {
                //图标显示区域
                anchors.fill: parent
                anchors.bottomMargin: textArea.opacity === 0 ? 0 : parent.height / 5
                //                anchors.topMargin: 0
                //                anchors.leftMargin: 0
                //                anchors.rightMargin: 0
                //                color: "transparent"
                Image {
                    id: iconArea
                    source: "./temperature.svg"
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    anchors.bottomMargin: parent.height / (root.pressed | root.pressAndHold ? 5 : 6)
                    anchors.topMargin: parent.height / (root.pressed | root.pressAndHold ? 5 : 6)
                    anchors.leftMargin: parent.width / (root.pressed | root.pressAndHold ? 5 : 6)
                    anchors.rightMargin: parent.width / (root.pressed | root.pressAndHold ? 5 : 6)
                    rotation: root.pressed | root.pressAndHold ? (rotate ? 180 : 0) : 0
                    Behavior on rotation {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                    Behavior on anchors.bottomMargin {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    Behavior on anchors.topMargin {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    Behavior on anchors.leftMargin {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    Behavior on anchors.rightMargin {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    layer.enabled: true
                    layer.effect: DropShadow {
                        radius: root.pressed | root.pressAndHold ? 24 : 0
                        Behavior on radius {
                            NumberAnimation {
                                duration: 75
                            }
                        }
                        color: "#65e7ff"
                        samples: 25 /*20*/
                    }
                }
                //                DropShadow {
                //                    anchors.fill: iconArea
                //                    horizontalOffset: root.pressed | root.pressAndHold ? 0 : 4
                //                    verticalOffset: root.pressed | root.pressAndHold ? 0 : 2
                //                    radius: root.pressed | root.pressAndHold ? 0 : 8
                //                    Behavior on radius {
                //                        NumberAnimation {
                //                            duration: 250
                //                        }
                //                    }
                //                    Behavior on verticalOffset {
                //                        NumberAnimation {
                //                            duration: 100
                //                        }
                //                    }
                //                    Behavior on horizontalOffset {
                //                        NumberAnimation {
                //                            duration: 100
                //                        }
                //                    }
                //                    rotation: iconArea.rotation
                //                    samples: 25
                //                    color: Qt.lighter("#999999", 1.35)
                //                    source: iconArea
                //                }
            }
        }
    }
}
