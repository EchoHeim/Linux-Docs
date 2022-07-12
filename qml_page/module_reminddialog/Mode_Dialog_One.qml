import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    opacity: active ? 1 : 0
    enabled: active
    property bool active: false
    //引入对话信号
    //    signal remind(var mode, var text)
    //执行对话信号
    signal execRemind(var text)
    //发起退出信号
    signal output(var result)
    onExecRemind: {
        dialog.text = text
    }
    enum Key {
        Yes = 0,
        No = 1,
        Comfirm = 2
    }
    Behavior on opacity {
        NumberAnimation {
            duration: 150
        }
    }
    Rectangle {
        //锁定区域
        id: background
        anchors.fill: parent
        color: "black"
        opacity: background_lockArea.pressed ? 0.8 : 0.5 //不支持操作提醒
        Behavior on opacity {
            NumberAnimation {
                duration: 150
            }
        }
        MouseArea {
            id: background_lockArea
            anchors.fill: parent
        }
    }
    Rectangle {
        id: backgroundRectangle
        anchors.centerIn: parent
        width: root.width / 5 * 4
        height: root.height / 3 * 2
        radius: 25
        color: "#101011"
        border.color: "#65e7ff"
        layer.enabled: true
        layer.effect: DropShadow {
            //            horizontalOffset: 2
            //            verticalOffset: 4
            radius: background_lockArea.pressed ? 24 : 12
            color: background_lockArea.pressed ? "#65e7ff" : "black"
            samples: 25 /*20*/
            Behavior on radius {
                NumberAnimation {
                    duration: 150
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 150
                }
            }
        }
        Label {
            id: dialog
            anchors.fill: parent
            anchors.margins: 10
            anchors.bottomMargin: 100
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WrapAnywhere
            color: "white"
            text: "耗材已用尽，请尽快更换耗材"
        }
        Remind_Button {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 70
            width: root.width / 2
            anchors.horizontalCenter: parent.horizontalCenter
            titleText: qsTr("确定")
            onClicked: {
                root.output(Mode_Dialog_One.Key.Comfirm)
                root.active = false
            }
        }
    }
}
