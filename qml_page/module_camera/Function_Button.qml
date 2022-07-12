import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property alias titleImg: titleArea.source //标题文字矢量图片
    property alias titleText: titleLabel.text //标题文字内容
    property alias iconImg: iconArea.source //整体图标文件
    property double dropShadowOffset: 0
    property bool rotate: false

    background: Rectangle {
        color: "transparent"
        anchors.fill: root
        anchors.margins: 1
        Item {
            //文本显示区域
            id: textArea
            width: parent.width - 4
            height: parent.height / 5 - 4
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 2
            anchors.bottom: parent.bottom
            opacity: titleArea.opacity === 0 && titleLabel.opacity === 0 ? 0 : 1
            Image {
                id: titleArea
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                opacity: status === Image.Null ? 0 : 1
            }
            Label {
                id: titleLabel
                anchors.fill: parent
                font.pixelSize: height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit
                minimumPixelSize: 1
                font.bold: true
                opacity: text.length <= 0 ? 0 : (titleArea.status !== Image.Null ? 0 : 1)
            }
        }
        Item {
            //图标显示区域
            anchors.fill: parent
            anchors.bottomMargin: textArea.opacity
                                  === 0 ? (root.checked | root.pressed
                                           | root.pressAndHold ? 4 : 2) : parent.height
                                          / 5 + (root.checked | root.pressed
                                                 | root.pressAndHold ? 4 : 2)
            anchors.topMargin: root.checked | root.pressed | root.pressAndHold ? 4 : 2
            anchors.leftMargin: root.checked | root.pressed | root.pressAndHold ? 4 : 2
            anchors.rightMargin: root.checked | root.pressed | root.pressAndHold ? 4 : 2
            Behavior on anchors.bottomMargin {
                NumberAnimation {
                    duration: 250
                }
            }
            Behavior on anchors.topMargin {
                NumberAnimation {
                    duration: 250
                }
            }
            Behavior on anchors.leftMargin {
                NumberAnimation {
                    duration: 250
                }
            }
            Behavior on anchors.rightMargin {
                NumberAnimation {
                    duration: 250
                }
            }
            Image {
                id: iconArea
                source: "cooldown.svg"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                anchors.bottomMargin: parent.height / 6
                anchors.topMargin: parent.height / 6
                anchors.leftMargin: parent.width / 6
                anchors.rightMargin: parent.width / 6
                rotation: root.checked | root.pressed | root.pressAndHold ? (rotate ? 180 : 0) : 0
                Behavior on rotation {
                    NumberAnimation {
                        duration: 250
                    }
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    radius: !(root.pressed | root.pressAndHold) ? 0 : 24
                    Behavior on radius {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    samples: 25
                    color: "#65e7ff"
                }
                Rectangle {
                    width: parent.width
                    height: 1
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: root.checked ? "gray" : "transparent"
                    Behavior on color {
                        ColorAnimation {
                            duration: 250
                        }
                    }
                }
                //                Rectangle {
                //                    width: 1
                //                    height: parent.height
                //                    anchors.right: parent.right
                //                    anchors.verticalCenter: parent.verticalCenter
                //                    color: root.checked ? "gray" : "transparent"
                //                    Behavior on color {
                //                        ColorAnimation {
                //                            duration: 250
                //                        }
                //                    }
                //                }
            }
        }
    }
}
