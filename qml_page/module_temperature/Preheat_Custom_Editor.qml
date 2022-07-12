import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind

    signal editor(var _preheat_name, var _preheat_hotend, var _preheat_heatbed)
    onEditor: {
        preheat_name = _preheat_name
        preheat_hotend = _preheat_hotend
        preheat_heatbed = _preheat_heatbed
        active = true
    }

    property string preheat_name: "PLA"
    property double preheat_hotend: 200
    property double preheat_heatbed: 60

    //    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation {
            id: root_opacity
            duration: 150
        }
    }
    signal back(var tag)
    signal callKeybroad(var currentText, var mode)
    signal keybroad_Reply(var outputdata, var checkState)
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }
    onBack: {
        active = false
    }
    Rectangle {
        MouseArea {
            id: stopArea
            enabled: root.active
            anchors.fill: parent
            //            onClicked: root.back()
        }
        //底色
        anchors.fill: parent
        color: "black"
        opacity: root.active ? (stopArea.pressed ? 0.9 : 0.75) : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }
    Rectangle {
        width: parent.width
        height: parent.height
        border.color: "#65e7ff"
        radius: 30
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#101011"
        y: active ? height / 4 : height
        Behavior on y {
            NumberAnimation {
                duration: 250
            }
        }
        MouseArea {
            anchors.fill: parent
        }
        Item {
            anchors.fill: parent
            anchors.bottomMargin: parent.height / 4
            Item {
                //页眉
                height: 60
                width: parent.width
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                Function_Button {
                    iconImg: "./cancel.svg"
                    width: height
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    onClicked: {
                        root.back(false)
                        root.remind(notice_phrase.Save_Cancel[config.language],
                                    Common_RemindDialog.Mode.Tose)
                    }
                }
                Label {
                    id: mylabel
                    height: parent.height
                    width: contentWidth
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "  " + qsTr("预热值修改") + "  "
                    //                    font.underline: true
                    font.pixelSize: height / 2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
                Function_Button {
                    iconImg: "./checkmark.svg"
                    width: height
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    onClicked: {
                        root.back(true)
                        root.remind(notice_phrase.Save_Comfirm[config.language],
                                    Common_RemindDialog.Mode.Tose)
                    }
                }
            }
            RowLayout {
                spacing: 0
                anchors.fill: parent
                anchors.topMargin: 70
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                anchors.bottomMargin: 20

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    id: preheat_name_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: preheat_name_title.contentWidth
                                           + preheat_name_value.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: preheat_name_title
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: qsTr("名称")
                            //                    font.underline: true
                            font.pixelSize: preheat_name_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: preheat_name_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.preheat_name + " "
                            font.underline: true
                            font.pixelSize: preheat_name_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(root.preheat_name,
                                                      Common_Keyboard.Mode.ALL)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.preheat_name = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    id: preheat_hotend_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: preheat_hotend_title.contentWidth
                                           + preheat_hotend_value.contentWidth
                                           + preheat_hotend_unit.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: preheat_hotend_title
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: qsTr("喷嘴")
                            //                    font.underline: true
                            font.pixelSize: preheat_hotend_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: preheat_hotend_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.preheat_hotend + " "
                            font.underline: true
                            font.pixelSize: preheat_hotend_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(
                                                root.preheat_hotend,
                                                Common_Keyboard.Mode.Number)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.preheat_hotend = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                        Label {
                            id: preheat_hotend_unit
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "℃"
                            //                    font.underline: true
                            font.pixelSize: preheat_hotend_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    id: preheat_heatbed_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: preheat_heatbed_title.contentWidth
                                           + preheat_heatbed_value.contentWidth
                                           + preheat_heatbed_unit.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: preheat_heatbed_title
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: qsTr("热床")
                            //                    font.underline: true
                            font.pixelSize: preheat_heatbed_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: preheat_heatbed_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.preheat_heatbed + " "
                            font.underline: true
                            font.pixelSize: preheat_heatbed_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(
                                                root.preheat_heatbed,
                                                Common_Keyboard.Mode.Number)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.preheat_heatbed = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                        Label {
                            id: preheat_heatbed_unit
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "℃"
                            //                    font.underline: true
                            font.pixelSize: preheat_heatbed_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }
}
