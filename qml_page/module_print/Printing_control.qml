import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
//具有公共抬头组件
import "../module_common"
import "../"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property int speed_factor: 0
    property int extrude_factor: 0
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    onActiveChanged: {
        if (active) {
            slider_heatbed.value = page_temperature.heatbed_target
            slider_hotend.value = page_temperature.hotend_target
            slider_fan.value = page_fan.currentSpeed
            slider_flow.value = extrude_factor
            slider_speed.value = speed_factor
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                if (message.method === "notify_status_update") {
                    try {
                        if (message.params[0].gcode_move.hasOwnProperty(
                                    "speed_factor"))
                            root.speed_factor = Number(
                                        ((message.params[0].gcode_move.speed_factor) * 100).toFixed(
                                            0))
                    } catch (e1) {

                    }
                    try {
                        if (message.params[0].gcode_move.hasOwnProperty(
                                    "extrude_factor"))
                            root.extrude_factor = Number(
                                        ((message.params[0].gcode_move.extrude_factor)
                                         * 100).toFixed(0))
                    } catch (e2) {

                    }
                }
            } catch (e) {

            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                if (message.result.status.hasOwnProperty("gcode_move")) {
                    try {
                        root.speed_factor = Number(
                                    ((message.result.status.gcode_move.speed_factor) * 100).toFixed(
                                        0))
                    } catch (e1) {

                    }
                    try {
                        root.extrude_factor = Number(
                                    ((message.result.status.gcode_move.extrude_factor)
                                     * 100).toFixed(0))
                    } catch (e2) {

                    }
                }
            } catch (e) {

            }
        }
    }
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
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height
        x: root.active ? 0 : root.width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
        color: "#2a2424"
        MouseArea {
            enabled: root.active
            anchors.fill: parent
        }
        Item {
            //页眉
            id: page_title
            height: 70
            width: parent.width
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
                id: mylabel
                height: contentHeight + 20
                width: contentWidth + height * 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: notice_phrase.Print_Parameters_Setting[config.language]
                //                font.underline: true
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
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
            GridLayout {
                anchors.fill: parent
                anchors.margins: 10
                rows: 5
                columns: 4
                rowSpacing: 0
                columnSpacing: 0
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
                Image {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./printing_icon_speed.svg"
                }
                HorizontalSlider {
                    id: slider_speed
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 200
                    unit: "%"
                    value: 25
                    onValueSet: {
                        root.remind(notice_phrase.Print_Preview_Speed[config.language]
                                    + ": " + value + unit,
                                    Common_RemindDialog.Mode.Tose)
                        webSocket.sendScript("M220 S" + value)
                    }
                }
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }

                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
                Image {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./printing_icon_rate.svg"
                }
                HorizontalSlider {
                    id: slider_flow
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 200
                    unit: "%"
                    value: 25
                    onValueSet: {
                        root.remind(notice_phrase.Print_Preview_Rate_Flow[config.language]
                                    + ": " + value + unit,
                                    Common_RemindDialog.Mode.Tose)
                        webSocket.sendScript("M221 S" + value)
                    }
                }
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }

                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
                Image {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./fan.svg"
                }
                HorizontalSlider {
                    id: slider_fan
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 100
                    unit: "%"
                    value: 25
                    onValueChanged: {
                        page_fan.fanSet.value = (2.55 * value).toFixed(0)
                    }
                }
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }

                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
                Image {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./print.svg"
                }
                HorizontalSlider {
                    id: slider_hotend
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 100
                    unit: "℃"
                    onValueSet: {
                        root.remind(notice_phrase.Nozzle[config.language] + ": " + value + unit,
                                    Common_RemindDialog.Mode.Tose)
                        webSocket.sendScript("M104 S" + value)
                    }
                    Connections {
                        target: webSocket
                        onNewData: {
                            if (message.hasOwnProperty("result"))
                                if (message.result.hasOwnProperty("status"))
                                    if (message.result.status.hasOwnProperty(
                                                "configfile")) {
                                        slider_hotend.to = message.result.status.configfile.config.extruder.max_temp
                                        slider_hotend.from = message.result.status.configfile.config.extruder.min_temp
                                    }
                        }
                    }
                }
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }

                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
                Image {
                    Layout.preferredWidth: 50
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./temperature.svg"
                }
                HorizontalSlider {
                    id: slider_heatbed
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 100
                    unit: "℃"
                    onValueSet: {
                        root.remind(notice_phrase.Hotbed[config.language] + ": " + value + unit,
                                    Common_RemindDialog.Mode.Tose)
                        webSocket.sendScript("M140 S" + value)
                    }
                    Connections {
                        target: webSocket
                        onNewData: {
                            if (message.hasOwnProperty("result"))
                                if (message.result.hasOwnProperty("status"))
                                    if (message.result.status.hasOwnProperty(
                                                "configfile")) {
                                        slider_heatbed.to = message.result.status.configfile.config.heater_bed.max_temp
                                        slider_heatbed.from = message.result.status.configfile.config.heater_bed.min_temp
                                    }
                        }
                    }
                }
                Item {
                    Layout.preferredWidth: 80
                    Layout.fillHeight: true
                }
            }
        }
    }
}
