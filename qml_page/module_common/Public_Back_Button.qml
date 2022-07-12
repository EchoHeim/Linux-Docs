import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Button {
    id: root
    implicitWidth: 100
    implicitHeight: 100
    //    property color themeColor: rgb(106, 194, 249)
    property alias titleImg: backImg.source //背景矢量图片
    property double dropShadowOffset: 0

    //    property double pressDarkFactor: 1.2
    //    function rgb(r, g, b) {
    //        var ret = (r << 16 | g << 8 | b)
    //        return ("#" + ret.toString(16)).toUpperCase()
    //    }
    background: Rectangle {
        color: "transparent"
        anchors.fill: root
        anchors.margins: root.pressed | root.pressAndHold ? 3 : 1
        Behavior on anchors.margins {
            NumberAnimation {
                duration: 75
            }
        }

        DropShadow {
            //            visible: false
            anchors.fill: backImg
            horizontalOffset: root.pressed | root.pressAndHold ? 0 : dropShadowOffset * 2
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
            source: backImg
        }

        Image {
            id: backImg
            source: "back.svg"
            sourceSize: Qt.size(parent.width, parent.height)
            //            smooth: true
            visible: true
        }
    }
}
