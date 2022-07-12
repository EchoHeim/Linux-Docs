import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_move"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property int x_max: 200
    property int y_max: 200
    property int z_max: 200
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
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
            if (message.hasOwnProperty("result"))
                if (message.result.hasOwnProperty("status"))
                    if (message.result.status.hasOwnProperty("configfile")) {
                        z_max = message.result.status.configfile.config.stepper_z.position_max
                        y_max = message.result.status.configfile.config.stepper_y.position_max
                        x_max = message.result.status.configfile.config.stepper_x.position_max
                    }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            if (message.hasOwnProperty("result"))
                if (message.result.hasOwnProperty("status")) {
                    try {
                        superSlider_X.slider.value
                                = message.result.status.motion_report.live_position[0]
                    } catch (e1) {

                    }
                    try {
                        superSlider_Y.slider.value
                                = message.result.status.motion_report.live_position[1]
                    } catch (e2) {

                    }
                    try {
                        superSlider_Z.slider.value
                                = message.result.status.motion_report.live_position[2]
                    } catch (e3) {

                    }
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
        x: root.active ? 0 : root.width
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
                width: contentWidth + height * 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("移动")
                //                font.underline: true
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 1
                color: "#65e7ff"
            }
            Preview_Submodule {
                anchors.fill: parent
            }
        }
        Item {
            //页脚
            id: page_item
            width: parent.width - 20
            height: parent.height - 70 - 10
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 10
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Item {
                            Layout.fillWidth: true
                        }
                        Function_Button {
                            titleText: qsTr("全部归零")
                            suspension: ""
                            iconImg: "./module_move/home_0.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                webSocket.sendScript("G28")
                                superSlider_X.slider.value = superSlider_X.slider.from
                                superSlider_Y.slider.value = superSlider_Y.slider.from
                                superSlider_Z.slider.value = superSlider_Z.slider.from
                            }
                        }
                        Function_Button {
                            titleText: qsTr("电机解锁")
                            //                            suspension: "0"
                            iconImg: (!page_main.pos_int_X
                                      || !page_main.pos_int_Y
                                      || !page_main.pos_int_Z) ? "./module_move/unlock.svg" : "./module_move/unlock_Disable.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                if (!page_main.pos_int_X || !page_main.pos_int_Y
                                        || !page_main.pos_int_Z)
                                    webSocket.sendScript("M18")
                            }
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Function_Button {
                            suspension: ""
                            iconImg: "./module_move/home_X.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                webSocket.sendScript("G28 X")
                                superSlider_X.slider.value = superSlider_X.slider.from
                            }
                        }
                        SuperSlider {
                            id: superSlider_X
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            slider.from: 0
                            slider.to: x_max
                            slider.onValueSet: {
                                if (!page_main.pos_int_X)
                                    webSocket.sendScript("G28 X")

                                //                                console.debug("X" + ": " + value)
                                root.remind("X" + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                                webSocket.sendScript("G90")
                                webSocket.sendScript("G1 X" + value)
                            }
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Function_Button {
                            suspension: ""
                            iconImg: "./module_move/home_Y.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                webSocket.sendScript("G28 Y")
                                superSlider_Y.slider.value = superSlider_Y.slider.from
                            }
                        }
                        SuperSlider {
                            id: superSlider_Y
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            slider.from: 0
                            slider.to: y_max
                            slider.onValueSet: {
                                if (!page_main.pos_int_Y)
                                    webSocket.sendScript("G28 Y")

                                //                                console.debug("Y" + ": " + value)
                                root.remind("Y" + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                                webSocket.sendScript("G90")
                                webSocket.sendScript("G1 Y" + value)
                            }
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Function_Button {
                            suspension: ""
                            iconImg: "./module_move/home_Z.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                webSocket.sendScript("G28 Z")
                                superSlider_Z.slider.value = superSlider_Z.slider.from
                            }
                        }
                        SuperSlider {
                            id: superSlider_Z
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            slider.from: 0
                            slider.to: z_max
                            slider.onValueSet: {
                                if (!page_main.pos_int_Z)
                                    webSocket.sendScript("G28 Z")

                                //                                console.debug("Z" + ": " + value)
                                root.remind("Z" + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                                webSocket.sendScript("G90")
                                webSocket.sendScript("G1 Z" + value)
                            }
                        }
                    }
                }
            }
        }
    }
}
