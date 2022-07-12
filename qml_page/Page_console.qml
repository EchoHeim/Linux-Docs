import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtWebSockets 1.1
import "module_console"
//具有公共抬头组件
import "module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property alias msg: msg_viewer.text
    signal remind(var text, var mode)
    enabled: active
    //    visible: active
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
        }
    }
    opacity: active ? 1 : 0
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
    Rectangle {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: root.active ? 0 : root.height
        onYChanged: {
            if (y === 0) {
                console_Input.focus = true
                root_opacity.duration = 1500
            } else if (y === height) {
                root_opacity.duration = 150
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: 250
            }
        }

        //        color: root.rgb(236, 236, 236)
        color: "#2a2424"

        Rectangle {
            //页眉
            height: 70
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            Flickable {
                anchors.fill: parent
                contentHeight: 10
                contentWidth: 10
                onVerticalVelocityChanged: {
                    if (verticalVelocity < -500)
                        root.back()
                }
            }

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
                text: qsTr("控制台")
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
        }
        ScrollView {
            id: scroll_area
            height: parent.height - 150
            width: parent.width - 10
            anchors.centerIn: parent
            //            border.color: "black"
            //            color: "transparent"
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AsNeeded
            ScrollBar.vertical.interactive: true
            ScrollBar.vertical.width: 30
            property bool autoScroll: true //自动滚动标记
            //            background: Rectangle {
            //                anchors.fill: parent
            //                color: "transparent"
            //                border.color: "transparent"
            //                //                radius: 5
            //            }
            contentWidth: width - ScrollBar.vertical.width

            function checkAutoScroll() {
                if (scroll_area.contentHeigh <= scroll_area.contentItem.height)
                    scroll_area.autoScroll = true
                else
                    scroll_area.autoScroll = (scroll_area.contentItem.contentY
                                              >= scroll_area.contentHeight
                                              - scroll_area.contentItem.height)
            }
            Text {
                id: msg_viewer
                font.pixelSize: 30
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                anchors.fill: parent
                text: ""
                wrapMode: Text.WrapAnywhere
                color: "white"
                onTextChanged: {
                    if (scroll_area.autoScroll)
                        //自动滚动功能
                        scroll_area.contentItem.contentY = scroll_area.contentHeight
                                - scroll_area.contentItem.height
                }
                Connections {
                    target: webSocket
                    onNewData: {
                        if (message.hasOwnProperty("result"))
                            if (message.result.hasOwnProperty("gcode_store")) {
                                for (var gcode_store in message.result.gcode_store) {
                                    msg_viewer.text += message.result.gcode_store[gcode_store].message + "\n"
                                }
                            }
                    }
                }
                Connections {
                    target: webSocket
                    onNewData: {
                        if (message.method === "notify_gcode_response") {
                            for (var gcode_store in message.params) {
                                msg_viewer.text += message.params[gcode_store] + "\n"
                            }
                        }
                    }
                }
                Connections {
                    target: webSocket
                    onStatusChanged: {
                        if (webSocket.status === WebSocket.Open) {
                            msg_viewer.text = ""
                        }
                    }
                }
            }
        }
        Rectangle {
            //页脚
            height: 60
            width: parent.width - 10
            anchors.bottomMargin: 5
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"
            Console_Input {
                id: console_Input
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - height * 2
                height: parent.height
                font.pixelSize: height / 2
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                onCallKeybroad: //呼叫键盘，currentText为传递文本
                {
                    root.keybroad_Reply.connect(receiver)
                    root.callKeybroad(currentText, Common_Keyboard.Mode.ALL)
                }
                function receiver(outputdata, checkState) {
                    if (checkState) {
                        console_Input.text = outputdata
                    }
                    console_Input.focus = true
                    //传递键盘结果
                    root.keybroad_Reply.disconnect(receiver) //解绑键盘信号
                }
            }
            Sender_Button {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: height * 2
                height: parent.height
                onClicked: {
                    scroll_area.checkAutoScroll()
                    //                    msg_viewer.text += "\n" + console_Input.text + "<<<"
                    msg_viewer.text += console_Input.text + "\n"
                    webSocket.sendScript(console_Input.text)
                    //                    root.remind("未连接打印机!", Common_RemindDialog.Mode.Tose)
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:800}
}
##^##*/

