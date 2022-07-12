import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import "../module_common"
import "../"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    //测试源数据
    //    property alias preheatData: listView.json
    signal remind(var text, var mode)
    enabled: active
    //    visible: active
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
        }
    }
    property alias preheatData: listView.json
    opacity: active ? 1 : 0
    signal back
    signal callKeybroad(var currentText, var mode)
    signal remind_Reply(var result)
    signal exitRemind
    signal keybroad_Reply(var outputdata, var checkState)

    onBack: {
        root.active = false
        webSocket.writeFile("config/Preheat_Custom.json",
                            JSON.stringify(root.preheatData))
    }
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
    Rectangle {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: root.active ? 0 : root.height
        color: "#101011"
        onYChanged: {
            if (y === 0) {
                root_opacity.duration = 1500
            } else if (y === root.height) {
                root_opacity.duration = 150
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: 250
            }
        }

        Item {
            width: parent.width - 10
            height: parent.height - 120
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 50
            ListView {
                id: listView
                anchors.fill: parent
                orientation: ListView.Vertical
                clip: true
                model: listModel
                delegate: listDel

                move: Transition {
                    NumberAnimation {
                        properties: "x,y"
                        duration: 500
                        easing.type: Easing.InOutExpo
                    }
                }
                property var json: JSON.parse(webSocket.readFile(
                                                  "config/Preheat_Custom.json"))
                Component.onCompleted: {
                    for (var data in root.preheatData.preheatlist) {
                        listModel.append({
                                             "inputJson": root.preheatData.preheatlist[data]
                                         })
                    }
                }
            }
            Component {
                id: listDel
                Preheat_Custom_Submodule {
                    width: listView.width
                    height: 70
                    preheat_name: inputJson.preheat_name
                    preheat_hotend: inputJson.preheat_hotend
                    preheat_heatbed: inputJson.preheat_heatbed
                    isTop: index === 0
                    light: index < 6
                    canDelete: listModel.count > 6
                    onMoveToTop: {
                        root.preheatData.preheatlist.splice(
                                    0, 0, root.preheatData.preheatlist[index])
                        root.preheatData.preheatlist.splice(index + 1, 1)
                        //                        console.debug(
                        //                                    root.preheatData.preheatlist[0].preheat_name)
                        listModel.move(index, 0, 1)
                    }
                    onRemoveSubmodule: {
                        root.preheatData.preheatlist.splice(index, 1)
                        listModel.remove(index)
                    }
                    onCallSubEditor: {
                        preheat_Custom_Editor.back.connect(receiver)
                        preheat_Custom_Editor.editor(preheat_name,
                                                     preheat_hotend,
                                                     preheat_heatbed)
                    }
                    function receiver(tag) {
                        if (tag) {
                            preheat_name = preheat_Custom_Editor.preheat_name
                            preheat_hotend = preheat_Custom_Editor.preheat_hotend
                            preheat_heatbed = preheat_Custom_Editor.preheat_heatbed

                            root.preheatData.preheatlist.splice(index, 1, {
                                                                    "preheat_name": preheat_Custom_Editor.preheat_name,
                                                                    "preheat_hotend": preheat_Custom_Editor.preheat_hotend,
                                                                    "preheat_heatbed": preheat_Custom_Editor.preheat_heatbed
                                                                })
                        }
                        //传递结果
                        preheat_Custom_Editor.back.disconnect(receiver) //解绑信号
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
                            root.remind_Reply.connect(remind_Result)
                            break
                        }
                        root.remind(text, mode)
                    }
                    function remind_Result(result) {
                        remind_Reply(result) //传递通知结果
                        root.remind_Reply.disconnect(remind_Result) //解绑通知信号
                    }

                    Component.onCompleted: {

                        //                        console.debug(JSON.stringify(inputJson))
                    }
                }
            }
            ListModel {
                id: listModel
            }
        }
        Rectangle {
            //页眉
            height: 70
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#101011"
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
                text: qsTr("预定义预热选项")
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
            layer.enabled: true
            layer.effect: DropShadow {
                radius: 24
                samples: 25
                color: Qt.darker("#65e7ff", 1.5)
            }
        }
        Rectangle {
            width: parent.width
            height: 50
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            layer.enabled: true
            color: "#101011"
            layer.effect: DropShadow {
                radius: 24
                samples: 25
                color: Qt.darker("#65e7ff", 1.5)
            }
            Rectangle {
                height: 1
                width: parent.width
                anchors.top: parent.top
                color: "#65e7ff"
            }
            Function_Button {
                iconImg: "./add_Item.svg"
                width: parent.width - 10
                height: parent.height
                anchors.centerIn: parent
                onClicked: {
                    preheat_Custom_Editor.back.connect(receiver)
                    preheat_Custom_Editor.editor("", 200, 60)
                }
                function receiver(tag) {
                    if (tag) {
                        listModel.insert(0, {
                                             "inputJson": {
                                                 "preheat_name": preheat_Custom_Editor.preheat_name,
                                                 "preheat_hotend": preheat_Custom_Editor.preheat_hotend,
                                                 "preheat_heatbed": preheat_Custom_Editor.preheat_heatbed
                                             }
                                         })
                        root.preheatData.preheatlist.splice(0, 0, listModel.get(
                                                                0).inputJson)
                    }
                    //传递结果
                    preheat_Custom_Editor.back.disconnect(receiver) //解绑信号
                }
            }
        }
    }
    Preheat_Custom_Editor {
        id: preheat_Custom_Editor
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
