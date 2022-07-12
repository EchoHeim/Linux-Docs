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

    property bool active: page_print.printer_state === "printing"
                          || page_print.printer_state === "paused"
    //    property bool active: true
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
            try {
                if (message.hasOwnProperty("result")) {
                    objNameLabel.text = message.result.jobs[0].filename
                }
            } catch (e) {

            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                if (message.method === "notify_status_update") {
                    try {
                        if (message.params[0].display_status.hasOwnProperty(
                                    "progress"))
                            progressBar.value = message.params[0].display_status.progress
                    } catch (e1) {

                    }
                    try {
                        if (message.params[0].print_stats.hasOwnProperty(
                                    "filament_used"))
                            length.text = (message.params[0].print_stats.filament_used
                                           / 1000).toFixed(2) + "mm"
                    } catch (e2) {

                    }
                }
            } catch (e) {

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
        //铺垫元素
        Item {
            anchors.fill: parent
            Rectangle {
                //右侧边栏
                id: reference
                width: 150
                height: parent.height - 10
                color: "#191414"
                radius: 30
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: -width / 3
                ColumnLayout {
                    width: parent.width / 3 * 2 - 10
                    height: parent.height - 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 0
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Function_Button {
                        iconImg: "./printing_menu_zStep.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: {
                            printing_zStep.active = true
                        }
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Rectangle {
                            height: 1
                            width: parent.width / 3 * 2
                            anchors.centerIn: parent
                            color: "#65e7ff"
                        }
                    }
                    Function_Button {
                        iconImg: "./printing_menu_adj.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: {
                            printing_control.active = true
                        }
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Rectangle {
                            height: 1
                            width: parent.width / 3 * 2
                            anchors.centerIn: parent
                            color: "#65e7ff"
                        }
                    }
                    Function_Button {
                        iconImg: "./printing_menu_cam.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: {
                            printing_camera.active = true
                        }
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Rectangle {
                            height: 1
                            width: parent.width / 3 * 2
                            anchors.centerIn: parent
                            color: "#65e7ff"
                        }
                    }
                    Function_Button {
                        iconImg: page_print.printer_state === "printing" ? "./printing_menu_pause.svg" : "./printing_menu_resume.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: {
                            json_Data = JSON.parse(
                                        webSocket.readFile(
                                            page_print.printer_state === "printing" ? "moonraker/API/printer/print/post_pause_request_rpc.json" : "moonraker/API/printer/print/post_resume_reques_rpc.json"))
                            //                            console.debug(JSON.stringify(json_Data))
                            webSocket.sendTextMessage(JSON.stringify(json_Data))
                        }
                        property var json_Data
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Rectangle {
                            height: 1
                            width: parent.width / 3 * 2
                            anchors.centerIn: parent
                            color: "#65e7ff"
                        }
                    }
                    Function_Button {
                        iconImg: "./printing_menu_stop.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: webSocket.sendTextMessage(JSON.stringify(
                                                                 json_Data))
                        property var json_Data: JSON.parse(
                                                    webSocket.readFile(
                                                        "moonraker/API/printer/print/post_cancel_request_rpc.json"))
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Rectangle {
                            height: 1
                            width: parent.width / 3 * 2
                            anchors.centerIn: parent
                            color: "#65e7ff"
                        }
                    }
                    Function_Button {
                        iconImg: "./printing_menu_extruder.svg"
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 3 * 2
                        onClicked: {
                            printing_extruder.active = true
                        }
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
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
            Coordinate_view_panel {
                id: coordinate_view_panel
                anchors.fill: parent
            }
        }
        Item {
            //页脚
            id: page_item
            width: parent.width - 20 - reference.width / 3 * 2
            height: parent.height - 70 - 30
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottomMargin: 30
            GridLayout {
                id: panel
                anchors.fill: parent
                rows: 3
                columns: 4
                rowSpacing: 10
                columnSpacing: 0
                Item {
                    id: object_item
                    Layout.rowSpan: 3
                    Layout.preferredWidth: panel.width / 4
                    Layout.fillHeight: true
                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 0
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: width
                            Image {
                                id: iconArea
                                source: "./printing_icon_object.svg"
                                anchors.fill: parent
                                anchors.margins: 20
                                fillMode: Image.PreserveAspectFit
                                horizontalAlignment: Image.AlignHCenter
                                verticalAlignment: Image.AlignVCenter
                            }
                        }
                        Item {
                            //                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: objNameLabel.contentHeight
                            Label {
                                id: objNameLabel
                                font.pixelSize: 15
                                width: parent.width
                                height: contentHeight
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Cube"
                                wrapMode: Text.WrapAnywhere
                                color: "white"
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                    }
                }
                Item {
                    Layout.columnSpan: 3
                    Layout.preferredWidth: panel.width / 4 * 3
                    Layout.fillHeight: true
                    Rectangle {
                        anchors.fill: parent
                        radius: 10
                        color: "transparent"
                        border.color: "#65e7ff"
                        RowLayout {
                            anchors.fill: parent
                            spacing: 0
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: 10
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                ColumnLayout {
                                    anchors.fill: parent
                                    spacing: 0
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                    Item {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: width - 80
                                        Image {
                                            source: "./printing_icon_progress.svg"
                                            anchors.fill: parent
                                            fillMode: Image.PreserveAspectFit
                                            horizontalAlignment: Image.AlignHCenter
                                            verticalAlignment: Image.AlignVCenter
                                            layer.enabled: true
                                            layer.effect: DropShadow {
                                                radius: 8
                                                samples: 25
                                                color: "#65e7ff"
                                            }
                                        }
                                    }
                                    Item {
                                        //                            Layout.fillHeight: true
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: progressLabel.contentHeight
                                        Label {
                                            id: progressLabel
                                            font.pixelSize: 20
                                            width: parent.width
                                            height: contentHeight
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                            text: notice_phrase.Print_Preview_Progress[config.language]
                                            //                                            text: "Progress"
                                            wrapMode: Text.WrapAnywhere
                                            color: "white"
                                        }
                                    }
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: 20
                            }
                            Item {
                                //进度时间
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                Label {
                                    font.pixelSize: 30
                                    width: parent.width
                                    height: contentHeight
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: (progressBar.value * 100).toFixed(
                                              0) + "%"
                                    wrapMode: Text.WrapAnywhere
                                    color: "white"
                                    anchors.bottom: progressBar.top
                                    anchors.bottomMargin: 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                                Label {
                                    font.pixelSize: 20
                                    width: contentWidth
                                    height: contentHeight
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: "0:30:12"
                                    wrapMode: Text.WrapAnywhere
                                    color: "white"
                                    anchors.top: progressBar.bottom
                                    anchors.topMargin: 2
                                    anchors.left: progressBar.left
                                    visible: false
                                }
                                Label {
                                    font.pixelSize: 20
                                    width: contentWidth
                                    height: contentHeight
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: "1:00:30"
                                    wrapMode: Text.WrapAnywhere
                                    color: "white"
                                    anchors.top: progressBar.bottom
                                    anchors.topMargin: 2
                                    anchors.right: progressBar.right
                                    visible: false
                                }
                                ProgressBar {
                                    id: progressBar
                                    width: parent.width
                                    height: 20
                                    anchors.centerIn: parent
                                    //                                    value: 0.7
                                    background: Rectangle {
                                        id: progressBar_Rectangle
                                        implicitWidth: 200
                                        implicitHeight: 12
                                        color: "#2a2424"
                                        radius: height
                                        border.color: "white"
                                    }
                                    contentItem: Item {
                                        implicitWidth: progressBar.background.implicitWidth
                                        implicitHeight: progressBar.background.implicitHeight
                                        Rectangle {
                                            width: progressBar.visualPosition * parent.width - 2
                                            height: parent.height - 2
                                            color: "#65e7ff"
                                            radius: height
                                            anchors.left: parent.left
                                            anchors.leftMargin: 1
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                        layer.enabled: true
                                        layer.effect: OpacityMask {
                                            maskSource: progressBar_Rectangle
                                        }
                                    }
                                }
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: 10
                            }
                        }
                    }
                }

                Item {
                    Layout.columnSpan: 3
                    Layout.preferredWidth: panel.width / 4 * 3
                    Layout.fillHeight: true
                    Rectangle {
                        anchors.fill: parent
                        radius: 10
                        color: "transparent"
                        border.color: "#65e7ff"
                        RowLayout {
                            anchors.fill: parent
                            spacing: 0
                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    spacing: 0
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                    Item {
                                        Layout.preferredHeight: (parent.height - 20) / 3 * 2
                                        Layout.fillWidth: true
                                        RowLayout {
                                            anchors.fill: parent
                                            spacing: 0
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                            Image {
                                                Layout.preferredHeight: parent.height / 3 * 2
                                                Layout.preferredWidth: height
                                                source: "./printing_icon_speed.svg"
                                                fillMode: Image.PreserveAspectFit
                                                horizontalAlignment: Image.AlignHCenter
                                                verticalAlignment: Image.AlignVCenter
                                                layer.enabled: true
                                                layer.effect: DropShadow {
                                                    radius: 8
                                                    samples: 25
                                                    color: "#65e7ff"
                                                }
                                            }
                                            Label {
                                                Layout.fillHeight: true
                                                Layout.preferredWidth: contentWidth
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                                font.pixelSize: parent.height / 3
                                                text: notice_phrase.Print_Preview_Speed[config.language]
                                                color: "white"
                                            }
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }
                                    Label {
                                        Layout.preferredHeight: (parent.height - 20) / 3
                                        Layout.fillWidth: true
                                        font.pixelSize: height / 5 * 4
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        text: printing_control.speed_factor + "%"
                                        wrapMode: Text.WrapAnywhere
                                        color: "#65e7ff"
                                    }
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    spacing: 0
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                    Item {
                                        Layout.preferredHeight: (parent.height - 20) / 3 * 2
                                        Layout.fillWidth: true
                                        RowLayout {
                                            anchors.fill: parent
                                            spacing: 0
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                            Image {
                                                Layout.preferredHeight: parent.height / 3 * 2
                                                Layout.preferredWidth: height
                                                source: "./printing_icon_length.svg"
                                                fillMode: Image.PreserveAspectFit
                                                horizontalAlignment: Image.AlignHCenter
                                                verticalAlignment: Image.AlignVCenter
                                                layer.enabled: true
                                                layer.effect: DropShadow {
                                                    radius: 8
                                                    samples: 25
                                                    color: "#65e7ff"
                                                }
                                            }
                                            Label {
                                                Layout.fillHeight: true
                                                Layout.preferredWidth: contentWidth
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                                font.pixelSize: parent.height / 3
                                                text: notice_phrase.Print_Preview_Wire[config.language]
                                                color: "white"
                                            }
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }
                                    Label {
                                        id: length
                                        Layout.preferredHeight: (parent.height - 20) / 3
                                        Layout.fillWidth: true
                                        font.pixelSize: height / 5 * 4
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        text: "100mm"
                                        wrapMode: Text.WrapAnywhere
                                        color: "#65e7ff"
                                    }
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                        }
                    }
                }

                Item {
                    Layout.columnSpan: 3
                    Layout.preferredWidth: panel.width / 4 * 3
                    Layout.fillHeight: true
                    Rectangle {
                        anchors.fill: parent
                        radius: 10
                        color: "transparent"
                        border.color: "#65e7ff"
                        RowLayout {
                            anchors.fill: parent
                            spacing: 0
                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    spacing: 0
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                    Item {
                                        Layout.preferredHeight: (parent.height - 20) / 3 * 2
                                        Layout.fillWidth: true
                                        RowLayout {
                                            anchors.fill: parent
                                            spacing: 0
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                            Image {
                                                Layout.preferredHeight: parent.height / 3 * 2
                                                Layout.preferredWidth: height
                                                source: "./printing_icon_rate.svg"
                                                fillMode: Image.PreserveAspectFit
                                                horizontalAlignment: Image.AlignHCenter
                                                verticalAlignment: Image.AlignVCenter
                                                layer.enabled: true
                                                layer.effect: DropShadow {
                                                    radius: 8
                                                    samples: 25
                                                    color: "#65e7ff"
                                                }
                                            }
                                            Label {
                                                Layout.fillHeight: true
                                                Layout.preferredWidth: contentWidth
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                                font.pixelSize: parent.height / 3
                                                text: notice_phrase.Print_Preview_Rate_Flow[config.language]
                                                color: "white"
                                            }
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }
                                    Label {
                                        Layout.preferredHeight: (parent.height - 20) / 3
                                        Layout.fillWidth: true
                                        font.pixelSize: height / 5 * 4
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        text: printing_control.extrude_factor + "%"
                                        wrapMode: Text.WrapAnywhere
                                        color: "#65e7ff"
                                    }
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    spacing: 0
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                    Item {
                                        Layout.preferredHeight: (parent.height - 20) / 3 * 2
                                        Layout.fillWidth: true
                                        RowLayout {
                                            anchors.fill: parent
                                            spacing: 0
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                            Image {
                                                Layout.preferredHeight: parent.height / 3 * 2
                                                Layout.preferredWidth: height
                                                source: "./printing_icon_height.svg"
                                                fillMode: Image.PreserveAspectFit
                                                horizontalAlignment: Image.AlignHCenter
                                                verticalAlignment: Image.AlignVCenter
                                                layer.enabled: true
                                                layer.effect: DropShadow {
                                                    radius: 8
                                                    samples: 25
                                                    color: "#65e7ff"
                                                }
                                            }
                                            Label {
                                                Layout.fillHeight: true
                                                Layout.preferredWidth: contentWidth
                                                horizontalAlignment: Text.AlignHCenter
                                                verticalAlignment: Text.AlignVCenter
                                                font.pixelSize: parent.height / 3
                                                text: notice_phrase.Print_Preview_Thickness[config.language]
                                                color: "white"
                                            }
                                            Item {
                                                Layout.fillHeight: true
                                                Layout.fillWidth: true
                                            }
                                        }
                                    }
                                    Label {
                                        Layout.preferredHeight: (parent.height - 20) / 3
                                        Layout.fillWidth: true
                                        font.pixelSize: height / 5 * 4
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        text: "Null"
                                        wrapMode: Text.WrapAnywhere
                                        color: "#65e7ff"
                                    }
                                    Item {
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Page_extruder {
            //挤出机面板
            id: printing_extruder
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
                    remind_dialog.output.connect(remind_Result)
                    break
                }
                remind_dialog.remind(text, mode)
            }
            function remind_Result(result) {
                remind_Reply(result) //传递通知结果
                remind_dialog.output.disconnect(remind_Result) //解绑通知信号
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
        Printing_control {
            //挤出机面板
            id: printing_control
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
                    remind_dialog.output.connect(remind_Result)
                    break
                }
                remind_dialog.remind(text, mode)
            }
            function remind_Result(result) {
                remind_Reply(result) //传递通知结果
                remind_dialog.output.disconnect(remind_Result) //解绑通知信号
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
        Printing_camera {
            //摄像头面板
            id: printing_camera
            //        width: parent.width
            //        height: parent.height
            //        anchors.verticalCenter: parent.verticalCenter
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
                    remind_dialog.output.connect(remind_Result)
                    break
                }
                remind_dialog.remind(text, mode)
            }
            function remind_Result(result) {
                remind_Reply(result) //传递通知结果
                remind_dialog.output.disconnect(remind_Result) //解绑通知信号
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
        Printing_zStep {
            //摄像头面板
            id: printing_zStep
            //        width: parent.width
            //        height: parent.height
            //        anchors.verticalCenter: parent.verticalCenter
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
                    remind_dialog.output.connect(remind_Result)
                    break
                }
                remind_dialog.remind(text, mode)
            }
            function remind_Result(result) {
                remind_Reply(result) //传递通知结果
                remind_dialog.output.disconnect(remind_Result) //解绑通知信号
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
}
