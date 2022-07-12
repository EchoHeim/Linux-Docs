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
    RowLayout {
        spacing: 0
        anchors.fill: parent
        Item {
            //定位点
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            Item {
                width: 180
                height: 180
                anchors.centerIn: parent
                //                anchors.fill: parent
                //                anchors.margins: 20
                ColumnLayout {
                    spacing: 0
                    anchors.fill: parent
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        RowLayout {
                            spacing: 0
                            anchors.fill: parent
                            Function_Button {
                                iconImg: "./point.svg"
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                onClicked: {
                                    root.remind(notice_phrase.MBL_Point[config.language] + "1:"
                                                + (margins_Slider.slider.value) + ","
                                                + (page_move.y_max - margins_Slider.slider.value),
                                                Common_RemindDialog.Mode.Tose)
                                    if (!page_main.pos_int_X
                                            || !page_main.pos_int_Y)
                                        webSocket.sendScript("G28 XY")
                                    webSocket.sendScript("G90")
                                    webSocket.sendScript(
                                                "G1 X" + (margins_Slider.slider.value) + " Y"
                                                + (page_move.y_max - margins_Slider.slider.value))
                                }
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                            }
                            Function_Button {
                                iconImg: "./point.svg"
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                onClicked: {
                                    root.remind(notice_phrase.MBL_Point[config.language] + "2:"
                                                + (page_move.x_max - margins_Slider.slider.value)
                                                + "," + (page_move.y_max
                                                         - margins_Slider.slider.value),
                                                Common_RemindDialog.Mode.Tose)
                                    if (!page_main.pos_int_X
                                            || !page_main.pos_int_Y)
                                        webSocket.sendScript("G28 XY")
                                    webSocket.sendScript("G90")
                                    webSocket.sendScript(
                                                "G1 X" + (page_move.x_max
                                                          - margins_Slider.slider.value) + " Y"
                                                + (page_move.y_max - margins_Slider.slider.value))
                                }
                            }
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        RowLayout {
                            spacing: 0
                            anchors.fill: parent
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                            }
                            Function_Button {
                                iconImg: "./point.svg"
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                onClicked: {
                                    root.remind(notice_phrase.MBL_Point[config.language]
                                                + "3:" + (page_move.x_max / 2)
                                                + "," + (page_move.y_max / 2),
                                                Common_RemindDialog.Mode.Tose)
                                    if (!page_main.pos_int_X
                                            || !page_main.pos_int_Y)
                                        webSocket.sendScript("G28 XY")
                                    webSocket.sendScript("G90")
                                    webSocket.sendScript(
                                                "G1 X" + (page_move.x_max / 2)
                                                + " Y" + (page_move.y_max / 2))
                                }
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                            }
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        RowLayout {
                            spacing: 0
                            anchors.fill: parent
                            Function_Button {
                                iconImg: "./point.svg"
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                onClicked: {
                                    root.remind(notice_phrase.MBL_Point[config.language] + "4:"
                                                + (margins_Slider.slider.value)
                                                + "," + (margins_Slider.slider.value),
                                                Common_RemindDialog.Mode.Tose)
                                    if (!page_main.pos_int_X
                                            || !page_main.pos_int_Y)
                                        webSocket.sendScript("G28 XY")
                                    webSocket.sendScript("G90")
                                    webSocket.sendScript(
                                                "G1 X" + (margins_Slider.slider.value) + " Y"
                                                + (margins_Slider.slider.value))
                                }
                            }
                            Item {
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                            }
                            Function_Button {
                                iconImg: "./point.svg"
                                Layout.fillHeight: true
                                Layout.preferredWidth: height
                                onClicked: {
                                    root.remind(notice_phrase.MBL_Point[config.language] + "5:"
                                                + (page_move.x_max - margins_Slider.slider.value)
                                                + "," + (margins_Slider.slider.value),
                                                Common_RemindDialog.Mode.Tose)
                                    if (!page_main.pos_int_X
                                            || !page_main.pos_int_Y)
                                        webSocket.sendScript("G28 XY")
                                    webSocket.sendScript("G90")
                                    webSocket.sendScript(
                                                "G1 X" + (page_move.x_max
                                                          - margins_Slider.slider.value) + " Y"
                                                + (margins_Slider.slider.value))
                                }
                            }
                        }
                    }
                }
            }
        }
        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 3
            Rectangle {
                color: "#65e7ff"
                width: 1
                height: parent.height - 80
                anchors.centerIn: parent
            }
        }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Item {
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: 120
                width: parent.width - 80
                Label {
                    id: margin_label
                    text: qsTr("边距")
                    font.pixelSize: 30
                    //                    minimumPixelSize: 1
                    //                    fontSizeMode: Text.Fit
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "white"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                SuperSlider {
                    id: margins_Slider
                    height: parent.height
                    width: parent.width - margin_label.contentWidth
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    slider.checkedColor: "#65e7ff"
                    slider.unit: "mm"
                    slider.from: 0
                    slider.to: ((page_move.y_max < page_move.x_max ? page_move.y_max : page_move.x_max) / 4).toFixed(
                                   0)
                    slider.value: 0
                    slider.stepSize: 1
                    slider.onValueSet: {
                        root.remind(notice_phrase.MBL_Margins[config.language]
                                    + ": " + value + slider.unit,
                                    Common_RemindDialog.Mode.Tose)
                    }
                }
            }
            Std_Button {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: 70
                width: parent.width - 80
                titleText: qsTr("解锁XY")
                onClicked: webSocket.sendScript("M18 X Y")
            }
        }
    }
    layer.enabled: true
    layer.effect: DropShadow {
        radius: 12
        samples: 25
        color: root.active ? (root.opacity === 1 ? "#65e7ff" : "transparent") : "transparent"
        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
    }
}
