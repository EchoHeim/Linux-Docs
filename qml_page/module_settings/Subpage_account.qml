import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
//具有公共抬头组件
import "../module_common"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: true
    property bool callKeybroad_doEvent: false
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
    onCallKeybroad: {
        callKeybroad_doEvent = true
    }
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
        x: root.active ? 0 : root.width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
        //底色
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        color: root.rgb(255, 255, 255)
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
            DropShadow {
                anchors.fill: mylabel
                horizontalOffset: 4
                verticalOffset: 2
                radius: 8
                samples: 25
                color: Qt.lighter("#999999", 1.35)
                source: mylabel
            }
            Label {
                id: mylabel
                height: parent.height
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: "  " + qsTr("账户") + "  "
                font.underline: true
                font.pixelSize: height / 3 * 2
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
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
    }
    Rectangle {
        MouseArea {
            //阻止层
            anchors.fill: parent
            enabled: root.callKeybroad_doEvent
        }
        //底色
        anchors.fill: parent
        color: "black"
        opacity: root.callKeybroad_doEvent ? 0.8 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }
}
