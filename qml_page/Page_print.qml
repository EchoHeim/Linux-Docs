import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_print"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
        }
    }
    property string printer_state: "standby"
    //    "Idle"
    //    "Ready"
    //    "Printing"

    //    "standby"
    //    "printing"
    //    "paused"
    //    "complete"
    //    "cancelled"
    //    "error"
    Connections {
        target: webSocket
        onNewData: {
            if (message.method === "notify_status_update") {
                if (message.params[0].hasOwnProperty("idle_timeout")) {
                    if (message.params[0].idle_timeout.hasOwnProperty(
                                "state")) {
                        //    "Idle"
                        //    "Ready"
                        //    "Printing"
                        switch (message.params[0].idle_timeout.state) {
                        case "Idle":
                        case "Ready":
                            root.printer_state = "standby"
                            break
                        case "Printing":
                            root.printer_state = "printing"
                            break
                        }
                        return
                    } else if (message.params[0].idle_timeout.hasOwnProperty(
                                   "printing_time")) {
                        root.printer_state = "printing"
                        return
                    }
                }
                if (message.params[0].hasOwnProperty("print_stats")) {
//                    console.debug(JSON.stringify(message))
                    if (message.params[0].print_stats.hasOwnProperty("state"))
                        root.printer_state = message.params[0].print_stats.state
                    else if (message.params[0].print_stats.hasOwnProperty(
                                 "total_duration")) {
                        root.printer_state = "printing"
                    }
                    return
                }
                root.printer_state = "standby"
            }
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
                text: qsTr("文件列表")
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
            height: parent.height - 70 - 30
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 30
        }
        LocalList {
            id: localList
            anchors.fill: parent
            active: true
            onCallMenu: menu.show(currentPath, json)
        }
        Menu {
            id: menu
            anchors.fill: parent
            onCallDetail: detail.show(json)

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
        }
        Detail {
            id: detail
            anchors.fill: parent
        }
        Printing_preview {
            anchors.fill: parent
            onBack: root.back()
        }
    }
}
