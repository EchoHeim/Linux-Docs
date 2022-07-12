import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_fan"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property alias fanSpeed: slider.dispValue
    property alias fanSet: slider
    property int currentSpeed: 0
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
        }
    }
    onActiveChanged: {
        if (active) {
            slider.value = (2.55 * currentSpeed).toFixed(0)
        }
    }
    signal back
    signal callKeybroad(var currentText, var mode)
    signal remind_Reply(var result)
    signal exitRemind
    signal keybroad_Reply(var outputdata, var checkState)
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }
    Connections {
        target: webSocket
        onNewData: {
            if (message.method === "notify_status_update") {
                try {
                    root.currentSpeed = ((message.params[0].fan.speed) * 100).toFixed(
                                0)
                } catch (e1) {

                }
            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                root.currentSpeed = ((message.result.status.fan.speed) * 100).toFixed(
                            0)
            } catch (e1) {

            }
        }
    }
    Rectangle {
        //遮蔽层
        anchors.fill: parent
        color: "black"
        opacity: root.active ? 0.8 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
        MouseArea {
            enabled: root.active
            anchors.fill: parent
        }
    }
    //页面主体
    Rectangle {
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        x: active ? 0 : width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
        color: "#2a2424"
        Item {
            //页眉
            height: 70
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            Public_Back_Button {
                height: 47
                width: 47
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                onClicked: root.back()
            }
            Label {
                Trapezoidal {
                    anchors.fill: parent
                    //                    anchors.topMargin: 5
                    //                    anchors.bottomMargin: 5
                }
                id: mylabel
                height: contentHeight + 20
                width: contentWidth + height * 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("风扇")
                //                font.underline: true
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }
            Preview_Submodule {
                anchors.fill: parent
            }
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 1
                color: "#65e7ff"
            }
        }
        Item {
            //页脚
            id: page_item
            width: parent.width
            height: parent.height - 70 - 30
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 30
            Rectangle {
                width: parent.width - 40
                height: parent.height / 2
                anchors.centerIn: parent
                radius: 10
                color: "#2a2424"
                border.color: "#65e7ff"
                SliderBase {
                    id: slider
                    height: parent.height / 3 * 2 - 5
                    width: parent.width - 100
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    checkedColor: "#65e7ff"
                    unit: "%"
                    from: 0
                    to: 255
                    value: 80
                    stepSize: 1
                    onValueSet: {
                        //                        console.debug(
                        //                                    notice_phrase.Fan_speed[config.language] + ": " + value)
                        root.remind(notice_phrase.Fan_speed[config.language]
                                    + ": " + dispValue + unit,
                                    Common_RemindDialog.Mode.Tose)
                        webSocket.sendScript("M106 S" + value)
                    }
                    Connections {
                        target: webSocket
                        onNewData: {
                            if (message.hasOwnProperty("result"))
                                if (message.result.hasOwnProperty("status"))
                                    if (message.result.status.hasOwnProperty(
                                                "fan")) {
                                        slider.value = (message.result.status.fan.speed
                                                        * 255).toFixed(0)
                                    }
                        }
                    }
                    Connections {
                        target: webSocket
                        onNewData: {
                            try {
                                if (message.method === "notify_status_update") {
                                    slider.value = (message.params[0].fan.speed * 255).toFixed(
                                                0)
                                }
                            } catch (e) {

                            }
                        }
                    }
                }
                Rectangle {
                    height: 1
                    color: "#65e7ff"
                    width: parent.width - 100
                    anchors.top: parent.top
                    anchors.topMargin: parent.height / 3 * 2
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                RowLayout {
                    id: rowLayout
                    height: parent.height / 3 - 1
                    width: parent.width - 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    spacing: 0
                    Function_Button {
                        iconImg: "./module_fan/fan_close.svg"
                        Layout.fillHeight: true
                        Layout.preferredWidth: height
                        onClicked: slider.value = slider.from
                    }
                    Item {
                        Layout.preferredWidth: (rowLayout.width - 3 * rowLayout.height) / 2
                        Layout.fillHeight: true
                    }
                    Function_Button {
                        iconImg: "./module_fan/fan_half.svg"
                        Layout.fillHeight: true
                        Layout.preferredWidth: height
                        rotate: true
                        onClicked: slider.value = ((slider.to - slider.from) / 2)
                    }
                    Item {
                        Layout.preferredWidth: (rowLayout.width - 3 * rowLayout.height) / 2
                        Layout.fillHeight: true
                    }
                    Function_Button {
                        iconImg: "./module_fan/fan_full.svg"
                        Layout.fillHeight: true
                        Layout.preferredWidth: height
                        rotate: true
                        onClicked: slider.value = ((slider.to - slider.from) / 1)
                    }
                }
                layer.enabled: false
                layer.effect: DropShadow {
                    //                    horizontalOffset: 2
                    //                    verticalOffset: 2
                    radius: 12
                    samples: 25
                    color: "#65e7ff"
                }
            }
        }
    }
}
