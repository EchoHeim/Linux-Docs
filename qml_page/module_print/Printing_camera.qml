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
    property bool active: false
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
    signal remind_Reply(var result)
    signal exitRemind
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
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height
        x: root.active ? 0 : root.width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
        color: "#2a2424"
        MouseArea {
            enabled: root.active
            anchors.fill: parent
            onClicked: {
                page_title.active = !page_title.active
            }
        }
        //铺垫元素
        Item {
            anchors.fill: parent
            rotation: page_camera.flipData.flip_deg ? -90 : 0
            Behavior on rotation {
                NumberAnimation {
                    duration: 250
                }
            }
            scale: page_camera.flipData.flip_deg ? parent.height / parent.width : 1
            Behavior on scale {
                NumberAnimation {
                    duration: 100
                }
            }
            Item {
                anchors.fill: parent
                transform: Rotation {
                    origin.x: viewer.width / 2
                    origin.y: viewer.height / 2
                    axis.x: 0
                    axis.y: 1
                    axis.z: 0
                    angle: page_camera.flipData.flip_H ? 180 : 0
                    Behavior on angle {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                }
                Image {
                    id: preload
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    //                    source: "./Demo.jpeg"
                    property string address: "http://" + config.ipAddress + "/"
                    property string path: "webcam/?action=snapshot&"
                    Timer {
                        interval: 100
                        repeat: true
                        running: root.active && camSwitch.run
                        onTriggered: {
                            if (parent.status === Image.Ready
                                    || parent.status === Image.Null
                                    || parent.status === Image.Error)
                                parent.source = parent.address + parent.path + Date.now()
                        }
                    }
                    onStatusChanged: {
                        if (status === Image.Ready) {
                            preload.grabToImage(function (result) {
                                viewer.source = result.url
                            }, Qt.size(preload.width * 2, preload.height * 2))
                            whistleblowers.opacity = 0
                        }
                    }
                    visible: false
                }
                Image {
                    id: viewer
                    anchors.fill: parent
                    //                fillMode: Image.PreserveAspectFit
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    cache: false
                    asynchronous: true
                    source: "./Demo.jpeg"

                    transform: Rotation {
                        origin.x: viewer.width / 2
                        origin.y: viewer.height / 2
                        axis.x: 1
                        axis.y: 0
                        axis.z: 0
                        angle: coordinate_view_panel.flip_V ? 180 : 0
                        Behavior on angle {
                            NumberAnimation {
                                duration: 250
                            }
                        }
                    }
                }
            }
        }
        Item {
            //页眉
            id: page_title
            height: 70
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            y: active ? 0 : -height
            Behavior on y {
                NumberAnimation {
                    duration: 300
                }
            }
            property bool active: true
            Public_Back_Button {
                height: 47
                width: 47
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                onClicked: root.back()
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
            Label {
                id: whistleblowers
                height: 30
                width: parent.width * 0.6
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: height
                text: notice_phrase.Cam_Error[config.language]
                fontSizeMode: Text.Fit
                color: "white"
                Behavior on opacity {
                    NumberAnimation {
                        duration: 300
                    }
                }
            }
        }
        Function_Button {
            id: camSwitch
            iconImg: run ? "./printing_icon_camera_close.svg" : "./printing_icon_camera_open.svg"
            height: 100
            width: 100
            property bool run: true
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: page_title.active ? 10 : -height
            anchors.rightMargin: page_title.active ? 10 : -width
            Behavior on anchors.bottomMargin {
                NumberAnimation {
                    duration: 300
                }
            }
            Behavior on anchors.rightMargin {
                NumberAnimation {
                    duration: 300
                }
            }
            onClicked: {
                run = !run
            }
        }
    }
}
