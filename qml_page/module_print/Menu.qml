import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    signal remind(var text, var mode)
    signal exitRemind
    signal remind_Reply(var result)
    signal callDetail(var json)
    property bool active: false
    signal back
    signal show(var currentPath, var json)
    onShow: {
        itemPath = currentPath
        itemJson = json
        active = true
    }
    property string itemPath: "gcodes"
    property var itemJson: {
        "modified": 1615578004.9639666,
        "size": 7300692,
        "filename": "Funnel_0.2mm_PLA_Ender2_2h4m.gcode",
        "dirname": "thumbs"
    }
    onBack: {
        active = false
    }
    enabled: active
    //    opacity: active ? 1 : 0
    //    Behavior on opacity {
    //        NumberAnimation {
    //            id: root_opacity
    //            duration: 150
    //        }
    //    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            //            root.active = !root.active
            root.back()
        }
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: root.active ? 0.75 : 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 150
                }
            }
        }
        Rectangle {
            id: reference
            width: 100
            height: parent.height - 130
            color: "#191414"
            opacity: 1
            radius: 5
            //            border.color: "black"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.rightMargin: root.active ? 10 : -width
            Behavior on anchors.rightMargin {
                NumberAnimation {
                    id: root_opacity
                    duration: 150
                }
            }
        }
        ColumnLayout {
            width: reference.width - 10
            height: reference.height - 10
            anchors.centerIn: reference
            spacing: 0
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Function_Button {
                iconImg: "./print.svg"
                Layout.fillWidth: true
                Layout.preferredHeight: width
                property var jsonId: 1323
                onClicked: {
                    root.remind_Reply.connect(remind_Result)
                    root.remind(notice_phrase.Print_Model[config.language]
                                + " :" + itemJson.filename + "?",
                                Common_RemindDialog.Mode.Select)
                }
                function remind_Result(result) {
                    if (result === Common_RemindDialog.Key.Yes) {
                        var data = JSON.parse(
                                    webSocket.readFile(
                                        "moonraker/API/printer/print/post_start_request_rpc.json"))
                        var tree = root.itemPath.split("/")
                        tree.shift()
                        tree.push(itemJson.filename)
                        data.params.filename = tree.join("/")
                        jsonId = data.id
                        webSocket.sendTextMessage(JSON.stringify(data))
                        //执行操作
                        root.remind_Reply.disconnect(remind_Result) //解绑通知信号
                        root.back()
                    }
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
                iconImg: "./delete.svg"
                Layout.fillWidth: true
                Layout.preferredHeight: width
                property var jsonId: 1323
                onClicked: {
                    root.remind_Reply.connect(remind_Result)
                    root.remind(notice_phrase.Print_Delete[config.language]
                                + ": " + itemJson.filename + "?",
                                Common_RemindDialog.Mode.Select)
                }
                function remind_Result(result) {
                    if (result === Common_RemindDialog.Key.Yes) {
                        var data = JSON.parse(
                                    webSocket.readFile(
                                        "moonraker/API/server/files/delete_file_request_rpc.json"))
                        var tree = root.itemPath.split("/")
                        tree.push(itemJson.filename)
                        data.params.path = tree.join("/")
                        jsonId = data.id
                        webSocket.sendTextMessage(JSON.stringify(data))
                        //执行操作
                        root.remind_Reply.disconnect(remind_Result) //解绑通知信号
                        root.back()
                    }
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
                iconImg: "./info.svg"
                Layout.fillWidth: true
                Layout.preferredHeight: width
                onClicked: root.callDetail(root.itemJson)
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
