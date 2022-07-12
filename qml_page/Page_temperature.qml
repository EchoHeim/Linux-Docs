import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_temperature"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    //    property alias metadata: preheat_Custom.metadata
    property double hotend_target: 180
    property double hotend_active: 120
    property double heatbed_target: 60
    property double heatbed_active: 25
    property alias preheatData: preheat_Custom.preheatData
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    signal update
    onUpdate: {
        preheat_Std.update()
    }
    onActiveChanged: {
        if (active) {
            hotend_slider.slider.value = root.hotend_target
            heatbed_slider.slider.value = root.heatbed_target
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            if (message.method === "notify_status_update") {
                try {
                    root.hotend_active = message.params[0].extruder.temperature.toFixed(
                                1)
                } catch (e1) {

                }
                try {
                    root.hotend_target = message.params[0].extruder.target.toFixed(
                                1)
                } catch (e3) {

                }
                try {
                    root.heatbed_active = message.params[0].heater_bed.temperature.toFixed(
                                1)
                } catch (e2) {

                }
                try {
                    root.heatbed_target = message.params[0].heater_bed.target.toFixed(
                                1)
                } catch (e4) {

                }
            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                root.hotend_active = message.result.status.extruder.temperature.toFixed(
                            1)
            } catch (e1) {

            }
            try {
                root.hotend_target = message.result.status.extruder.target.toFixed(
                            1)
            } catch (e3) {

            }
            try {
                root.heatbed_active = message.result.status.heater_bed.temperature.toFixed(
                            1)
            } catch (e2) {

            }
            try {
                root.heatbed_target = message.result.status.heater_bed.target.toFixed(
                            1)
            } catch (e4) {

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
                text: qsTr("温度")
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
        }
        //页面内容
        ColumnLayout {
            id: page_item
            width: parent.width - 20
            height: parent.height - 100
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            //            anchors.fill: parent
            //            anchors.topMargin: 70
            anchors.bottomMargin: 30
            //            anchors.leftMargin: 10
            //            anchors.rightMargin: 10
            spacing: 0
            Item {
                Layout.preferredHeight: page_item.height / 4
                Layout.fillWidth: true
                RowLayout {
                    anchors.fill: parent
                    //                    anchors.leftMargin: 10
                    //                    anchors.rightMargin: 10
                    Item {
                        Layout.fillWidth: true
                    }
                    Function_Button {
                        titleText: qsTr("冷却")
                        iconImg: "./module_temperature/cooldown.svg"
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        onClicked: {
                            hotend_slider.slider.value = hotend_slider.slider.from
                            heatbed_slider.slider.value = heatbed_slider.slider.from
                        }
                    }
                    Function_Button {
                        titleText: qsTr("预热")
                        iconImg: "./module_temperature/preheat.svg"
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        onClicked: preheat_Std.active = true
                    }
                }
            }
            Item {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    Image {
                        Layout.preferredWidth: 25
                        Layout.preferredHeight: 25
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        source: "./module_temperature/title_hotend.svg"
                    }
                    Label {
                        text: root.hotend_active
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                    }
                    Label {
                        text: "/"
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#65e7ff"
                    }
                    Label {
                        text: root.hotend_target
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#65e7ff"
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
            Item {
                Layout.preferredHeight: 5
                Layout.fillWidth: true
            }
            SuperSlider {
                id: hotend_slider
                Layout.preferredHeight: (page_item.height / 4 * 3 / 2) - 40
                Layout.fillWidth: true
                slider.checkedColor: "#65e7ff"
                slider.unit: "℃"
                slider.from: 0
                slider.to: 300
                slider.value: 120
                slider.stepSize: 1
                slider.onValueSet: {
                    //                    console.debug(qsTr("喷嘴") + ": " + value)
                    root.remind(notice_phrase.Nozzle[config.language] + ": " + value + slider.unit,
                                Common_RemindDialog.Mode.Tose)
                    webSocket.sendScript("M104 S" + slider.value)
                    //                    page_extruder.hotend_target = value
                }
                Component.onCompleted: {
                    preheat_Std.setTempperature.connect(
                                function (hotend, heatbed) {
                                    slider.value = hotend
                                })
                }
                Connections {
                    target: webSocket
                    onNewData: {
                        if (message.hasOwnProperty("result"))
                            if (message.result.hasOwnProperty("status"))
                                if (message.result.status.hasOwnProperty(
                                            "configfile")) {
                                    hotend_slider.slider.to = message.result.status.configfile.config.extruder.max_temp
                                    hotend_slider.slider.from = message.result.status.configfile.config.extruder.min_temp
                                }
                    }
                }
            }
            Item {
                Layout.preferredHeight: 10
                Layout.fillWidth: true
            }
            Item {
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    Image {
                        Layout.preferredWidth: 25
                        Layout.preferredHeight: 25
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        source: "./module_temperature/title_heatbed.svg"
                    }
                    Label {
                        text: root.heatbed_active
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                    }
                    Label {
                        text: "/"
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#65e7ff"
                    }
                    Label {
                        text: root.heatbed_target
                        Layout.fillHeight: true
                        font.pixelSize: parent.height - 5
                        minimumPixelSize: 1
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: "#65e7ff"
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
            Item {
                Layout.preferredHeight: 5
                Layout.fillWidth: true
            }
            SuperSlider {
                id: heatbed_slider
                Layout.preferredHeight: (page_item.height / 4 * 3 / 2) - 40
                Layout.fillWidth: true
                slider.checkedColor: "#65e7ff"
                slider.unit: "℃"
                slider.from: 0
                slider.to: 120
                slider.value: 50
                slider.stepSize: 1
                slider.onValueSet: {
//                    console.debug(qsTr("热床") + ": " + value)
                    root.remind(notice_phrase.Hotbed[config.language] + ": " + value + slider.unit,
                                Common_RemindDialog.Mode.Tose)
                    webSocket.sendScript("M140 S" + slider.value)
                }
                Component.onCompleted: {
                    preheat_Std.setTempperature.connect(
                                function (hotend, heatbed) {
                                    slider.value = heatbed
                                })
                }
                Connections {
                    target: webSocket
                    onNewData: {
                        if (message.hasOwnProperty("result"))
                            if (message.result.hasOwnProperty("status"))
                                if (message.result.status.hasOwnProperty(
                                            "configfile")) {
                                    heatbed_slider.slider.to = message.result.status.configfile.config.heater_bed.max_temp
                                    heatbed_slider.slider.from = message.result.status.configfile.config.heater_bed.min_temp
                                }
                    }
                }
            }
        }
    }
    Preheat_Std {
        id: preheat_Std
        anchors.fill: parent
        metadata: root.preheatData
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
        onCallKeybroad: {
            keyboard_page.keybroad_Reply.connect(receiver) //绑定键盘信号
            keyboard_page.callKeybroad(currentText, mode) //呼叫键盘实体
        }
        function receiver(outputdata, checkState) {
            keybroad_Reply(outputdata, checkState) //传递键盘结果
            keyboard_page.keybroad_Reply.disconnect(receiver) //解绑键盘信号
        }
        onCallCustomEditor: preheat_Custom.active = true
    }
    Preheat_Custom {
        id: preheat_Custom
        anchors.fill: parent
        onBack: root.update()
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
