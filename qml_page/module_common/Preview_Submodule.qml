import QtQuick 2.14
import QtQuick.Controls 2.13

Item {
    id: root
    height: 480
    width: 800

    property double hotend_target: 180
    property double hotend_active: 120
    property double heatbed_target: 60
    property double heatbed_active: 25
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
            if (message.hasOwnProperty("result"))
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
        }
    }
    Flow {
        layoutDirection: Qt.RightToLeft
        spacing: 0
        height: 50
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        //        Item {
        //            height: parent.height
        //            width: 20
        //        }
        Item {
            //热床
            height: parent.height
            width: title_heatbed_img.width + title_heatbed_label.width
            Image {
                id: title_heatbed_img
                source: "./title_heatbed.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 2
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Label {
                id: title_heatbed_label
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height / 3
                width: contentWidth + height
                font.pixelSize: height
                text: root.heatbed_active + "/" + root.heatbed_target + "℃"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                //                fontSizeMode: Text.VerticalFit
                minimumPixelSize: 1
                color: "white"
            }
        }
        Item {
            height: parent.height
            width: 5
        }
        Item {
            //喷嘴
            height: parent.height
            width: title_hotend_img.width + title_hotend_label.width
            //            color: "transparent"
            Image {
                id: title_hotend_img
                source: "./title_hotend.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 2
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Label {
                id: title_hotend_label
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height / 3
                width: contentWidth + height
                font.pixelSize: height
                text: root.hotend_active + "/" + root.hotend_target + "℃"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                //                fontSizeMode: Text.VerticalFit
                minimumPixelSize: 1
                color: "white"
            }
        }
    }
}
