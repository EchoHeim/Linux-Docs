import QtQuick 2.14
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import "../module_common"

Item {
    id: root
    implicitWidth: 800
    implicitHeight: 60
    property bool pos_int_X: false
    property bool pos_int_Y: true
    property bool pos_int_Z: true
    property double x_pos: 12.3
    property double y_pos: 144.1
    property double z_pos: 0
    property double contentWidth: x_viewer.contentWidth + y_viewer.contentWidth
                                  + z_viewer.contentWidth + 20
    property string state: "Anonymous"
    //    property alias stateLight: state_light.color
    property var fanSpeed: page_fan.currentSpeed
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

                try {
                    x_pos = message.params[0].toolhead.position[0]
                } catch (e5) {

                }
                try {
                    y_pos = message.params[0].toolhead.position[1]
                } catch (e6) {

                }
                try {
                    z_pos = message.params[0].toolhead.position[2]
                } catch (e7) {

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
    Connections {
        target: webSocket
        onNewData: {
            try {
                if (message.result.hasOwnProperty("status")) {
                    var homed_axes = message.result.status.toolhead.homed_axes
                    try {
                        pos_int_X = (homed_axes.indexOf("x") > -1
                                     || homed_axes.indexOf("X") > -1)
                    } catch (e1) {

                    }
                    try {
                        pos_int_Y = (homed_axes.indexOf("y") > -1
                                     || homed_axes.indexOf("Y") > -1)
                    } catch (e2) {

                    }
                    try {
                        pos_int_Z = (homed_axes.indexOf("z") > -1
                                     || homed_axes.indexOf("Z") > -1)
                    } catch (e3) {

                    }
                    try {
                        x_pos = message.result.status.motion_report.live_position[0]
                    } catch (e4) {

                    }
                    try {
                        y_pos = message.result.status.motion_report.live_position[1]
                    } catch (e5) {

                    }
                    try {
                        z_pos = message.result.status.motion_report.live_position[2]
                    } catch (e6) {

                    }
                }
            } catch (e) {

            }
        }
    }
    RowLayout {
        spacing: 0
        anchors.fill: parent
        anchors.margins: 0
        Item {
            Layout.fillHeight: true
            //            Layout.preferredWidth: x_viewer.contentWidth + y_viewer.contentWidth
            //                                   + z_viewer.contentWidth + 30
            Layout.preferredWidth: height * 3 + 30
            Halo {
                anchors.fill: parent
            }
            RowLayout {
                spacing: 0
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 10
                }
                Item {
                    Layout.fillHeight: true
                    //                    Layout.preferredWidth: x_viewer.contentWidth
                    Layout.preferredWidth: height / 3 * 3
                    Label {
                        id: x_viewer
                        anchors.fill: parent
                        font.pixelSize: height / 3
                        text: "X " + (root.pos_int_X ? root.x_pos.toFixed(
                                                           0) : "---") + " "
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        //                fontSizeMode: Text.VerticalFit
                        minimumPixelSize: 1
                        color: "white"
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 5
                }
                Item {
                    Layout.fillHeight: true
                    //                    Layout.preferredWidth: y_viewer.contentWidth
                    Layout.preferredWidth: height / 3 * 3
                    Label {
                        id: y_viewer
                        anchors.fill: parent
                        font.pixelSize: height / 3
                        text: "Y " + (root.pos_int_Y ? root.y_pos.toFixed(
                                                           0) : "---") + " "
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        //                        fontSizeMode: Text.VerticalFit
                        minimumPixelSize: 1
                        color: "white"
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 5
                }
                Item {
                    Layout.fillHeight: true
                    //                    Layout.preferredWidth: z_viewer.contentWidth
                    Layout.preferredWidth: height / 3 * 3
                    Label {
                        id: z_viewer
                        anchors.fill: parent
                        font.pixelSize: height / 3
                        text: "Z " + (root.pos_int_Z ? root.z_pos.toFixed(
                                                           0) : "---") + " "
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        //                fontSizeMode: Text.VerticalFit
                        minimumPixelSize: 1
                        color: "white"
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 10
                }
            }
        }
        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 5
        }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Halo {
                anchors.fill: parent
            }
            RowLayout {
                spacing: 0
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    //喷嘴
                    Layout.fillHeight: true
                    Layout.preferredWidth: height / 2 + title_hotend_label.contentWidth
                    Image {
                        id: title_hotend_img
                        source: "./title_hotend.svg"
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        height: parent.height / 2
                        width: parent.height / 2
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                    }
                    Label {
                        id: title_hotend_label
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height
                        width: contentWidth
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
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    //热床
                    Layout.fillHeight: true
                    Layout.preferredWidth: height / 2 + title_heatbed_label.contentWidth
                    Image {
                        id: title_heatbed_img
                        source: "./title_heatbed.svg"
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        height: parent.height / 2
                        width: parent.height / 2
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                    }
                    Label {
                        id: title_heatbed_label
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height
                        width: contentWidth
                        font.pixelSize: height / 3
                        text: root.heatbed_active.toFixed(
                                  0) + "/" + root.heatbed_target.toFixed(
                                  0) + "℃"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        minimumPixelSize: 1
                        color: "white"
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Item {
                    //风速
                    Layout.fillHeight: true
                    Layout.preferredWidth: height / 2 + title_fan_label.contentWidth
                    Image {
                        id: title_fan_img
                        source: "./title_fan.svg"
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        height: parent.height / 2
                        width: parent.height / 2
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                    }
                    Label {
                        id: title_fan_label
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height
                        width: contentWidth
                        font.pixelSize: height / 3
                        text: root.fanSpeed + "%"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        minimumPixelSize: 1
                        color: "white"
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 5
        }
        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: state_viewer.width + state_img.width + 40
            Halo {
                anchors.fill: parent
            }
            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: 20
            }
            Label {
                id: state_viewer
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: contentWidth
                font.pixelSize: height / 3
                text: qsTr(root.state) + " "
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                minimumPixelSize: 1
                color: "white"
            }
            Image {
                id: state_img
                source: "./home_page_icon_user.svg"
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                height: parent.height / 2
                width: parent.height / 2
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
            }
            //            Rectangle {
            //                id: state_light
            //                color: "lime"
            //                height: parent.height / 5
            //                width: parent.height / 5
            //                radius: parent.height
            //                anchors.right: parent.right
            //                anchors.rightMargin: 10
            //                anchors.verticalCenter: parent.verticalCenter

            //                Behavior on color {
            //                    ColorAnimation {
            //                        duration: 100
            //                    }
            //                }
            //            }
            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: 20
            }
        }
    }
}
