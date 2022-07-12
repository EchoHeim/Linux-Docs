import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    property color themeColor: "#101011"
    property alias titleImg: titleArea.source //标题文字矢量图片
    property alias titleText: titleLabel.text //标题文字内容
    property alias fontColor: titleLabel.color
    property alias fontFamily: titleLabel.font.family
    property double dropShadowOffset: 0
    property double pressDarkFactor: 1.2
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }

    background: Item {
        anchors.fill: root
        //        color: "transparent"
        anchors.margins: root.pressed | root.pressAndHold ? 7 : 5
        Behavior on anchors.margins {
            NumberAnimation {
                duration: 75
            }
        }
        Rectangle {
            //阴影效果
            id: visualTargrtShadow
            anchors.fill: parent
            color: "#65e7ff"
            z: 0
            radius: 15
            //            visible: false
            layer.enabled: true
            layer.effect: DropShadow {
                id: dropShadow
                anchors.fill: visualTargrtShadow
                //                horizontalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset
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
                radius: !(root.pressed | root.pressAndHold) ? 0 : 24
                Behavior on radius {
                    NumberAnimation {
                        duration: 75
                    }
                }
                samples: 25
                color: "#65e7ff"
                source: visualTargrtShadow
                z: 0
            }
        }
        Rectangle {
            id: visualTargrt
            anchors.fill: parent
            color: root.pressed | root.pressAndHold ? Qt.darker(
                                                          themeColor,
                                                          pressDarkFactor) : themeColor
            border.color: "#65e7ff"
            z: 1
            //            border.color: root.pressed | root.pressAndHold ? "#999999" : "transparent"
            //            Behavior on border.color {
            //                ColorAnimation {
            //                    duration: 75
            //                }
            //            }
            radius: 15
            clip: true

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    //                    anchors.fill: visualTargrt
                    //                    anchors.centerIn: visualTargrt
                    radius: visualTargrt.radius

                    implicitWidth: visualTargrt.implicitWidth
                    implicitHeight: visualTargrt.implicitHeight
                    width: visualTargrt.width
                    height: visualTargrt.height
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 75
                }
            }
            Rectangle {
                //图文显示区域
                id: textArea
                width: parent.width - 4
                height: parent.height - 4
                anchors.centerIn: parent
                color: "transparent"
                clip: true

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
                    font.pixelSize: height / 2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 1
                    color: "white"
                    //                    anchors.horizontalCenter: visualTargrt.horizontalCenter
                    //                    anchors.bottom: visualTargrt.bottom
                    //                    width: visualTargrt.width - 4
                    //                    height: visualTargrt.height / 5 - 4
                    text: qsTr("确认")
                    opacity: text.length <= 0 ? 0 : (titleArea.status !== Image.Null ? 0 : 1)
                }
            }
        }
    }
}
