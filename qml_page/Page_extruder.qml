import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_extruder"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    //    property alias hotend_target: slider_temp.value
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
            slider_temp.value = page_temperature.hotend_target
        }
    }
    signal back
    signal callKeybroad(var currentText, var mode)
    signal keybroad_Reply(var outputdata, var checkState)
    signal remind_Reply(var result)
    signal exitRemind
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
                text: qsTr("进退料")
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
                            Layout.fillHeight: true
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: height * 2
                            Function_Button {
                                anchors.fill: parent
                                anchors.margins: 10
                                iconImg: "./module_extruder/up.svg"
                                onClicked: {
                                    root.remind(notice_phrase.Suction[config.language],
                                                Common_RemindDialog.Mode.Tose)
                                    if (page_temperature.hotend_active
                                            < slider_temp.min_extrude_temp) {
                                        root.remind_Reply.connect(remind_Result)
                                        root.remind(notice_phrase.Suction_with_nozzle[config.language],
                                                    Common_RemindDialog.Mode.Comfirm)
                                    } else {
                                        webSocket.sendScript("G90")
                                        webSocket.sendScript(
                                                    "G1 E-" + slider_lenght.value
                                                    + " F" + slider_speed.value)
                                    }
                                }
                                function remind_Result(result) {
                                    preheat_Std.active = true //执行操作
                                    root.remind_Reply.disconnect(
                                                remind_Result) //解绑通知信号
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: height / 2
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: height * 2
                            Function_Button {
                                anchors.fill: parent
                                anchors.margins: 10
                                iconImg: "./module_extruder/down.svg"
                                onClicked: {
                                    root.remind(notice_phrase.Extrude[config.language],
                                                Common_RemindDialog.Mode.Tose)
                                    if (page_temperature.hotend_active
                                            < slider_temp.min_extrude_temp) {
                                        root.remind_Reply.connect(remind_Result)
                                        root.remind(notice_phrase.Extrude_with_nozzle[config.language],
                                                    Common_RemindDialog.Mode.Comfirm)
                                    } else {
                                        webSocket.sendScript("G90")
                                        webSocket.sendScript(
                                                    "G1 E" + slider_lenght.value
                                                    + " F" + slider_speed.value)
                                    }
                                }
                                function remind_Result(result) {
                                    preheat_Std.active = true //执行操作
                                    root.remind_Reply.disconnect(
                                                remind_Result) //解绑通知信号
                                }
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Label {
                            id: label_lenght
                            Layout.fillHeight: true
                            Layout.preferredWidth: label_lenght.contentWidth > label_speed.contentWidth ? (label_lenght.contentWidth > label_temp.contentWidth ? label_lenght.contentWidth : label_temp.contentWidth) : (label_speed.contentWidth > label_temp.contentWidth ? label_speed.contentWidth : label_temp.contentWidth)
                            text: "  " + qsTr("单位量") + "   "
                            font.pixelSize: parent.height / 3
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }
                        SliderBase {
                            id: slider_lenght
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            from: 0
                            to: 100
                            unit: "mm"
                            value: 10
                            onValueSet: {
//                                console.debug(label_lenght.text + ": " + value)
                                root.remind(label_lenght.text + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 40
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Label {
                            id: label_speed
                            Layout.fillHeight: true
                            Layout.preferredWidth: label_lenght.contentWidth > label_speed.contentWidth ? (label_lenght.contentWidth > label_temp.contentWidth ? label_lenght.contentWidth : label_temp.contentWidth) : (label_speed.contentWidth > label_temp.contentWidth ? label_speed.contentWidth : label_temp.contentWidth)
                            text: "  " + qsTr("速度") + "   "
                            font.pixelSize: parent.height / 3
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }
                        SliderBase {
                            id: slider_speed
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            from: 0
                            to: 100
                            unit: "mm/min"
                            value: 10
                            onValueSet: {
//                                console.debug(label_speed.text + ": " + value)
                                root.remind(label_speed.text + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                            }
                            Connections {
                                target: webSocket
                                onNewData: {
                                    if (message.hasOwnProperty("result"))
                                        if (message.result.hasOwnProperty(
                                                    "status"))
                                            if (message.result.status.hasOwnProperty(
                                                        "configfile")) {
                                                slider_speed.to = message.result.status.configfile.config.printer.max_velocity
                                            }
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 40
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    RowLayout {
                        anchors.fill: parent
                        Label {
                            id: label_temp
                            Layout.fillHeight: true
                            Layout.preferredWidth: label_lenght.contentWidth > label_speed.contentWidth ? (label_lenght.contentWidth > label_temp.contentWidth ? label_lenght.contentWidth : label_temp.contentWidth) : (label_speed.contentWidth > label_temp.contentWidth ? label_speed.contentWidth : label_temp.contentWidth)
                            text: "  " + qsTr("温度") + "   "
                            font.pixelSize: parent.height / 3
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }
                        SliderBase {
                            id: slider_temp
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            from: 0
                            to: 300
                            unit: "℃"
                            property var min_extrude_temp: 120
                            checkedColor: value < min_extrude_temp ? rgb(183,
                                                                         61,
                                                                         61) : rgb(
                                                                         106,
                                                                         194,
                                                                         249)
                            onValueSet: {
//                                console.debug(label_temp.text + ": " + value)
                                root.remind(label_temp.text + ": " + value,
                                            Common_RemindDialog.Mode.Tose)
                                webSocket.sendScript("M104 S" + value)
                            }
                            Component.onCompleted: {
                                preheat_Std.setTempperature.connect(
                                            function (hotend) {
                                                slider_temp.value = hotend
                                            })
                            }
                            Connections {
                                target: webSocket
                                onNewData: {
                                    if (message.hasOwnProperty("result"))
                                        if (message.result.hasOwnProperty(
                                                    "status"))
                                            if (message.result.status.hasOwnProperty(
                                                        "configfile")) {
                                                slider_temp.to = message.result.status.configfile.settings.extruder.max_temp
                                                slider_temp.from = message.result.status.configfile.settings.extruder.min_temp
                                                slider_temp.min_extrude_temp = message.result.status.configfile.settings.extruder.min_extrude_temp
                                            }
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 40
                        }
                    }
                }
            }
        }
    }
    Preheat_Std {
        id: preheat_Std
        anchors.fill: parent
        onRemind: {
            switch (mode) {
                //判断对话类型
            case Common_RemindDialog.Mode.Tose:
                break
            case Common_RemindDialog.Mode.Lock:
                break
            case Common_RemindDialog.Mode.Select:
            case Common_RemindDialog.Mode.Comfirm:
                root.remind_Reply.connect(remind_Result)
                break
            }
            root.remind(text, mode)
        }
        function remind_Result(result) {
            remind_Reply(result) //传递通知结果
            root.remind_Reply.disconnect(remind_Result) //解绑通知信号
        }
        onBack: {
            active = false
        }
        onCallKeybroad: {
            keyboard_page.keybroad_Reply.connect(receiver) //绑定键盘信号
            keyboard_page.callKeybroad(currentText, mode) //呼叫键盘实体
        }
        function receiver(outputdata, checkState) {
            keybroad_Reply(outputdata, checkState) //传递键盘结果
            keyboard_page.keybroad_Reply.disconnect(receiver) //解绑键盘信号
        }
    }
}
