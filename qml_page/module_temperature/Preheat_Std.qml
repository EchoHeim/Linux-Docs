import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    property bool active: false
    //测试源数据
    property var metadata
    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind
    signal callCustomEditor
    signal update

    signal setTempperature(var hotend, var heatbed)
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
        border.color: "#65e7ff"
        anchors.horizontalCenter: parent.horizontalCenter
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
                    text: qsTr("请选择预热类型")
                    //                    font.underline: true
                    font.pixelSize: height / 2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                }
                Function_Button {
                    iconImg: "./settings.svg"
                    width: height
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    rotate: true
                    onClicked: root.callCustomEditor()
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
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
                        root.update.connect(setValue)
                    }
                    function setValue() {
                        name = root.metadata.preheatlist[index].preheat_name
                        hotend = root.metadata.preheatlist[index].preheat_hotend
                        heatbed = root.metadata.preheatlist[index].preheat_heatbed
                    }
                    onClicked: {
                        root.back()
                        root.setTempperature(hotend, heatbed)
                    }
                }
            }
        }
    }
}
