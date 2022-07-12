import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtWebSockets 1.1
import "qml_page"
import "qml_page/module_common"

Window {
    visible: true
    width: 800
    height: 480
    title: qsTr("Bigtree TouchUI")
    property var config: JSON.parse(webSocket.readFile(
                                        "config/UserDefine.json"))
    property var notice_phrase: JSON.parse(webSocket.readFile(
                                               "config/Notice_phrase.json"))
    //    property string ipAddress: config.ipAddress
    property string token: "6PPP6KEZWZGR3NJXYOCHQFNPEGE6TSKQ"
    Component.onCompleted: {
        qmlLanguage.setLanguage(config.language)
    }

    ///自上而下层级递增，高层级绝对覆盖低层级

    ///数据处理层 -->首层具备数据向下传递能力

    ///引导层
    Page_main {
        //主页面板 -->呼叫其它页面
        id: page_main
        anchors.fill: parent
        onOpenPage: {
            if (active === false)
                //避免二次触发
                return
            active = false //取消主页激活，转移焦点
            if (pageName === "Page_console")
                page_console.active = true
            if (pageName === "Page_temperature")
                page_temperature.active = true
            if (pageName === "Page_fan")
                page_fan.active = true
            if (pageName === "Page_move")
                page_move.active = true
            if (pageName === "Page_extruder")
                page_extruder.active = true
            if (pageName === "Page_level")
                page_level.active = true
            if (pageName === "Page_camera")
                page_camera.active = true
            if (pageName === "Page_settings")
                page_settings.active = true
            if (pageName === "Page_print") {
                page_print.active = true
            }
        }
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
    }
    ///页面层
    Page_temperature {
        //温度面板
        id: page_temperature
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
            page_main.active = true
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
    Page_fan {
        //风扇面板
        id: page_fan
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
            page_main.active = true
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
    Page_move {
        //移动面板
        id: page_move
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
            page_main.active = true
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
    Page_extruder {
        //挤出机面板
        id: page_extruder
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
            page_main.active = true
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
    Page_level {
        //调平面板
        id: page_level
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
            page_main.active = true
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
    Page_camera {
        //摄像头面板
        id: page_camera
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
            page_main.active = true
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
    Page_settings {
        //设置面板
        id: page_settings
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
            page_main.active = true
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
    Page_print {
        //打印面板
        id: page_print
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
            page_main.active = true
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
    Page_console {
        //控制台面板
        id: page_console
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
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
            page_main.active = true
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
    ///键盘浮层
    Common_Keyboard {
        //键盘区域
        id: keyboard_page
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
    }
    ///弹窗浮层
    Common_RemindDialog {
        id: remind_dialog
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
    }
    //数据层
    WebSocket {
        id: webSocket
        url: "ws://" + config.ipAddress + "/websocket"
        active: false
        onTextMessageReceived: {
            //            console.debug(">>>\t" + message)
            //            console.debug()
            webSocket_server.restart()
            var data = JSON.parse(message)
            newData(data)
            if (data.hasOwnProperty("method"))
                if (data.method === "notify_klippy_disconnected") {
                    webSocket.active = false
                    webSocket_server.restart()
                }
        }
        onStatusChanged: {
//            console.debug("---status---\t" + status)
//            console.debug()
            if (status === WebSocket.Connecting) {
                webSocket_server.restart()
            }
            if (status === WebSocket.Open) {
                initialize()
                remind_dialog.exitRemind()
                webSocket_server.restart()
            } else {
                remind_dialog.exitRemind()
                remind_dialog.remind(
                            /*qsTr("Moonraker服务连接中...")*/ notice_phrase.Moonraker_reconnect[config.language],
                            Common_RemindDialog.Mode.Lock)
            }
        }
        signal newData(var message)
        function initialize() {
            var data = JSON.parse(
                        readFile(
                            "moonraker/Websocket/Initialize/Initialize.json"))
            for (var initialize in data.initialize) {
                webSocket.sendTextMessage(JSON.stringify(
                                              data.initialize[initialize]))
            }
        }
        function readFile(path) {
            var request = new XMLHttpRequest()
            request.open("GET", path, false) // false为同步操作设置
            request.send(null)
            //            console.debug(path + " >>> Read : " + request.responseText)
            return request.responseText
        }
        function writeFile(path, text) {
            var request = new XMLHttpRequest()
            request.open("PUT", path, true) // false为同步操作设置
            request.send(text)
            return request.status
        }
        function sendScript(gcodeScript) {
            var data = JSON.parse(
                        webSocket.readFile(
                            "moonraker/API/printer/gcode/post_script_request_rpc.json"))
            data.params.script = gcodeScript
            webSocket.sendTextMessage(JSON.stringify(data))
        }
        Component.onCompleted: {
            if (token !== "")
                url = Qt.binding(function () {
                    return "ws://" + config.ipAddress + "/websocket?token=" + token
                })
            else
                url = Qt.binding(function () {
                    return "ws://" + config.ipAddress + "/websocket"
                })
            webSocket.active = true
        }
    }
    Timer {
        id: webSocket_server
        //测试：通讯控制定时器
        running: false
        interval: 2500
        repeat: false
        onTriggered: {
            webSocket.active = false
            webSocket.active = true
        }
    }
    //测试层
}
