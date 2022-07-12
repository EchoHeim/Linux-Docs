import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    signal remind(var text, var mode)
    signal exitRemind
    signal show(var json)
    onShow: {
        item_json = json
        active = true
    }
    property var item_json: {
        "modified": 1615578004.9639666,
        "size": 7300692,
        "filename": "Funnel_0.2mm_PLA_Ender2_2h4m.gcode",
        "dirname": "thumbs"
    }
    property bool active: false

    //时间数据转换
    function changeDateFormat(cellval) {
        var date = new Date(parseInt(cellval))
        var month = date.getMonth(
                    ) + 1 < 10 ? "0" + (date.getMonth(
                                            ) + 1) : date.getMonth() + 1
        var currentDate = date.getDate() < 10 ? "0" + date.getDate(
                                                    ) : date.getDate()
        return date.getFullYear() + "-" + month + "-" + currentDate + " "
                + date.getHours() + ":" + date.getMinutes(
                    ) + ":" + date.getSeconds()
    }
    //存储数据转换
    function changeSizeFormat(sizevalue) {
        var sizeVal = sizevalue
        var unit = ["b", "KB", "MB", "GB"]
        var index = 0
        while (sizeVal / 1024 > 1 && index < 4) {
            sizeVal = (sizeVal / 1024).toFixed(2)
            index++
        }
        //        console.debug(sizeVal)
        return sizeVal + unit[index]
    }

    signal back
    onBack: {
        active = false
    }
    enabled: active
    //    opacity: active ? 1 : 0
    //    Behavior on opacity {
    //        NumberAnimation {
    //            id: root_opacity
    //            duration: 150
    //        }
    //    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            //            root.active = !root.active
            root.back()
        }
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: root.active ? 0.5 : 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 150
                }
            }
        }
        Rectangle {
            id: reference
            width: root.active ? parent.width / 5 * 4 : 1
            height: root.active ? parent.height / 3 * 2 : 1
            color: "#101011"
            border.color: "#65e7ff"
            opacity: root.active ? 1 : 0
            radius: 5
            anchors.centerIn: parent
            onWidthChanged: {
                if (width === 1) {
                    ref_opacity.duration = 30
                    ref_width.easing.type = Easing.InOutQuint
                }
                if (width === parent.width / 3 * 2) {
                    ref_opacity.duration = 1000
                    ref_width.easing.type = Easing.OutExpo
                }
            }
            Behavior on opacity {
                NumberAnimation {
                    id: ref_opacity
                    duration: 30
                }
            }
            Behavior on width {
                NumberAnimation {
                    id: ref_width
                    duration: 500
                    easing.type: Easing.InOutQuint
                }
            }
            Behavior on height {
                NumberAnimation {
                    id: ref_height
                    duration: ref_width.duration
                    easing.type: ref_width.easing.type
                }
            }
            MouseArea {
                id: reference_MouseArea
                anchors.fill: parent
            }
            layer.enabled: true
            layer.effect: DropShadow {
                radius: reference_MouseArea.pressed | reference_MouseArea.pressAndHold ? 24 : 0
                Behavior on radius {
                    NumberAnimation {
                        duration: 250
                    }
                }
                color: "#65e7ff"
                samples: 25 /*20*/
            }
        }
        Label {
            anchors.fill: reference
            anchors.margins: 20
            font.pixelSize: 20
            fontSizeMode: Text.Fit
            minimumPixelSize: 1
            wrapMode: Text.WrapAnywhere
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            text: qsTr("filename") + " : " + root.item_json.filename + "\n\n"
                  + qsTr("size") + " : " + root.changeSizeFormat(
                      root.item_json.size) + "\n\n" + qsTr("modified")
                  + " : " + root.changeDateFormat(root.item_json.modified)
            font.bold: true
            color: "#FFFFFF"
            clip: true
            opacity: reference.width === parent.width / 5 * 4 ? 1 : 0
            //            Behavior on opacity {
            //                NumberAnimation {
            //                    duration: 30
            //                }
            //            }
        }
    }
}
