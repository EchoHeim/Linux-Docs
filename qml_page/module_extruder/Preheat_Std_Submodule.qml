import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 200
    implicitHeight: 100
    property string name: "PLA" //耗材类型
    property color themeColor: "#101011"
    property int hotend: 200 //喷嘴温度
    property double dropShadowOffset: 0
    property double pressDarkFactor: 1.1
    background: Rectangle {
        id: visualTargrt
        anchors.fill: root
        border.color: "#65e7ff"
        color: root.pressed | root.pressAndHold ? Qt.darker(
                                                      themeColor,
                                                      pressDarkFactor) : themeColor
        Behavior on color {
            ColorAnimation {
                duration: 75
            }
        }
        anchors.margins: root.pressed | root.pressAndHold ? 7 : 5
        radius: 10
        Behavior on anchors.margins {
            NumberAnimation {
                duration: 75
            }
        }
        layer.enabled: true
        layer.effect: DropShadow {
            //            horizontalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
            //            Behavior on horizontalOffset {
            //                NumberAnimation {
            //                    duration: 75
            //                }
            //            }
            //            verticalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
            //            Behavior on verticalOffset {
            //                NumberAnimation {
            //                    duration: 75
            //                }
            //            }
            radius: !(root.pressed | root.pressAndHold) ? 0 : 24
            Behavior on radius {
                NumberAnimation {
                    duration: 75
                }
            }
            samples: 25
            color: "#65e7ff"
        }
        Label {
            text: root.name
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height / 3 * 2
            font.pixelSize: height / 3 * 2
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            color: "white"
        }
        Item {
            height: parent.height / 3
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            //            color: root.pressed | root.pressAndHold ? Qt.darker(
            //                                                          themeColor,
            //                                                          pressDarkFactor) : themeColor
            //            Behavior on color {
            //                ColorAnimation {
            //                    duration: 75
            //                }
            //            }
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
            //            radius: 10
            Item {
                anchors.fill: parent
                Item {
                    height: parent.height
                    anchors.centerIn: parent
                    width: height + hotend_label.contentWidth
                    Image {
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        height: parent.height - 8
                        width: height
                        source: "./title_hotend.svg"
                    }
                    Label {
                        id: hotend_label
                        height: parent.height - 4
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        font.pixelSize: height / 3 * 2
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        //                        fontSizeMode: Text.Fit
                        minimumPixelSize: 1
                        //                    anchors.horizontalCenter: visualTargrt.horizontalCenter
                        //                    anchors.bottom: visualTargrt.bottom
                        //                    width: visualTargrt.width - 4
                        //                    height: visualTargrt.height / 5 - 4
                        text: root.hotend + "℃"
                        color: "white"
                    }
                }
            }
        }
    }
}
