import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../"

Item {
    id: root
    implicitHeight: 70
    implicitWidth: 800

    property string preheat_name: "PLA"
    property double preheat_hotend: 200
    property double preheat_heatbed: 60
    property bool isTop: false
    property bool light: false
    property bool canDelete: true

    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind

    signal callSubEditor

    //    signal subEditorReply(var _preheat_name, var _preheat_hotend, var _preheat_heatbed)

    //    onSubEditorReply: {
    //        root.preheat_name = _preheat_name
    //        root.preheat_hotend = _preheat_hotend
    //        root.preheat_heatbed = _preheat_heatbed
    //    }
    signal moveToTop

    signal removeSubmodule

    Rectangle {
        width: parent.width - 10
        height: parent.height - 10
        radius: 10
        color: "#101011"
        anchors.centerIn: parent
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 12
            samples: 25
            color: Qt.lighter(light ? "#65e7ff" : "transparent", 1.35)
        }
        Rectangle {
            id: unit_item
            width: parent.width
            height: parent.height
            radius: parent.radius
            anchors.centerIn: parent
            color: parent.color
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: unit_item.width
                    height: unit_item.height
                    radius: unit_item.radius
                }
            }
            border.color: root.light ? "#65e7ff" : "white"
            Behavior on border.color {
                ColorAnimation {
                    duration: 250
                }
            }
            RowLayout {
                spacing: 0
                anchors.fill: parent
                Function_Button {
                    iconImg: canDelete ? "./delete.svg" : "./delete_Disable.svg"
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    onClicked: {
                        if (!canDelete)
                            return
                        root.remind_Reply.connect(remind_Result)
                        root.remind(notice_phrase.Delete[config.language]
                                    + root.preheat_name + "?",
                                    Common_RemindDialog.Mode.Select)
                    }
                    function remind_Result(result) {
                        root.remind_Reply.disconnect(remind_Result) //解绑通知信号
                        if (result === Common_RemindDialog.Key.Yes)
                            root.removeSubmodule() //执行操作
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: " " + root.preheat_name + " "
                    font.underline: true
                    font.bold: true
                    color: "white"
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: notice_phrase.Nozzle[config.language]
                    color: "#65e7ff"
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: " " + root.preheat_hotend + " "
                    font.underline: true
                    font.bold: true
                    color: "white"
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "℃"
                    color: "#65e7ff"
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: notice_phrase.Hotbed[config.language]
                    color: "#65e7ff"
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: " " + root.preheat_heatbed + " "
                    font.underline: true
                    font.bold: true
                    color: "white"
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "℃"
                    color: "#65e7ff"
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Function_Button {
                    iconImg: "./editor.svg"
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    onClicked: root.callSubEditor(root.preheat_name,
                                                  root.preheat_hotend,
                                                  root.preheat_heatbed)
                }
                Function_Button {
                    //                    enabled: !root.isTop
                    iconImg: root.isTop ? "./moveTop_Disable.svg" : "./moveTop.svg"
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    onClicked: {
                        if (!root.isTop)
                            root.moveToTop()
                    }
                }
            }
        }
    }
}
