import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import "../"

Rectangle {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property bool callKeybroad_doEvent: false
    signal remind(var text, var mode)
    enabled: active
    opacity: active ? 1 : 0
    border.color: "#65e7ff"
    color: "#2a2424"
    signal callProbeSet
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
    signal remind_Reply(var result)
    signal exitRemind
    function rgb(r, g, b) {
        var ret = (r << 16 | g << 8 | b)
        return ("#" + ret.toString(16)).toUpperCase()
    }
    radius: 20
    Std_Button {
        anchors.centerIn: parent
        height: width / 3
        width: parent.width / 4
        titleText: qsTr("开始")
        onClicked: {
            root.remind(notice_phrase.Start_ABL[config.language],
                        Common_RemindDialog.Mode.Tose)
            //            _GCode_.append("M502");
            webSocket.sendScript("M502")
            //            _GCode_.append("M500");
            webSocket.sendScript("M500")
            //            _GCode_.append("G91");
            webSocket.sendScript("G91")
            //            _GCode_.append("G28");
            webSocket.sendScript("G28")
            //            _GCode_.append("G29");
            webSocket.sendScript("G29")
            //            _GCode_.append("G90");
            webSocket.sendScript("G90")
            //            _GCode_.append("M500");
            webSocket.sendScript("M500")
        }
    }
    Function_Button {
        iconImg: "./settings.svg"
        anchors.right: parent.right
        height: width / 3
        width: parent.width / 4
        anchors.verticalCenter: parent.verticalCenter
        rotate: true
        onClicked: root.callProbeSet()
    }
    layer.enabled: true
    layer.effect: DropShadow {
        radius: 12
        samples: 25
        color: root.active ? (root.opacity === 1 ? "#65e7ff" : "transparent") : "transparent"
        Behavior on color {
            ColorAnimation {
                duration: 75
            }
        }
    }
}
