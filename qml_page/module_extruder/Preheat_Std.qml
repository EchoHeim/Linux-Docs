import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    property bool callKeybroad_doEvent: false
    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind
    //    property var metadata
    signal setTempperature(var hotend)
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
            enabled: root.active
            anchors.fill: parent
            onClicked: root.back()
        }
        //底色
        anchors.fill: parent
        color: "black"
        opacity: root.active ? 0.75 : 0
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
        border.color: "#65e7ff"
        color: "#101011"
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
                Label {
                    id: mylabel
                    height: parent.height
                    width: contentWidth
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "  " + qsTr("请选择加热类型") + "  "
                    //                    font.underline: true
                    font.pixelSize: height / 2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
            }
            Flow {
                id: flower
                spacing: 0
                anchors.fill: parent
                anchors.topMargin: 70
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                anchors.bottomMargin: 20
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 0
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
                Item {
                    width: 40
                    height: (parent.height - 20) / 2
                }
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 1
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
                Item {
                    width: 40
                    height: (parent.height - 20) / 2
                }
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 2
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
                Item {
                    width: parent.width
                    height: 20
                }
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 3
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
                Item {
                    width: 40
                    height: (parent.height - 20) / 2
                }
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 4
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
                Item {
                    width: 40
                    height: (parent.height - 20) / 2
                }
                Preheat_Std_Submodule {
                    width: (parent.width - 80) / 3
                    height: (parent.height - 20) / 2
                    property int index: 5
                    Component.onCompleted: {
                        setValue()
                        page_temperature.update.connect(setValue)
                    }
                    function setValue() {
                        name = page_temperature.preheatData.preheatlist[index].preheat_name
                        hotend = page_temperature.preheatData.preheatlist[index].preheat_hotend
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend)
                    }
                }
            }
        }
    }
}
