import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Slider {
    id: root
    implicitHeight: 20
    implicitWidth: 250
    stepSize: 1
    property color checkedColor: "#65e7ff"
    property string unit: "℃"
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }
    signal valueSet(var value)
    property int responseTime: 2000
    Timer {
        //触发设置
        id: tick
        running: false
        interval: root.responseTime
        repeat: false
        onTriggered: root.valueSet(root.value)
    }
    Component.onCompleted: {
        root.valueChanged.connect(function () {
            if (tick.running !== false)
                tick.restart()
            else
                tick.start()
        })
    }
    //    onValueSet: {
    //        console.debug(value)
    //    }
    //        onValueChanged: {
    //            if (tick.running !== false)
    //                tick.restart()
    //            else
    //                tick.start()
    //        }
    background: Rectangle {
        x: root.leftPadding
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 12
        width: root.availableWidth
        height: root.availableHeight / 5
        radius: height / 2
        color: "transparent"
        border.color: "white"

        Rectangle {
            width: root.visualPosition === 0 ? 0 : root.handle.x + root.handle.width / 2
            height: parent.height
            color: root.checkedColor
            radius: height / 2

            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                color: root.hovered | root.pressed ? root.checkedColor : "transparent"
                samples: root.hovered | root.pressed ? 12 : 0
                Behavior on color {
                    ColorAnimation {
                        duration: 250
                    }
                }
                Behavior on samples {
                    NumberAnimation {
                        duration: 250
                    }
                }
            }
        }
    }
    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight / 2 - height / 2
        color: root.pressed ? Qt.darker(root.checkedColor,
                                        1.2) : root.checkedColor
        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
        Behavior on x {
            NumberAnimation {
                duration: 50
            }
        }
        border.color: tick.running ? "gold" : "white"
        Behavior on border.color {
            ColorAnimation {
                duration: 150
            }
        }
        border.width: (height - root.availableHeight / 5) / 2
        implicitWidth: implicitHeight
        implicitHeight: root.availableHeight / 3
        radius: implicitHeight
        transformOrigin: Item.Center
        Label {
            text: root.value + root.unit
            anchors.bottom: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: root.availableHeight / 3
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            color: "white"
        }
    }
}
