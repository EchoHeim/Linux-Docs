import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../"

Item {
    id: root
    implicitHeight: 70
    implicitWidth: 800

    //    property string item_name: "测试样例"
    property int item_type: Submodule.ItemType.File
    property var item_json: {
        "modified": 1615768162.0412788,
        "size": 4096,
        "dirname": "test",
        "filename": "CE2_Pi3_A+_CaseLID.gcode"
    }

    property bool selected: false

    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind

    signal callMenu(var json)
    signal goFolder(var path)

    signal moveToTop

    signal removeSubmodule
    enum ItemType {
        File = 0,
        Folder = 1
    }
    Rectangle {
        width: parent.width - 10
        height: parent.height - 10
        radius: 10
        anchors.centerIn: parent
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 12
            samples: 25
            color: (subMouse.pressed | subMouse.pressAndHold
                    | root.selected) ? "#65e7ff" : "#2a2424"
        }
        Rectangle {
            id: unit_item
            width: parent.width
            height: parent.height
            radius: parent.radius
            anchors.centerIn: parent
            color: (subMouse.pressed | subMouse.pressAndHold
                    | root.selected) ? "#41a8e3" : "#2a2424"
            Behavior on color {
                ColorAnimation {
                    duration: 250
                }
            }

            border.color: "#65e7ff"
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: unit_item.width
                    height: unit_item.height
                    radius: unit_item.radius
                }
            }
            MouseArea {
                id: subMouse
                anchors.fill: parent
                onClicked: btn.clicked()
                //                onPressed: btn.pressed()
                //                onReleased: btn.released()
                //                onPressAndHold: btn.pressAndHold()
            }

            RowLayout {
                spacing: 0
                anchors.fill: parent
                Item {
                    Layout.preferredWidth: 10
                    Layout.fillHeight: true
                }
                Image {
                    Layout.fillHeight: true
                    Layout.preferredWidth: root.item_type === Submodule.ItemType.File ? 0 : height
                    source: "./folder.svg"
                    fillMode: Image.PreserveAspectFit
                }
                Item {
                    Layout.preferredWidth: root.item_type === Submodule.ItemType.File ? 0 : 10
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillHeight: true
                    Layout.preferredWidth: contentWidth <= unit_item.width - 10
                                           - unit_item.height - (root.item_type === Submodule.ItemType.File ? 0 : 10 + height) ? contentWidth : unit_item.width - 10 - unit_item.height - (root.item_type === Submodule.ItemType.File ? 0 : 10 + height)
                    font.pixelSize: parent.height / 3
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    text: root.item_type === Submodule.ItemType.File ? root.item_json.filename : root.item_json.dirname
                    font.bold: true
                    color: "white"
                    clip: true
                }
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Function_Button {
                    id: btn
                    iconImg: root.item_type
                             === Submodule.ItemType.File ? "./menu.svg" : "./enter.svg"
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    onClicked: {
                        if (root.item_type === Submodule.ItemType.File)
                            root.callMenu(root.item_json)
                        else
                            root.goFolder(root.item_json.dirname)
                    }
                }
            }
        }
    }
}
