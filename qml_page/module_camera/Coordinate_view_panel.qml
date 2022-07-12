import QtQuick 2.14
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

Item {
    id: root
    implicitWidth: 800
    implicitHeight: 60

    //    property int fanSpeed: 100
    property double hotend_target: 180
    property double hotend_active: 120
    property double heatbed_target: 60
    property double heatbed_active: 25
    property var fanSpeed: page_fan.fanSpeed
    property alias flip_H: flip_H_btn.checked
    property alias flip_V: flip_V_btn.checked
    property alias flip_deg: flip_deg_btn.checked
    Connections {
        target: webSocket
        onNewData: {
            if (message.method === "notify_status_update") {
                try {
                    root.hotend_active = message.params[0].extruder.temperature.toFixed(
                                1)
                } catch (e1) {

                }
                try {
                    root.hotend_target = message.params[0].extruder.target.toFixed(
                                1)
                } catch (e3) {

                }
                try {
                    root.heatbed_active = message.params[0].heater_bed.temperature.toFixed(
                                1)
                } catch (e2) {

                }
                try {
                    root.heatbed_target = message.params[0].heater_bed.target.toFixed(
                                1)
                } catch (e4) {

                }
            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            try {
                if (message.result.hasOwnProperty("status")) {
                    try {
                        root.hotend_active = message.result.status.extruder.temperature.toFixed(
                                    1)
                    } catch (e1) {

                    }
                    try {
                        root.hotend_target = message.result.status.extruder.target.toFixed(
                                    1)
                    } catch (e3) {

                    }
                    try {
                        root.heatbed_active = message.result.status.heater_bed.temperature.toFixed(
                                    1)
                    } catch (e2) {

                    }
                    try {
                        root.heatbed_target = message.result.status.heater_bed.target.toFixed(
                                    1)
                    } catch (e4) {

                    }
                }
            } catch (e) {

            }
        }
    }
    Rectangle {
        anchors.centerIn: parent
        height: parent.height / 2
        width: title_hotend_img.width + title_hotend_label.width + 5 + title_heatbed_img.width
               + title_heatbed_label.width + title_fan_img.width + title_fan_label.width + 30
        radius: 10
        color: "gray"
        opacity: 0.5
    }
    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 0
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Item {
            //喷嘴
            Layout.fillHeight: true
            Layout.preferredWidth: title_hotend_img.width + title_hotend_label.width + 5
            Image {
                id: title_hotend_img
                source: "./title_hotend.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 3
                width: parent.height / 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Label {
                id: title_hotend_label
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: contentWidth + 5
                font.pixelSize: height / 3
                text: root.hotend_active.toFixed(
                          0) + "/" + root.hotend_target.toFixed(0) + "℃"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                //                fontSizeMode: Text.VerticalFit
                minimumPixelSize: 1
                color: "white"
            }
        }
        Item {
            //热床
            Layout.fillHeight: true
            Layout.preferredWidth: title_heatbed_img.width + title_heatbed_label.width + 5
            Image {
                id: title_heatbed_img
                source: "./title_heatbed.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 3
                width: parent.height / 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Label {
                id: title_heatbed_label
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: contentWidth + 5
                font.pixelSize: height / 3
                text: root.heatbed_active.toFixed(
                          0) + "/" + root.heatbed_target.toFixed(0) + "℃"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                //                fontSizeMode: Text.VerticalFit
                minimumPixelSize: 1
                color: "white"
            }
        }
        Item {
            //风速
            Layout.fillHeight: true
            Layout.preferredWidth: title_fan_img.width + title_fan_label.width + 5
            Image {
                id: title_fan_img
                source: "./title_fan.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 3
                width: parent.height / 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Label {
                id: title_fan_label
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: contentWidth + 5
                font.pixelSize: height / 3
                text: root.fanSpeed + "%"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                //                fontSizeMode: Text.VerticalFit
                minimumPixelSize: 1
                color: "white"
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
    RowLayout {
        anchors.fill: parent
        spacing: 0
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Item {
            Layout.preferredWidth: 47
            Layout.fillHeight: true
            Function_Button {
                id: flip_H_btn
                iconImg: "./flip_H.svg"
                anchors.fill: parent
                anchors.margins: 2
                checkable: true
            }
        }

        Item {
            Layout.preferredWidth: 47
            Layout.fillHeight: true
            Function_Button {
                id: flip_V_btn
                iconImg: "./flip_V.svg"
                anchors.fill: parent
                anchors.margins: 2
                checkable: true
            }
        }

        Item {
            Layout.preferredWidth: 47
            Layout.fillHeight: true
            Function_Button {
                id: flip_deg_btn
                iconImg: "./flip_deg.svg"
                anchors.fill: parent
                anchors.margins: 2
                checkable: true
            }
        }
    }
}
