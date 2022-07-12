import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property alias titleImg: titleArea.source //标题文字矢量图片
    property alias titleText: titleLabel.text //标题文字内容
    property alias suspension: suspensionText.text //浮动文字内容
    property alias iconImg: iconArea.source //整体图标文件
    property double dropShadowOffset: 0
    property bool rotate: false
    property bool shadowEnalble: true

    background: Rectangle {
        color: "transparent"
        anchors.fill: root
        anchors.margins: 1
        Item {
            //文本显示区域
            id: textArea
            width: parent.width
            height: parent.height / 5
            anchors.horizontalCenter: parent.horizontalCenter
            //            anchors.bottomMargin: 2
            anchors.bottom: parent.bottom
            opacity: titleArea.opacity === 0 && titleLabel.opacity === 0 ? 0 : 1
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
                font.pixelSize: height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit
                minimumPixelSize: 1
                font.bold: true
                color: "white"
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
            anchors.bottomMargin: textArea.opacity
                                  === 0 ? (root.pressed | root.pressAndHold ? 2 : 0) : parent.height
                                          / 5 + (root.pressed | root.pressAndHold ? 2 : 0)
            anchors.topMargin: root.pressed | root.pressAndHold ? 2 : 0
            anchors.leftMargin: root.pressed | root.pressAndHold ? 2 : 0
            anchors.rightMargin: root.pressed | root.pressAndHold ? 2 : 0
            //            DropShadow {
            //                anchors.fill: iconArea
            //                horizontalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset * 2
            //                Behavior on horizontalOffset {
            //                    NumberAnimation {
            //                        duration: 75
            //                    }
            //                }
            //                verticalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
            //                Behavior on verticalOffset {
            //                    NumberAnimation {
            //                        duration: 75
            //                    }
            //                }
            //                radius: root.pressed | root.pressAndHold ? 0 : 8
            //                Behavior on radius {
            //                    NumberAnimation {
            //                        duration: 75
            //                    }
            //                }
            //                samples: 25
            //                color: Qt.lighter("#999999", 1.35)
            //                source: iconArea
            //            }
            Image {
                id: iconArea
                source: "cooldown.svg"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                //                anchors.bottomMargin: parent.height / 6
                //                anchors.topMargin: parent.height / 6
                //                anchors.leftMargin: parent.width / 6
                //                anchors.rightMargin: parent.width / 6
                rotation: root.pressed | root.pressAndHold ? (rotate ? 180 : 0) : 0
                Behavior on rotation {
                    NumberAnimation {
                        duration: 250
                    }
                }

                layer.enabled: shadowEnalble
                layer.effect: DropShadow {
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
                    radius: !(root.pressed | root.pressAndHold) ? 0 : 24
                    Behavior on radius {
                        NumberAnimation {
                            duration: 75
                        }
                    }
                    samples: 25
                    color: "#65e7ff"
                }
            }
            Label {
                id: suspensionText
                anchors.fill: iconArea
                font.pixelSize: height / 3 * 2
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                fontSizeMode: Text.Fit
                minimumPixelSize: 1
                color: "white"
                font.bold: true
                //                layer.enabled: shadowEnalble
                //                layer.effect: DropShadow {
                //                    horizontalOffset: dropShadowOffset
                //                    verticalOffset: dropShadowOffset
                //                    radius: 8
                //                    samples: 25
                //                    color: Qt.darker("#999999", 1.35)
                //                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "gray"
            opacity: root.enabled ? 0 : 0.8
            Behavior on opacity {
                NumberAnimation {
                    duration: 75
                }
            }
        }
    }
}
