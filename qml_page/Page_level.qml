import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_level"
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
                text: qsTr("调平")
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
            ColumnLayout {
                anchors.fill: parent
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 70
                    RowLayout {
                        anchors.fill: parent
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Switch_Button {
                                id: abl_btn
                                titleText: qsTr("自动调平")
                                anchors.fill: parent
                                anchors.topMargin: 5
                                anchors.bottomMargin: 5
                                checked: true
                                onReleased: {
                                    checked = true
                                    mbl_btn.checked = false
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Switch_Button {
                                id: mbl_btn
                                titleText: qsTr("手动调平")
                                anchors.fill: parent
                                anchors.topMargin: 5
                                anchors.bottomMargin: 5
                                onReleased: {
                                    checked = true
                                    abl_btn.checked = false
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                    }
                }
                Item {
                    //调平模式切换区域
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Mode_ABL {
                        anchors.fill: parent
                        active: abl_btn.checked
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
                            keyboard_page.keybroad_Reply.connect(
                                        receiver) //绑定键盘信号
                            keyboard_page.callKeybroad(currentText,
                                                       mode) //呼叫键盘实体
                        }
                        function receiver(outputdata, checkState) {
                            preheat_Std.keybroad_Reply(outputdata,
                                                       checkState) //传递键盘结果
                            keyboard_page.keybroad_Reply.disconnect(
                                        receiver) //解绑键盘信号
                        }
                        onCallProbeSet: probe_Set.active = true
                    }
                    Mode_MBL {
                        anchors.fill: parent
                        active: mbl_btn.checked
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
                }
            }
        }
    }
    Probe_Set {
        id: probe_Set
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
