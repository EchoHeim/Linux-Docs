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
    property bool callKeybroad_doEvent: false
    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind
    property double probe_x: 0.8
    property double probe_y: 0.8
    property double probe_z: 0.8
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
    onCallKeybroad: {
        callKeybroad_doEvent = true
    }
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
            id: mouseArea
            enabled: root.active
            anchors.fill: parent
            //            onClicked: root.back()
        }
        //底色
        anchors.fill: parent
        color: "black"
        opacity: root.active ? (mouseArea.pressed ? 0.9 : 0.75) : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }
    Rectangle {
        width: parent.width
        height: parent.height
        radius: 30
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#101011"
        border.color: "#65e7ff"
        y: active ? height / 4 : height
        MouseArea {
            anchors.fill: parent
        }
        Behavior on y {
            NumberAnimation {
                duration: 250
            }
        }
        //实际内容
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
                        root.remind(notice_phrase.Save_Cancel[config.language],
                                    Common_RemindDialog.Mode.Tose)
                        root.back()
                    }
                }
                Label {
                    id: mylabel
                    height: parent.height
                    width: contentWidth
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "  " + qsTr("探针偏移量") + "  "
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
                        root.remind(notice_phrase.Save_Comfirm[config.language],
                                    Common_RemindDialog.Mode.Tose)
                        //                        M851
                        webSocket.sendScript(
                                    "M851 X" + root.probe_x + " Y"
                                    + root.probe_y + " Z" + root.probe_z)
                        root.back()
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
                    id: probe_x_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: probe_x_x.contentWidth + probe_x_value.contentWidth
                                           + probe_x_unit.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: probe_x_x
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "X"
                            //                    font.underline: true
                            font.pixelSize: probe_x_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: probe_x_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.probe_x + " "
                            font.underline: true
                            font.pixelSize: probe_x_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(
                                                root.probe_x,
                                                Common_Keyboard.Mode.Number)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.probe_x = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                        Label {
                            id: probe_x_unit
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "mm"
                            //                    font.underline: true
                            font.pixelSize: probe_x_item.height / 2
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
                    id: probe_y_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: probe_y_y.contentWidth + probe_y_value.contentWidth
                                           + probe_y_unit.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: probe_y_y
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "Y"
                            //                    font.underline: true
                            font.pixelSize: probe_y_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: probe_y_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.probe_y + " "
                            font.underline: true
                            font.pixelSize: probe_y_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(
                                                root.probe_y,
                                                Common_Keyboard.Mode.Number)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.probe_y = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                        Label {
                            id: probe_y_unit
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "mm"
                            //                    font.underline: true
                            font.pixelSize: probe_y_item.height / 2
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
                    id: probe_z_item
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: probe_z_z.contentWidth + probe_z_value.contentWidth
                                           + probe_z_unit.contentWidth
                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            id: probe_z_z
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "Z"
                            //                    font.underline: true
                            font.pixelSize: probe_z_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#65e7ff"
                        }
                        Label {
                            id: probe_z_value
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: " " + root.probe_z + " "
                            font.underline: true
                            font.pixelSize: probe_z_item.height / 2
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                            MouseArea {
                                anchors.fill: parent
                                onReleased: {
                                    root.keybroad_Reply.connect(receiver)
                                    root.callKeybroad(
                                                root.probe_z,
                                                Common_Keyboard.Mode.Number)
                                }
                                function receiver(outputdata, checkState) {
                                    if (checkState) {
                                        root.probe_z = outputdata
                                    }
                                    //传递键盘结果
                                    root.keybroad_Reply.disconnect(
                                                receiver) //解绑键盘信号
                                }
                            }
                        }
                        Label {
                            id: probe_z_unit
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth
                            text: "mm"
                            //                    font.underline: true
                            font.pixelSize: probe_z_item.height / 2
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
