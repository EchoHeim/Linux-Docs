import QtQuick 2.14
import "module_main"

Item {
    id: root
    implicitWidth: 800
    implicitHeight: 480
    property bool active: true
    //    enabled: active
    //    visible: active
    signal openPage(var pageName)
    signal remind(var text, var mode)
    signal remind_Reply(var result)
    signal exitRemind

    property alias pos_int_X: parameterPanel.pos_int_X
    property alias pos_int_Y: parameterPanel.pos_int_Y
    property alias pos_int_Z: parameterPanel.pos_int_Z
    Rectangle {
        //底色
        anchors.fill: parent
        //        color: "white"
        color: "#2a2424"
        //        enabled: active
        //        color: "lightgray"
        //        Rectangle {
        //            //渲染测试
        //            anchors.fill: flower
        //            color: "transparent"
        //            border.width: 1
        //        }
        Item {
            //顶层预览元素
            //            anchors.horizontalCenter: parent.horizontalCenter
            //            width: parent.width
            height: 70
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            // anchors.left: parent.left
            // anchors.right: parent.right
            //            color: "transparent"
            Flickable {
                //触发顶部退出按钮
                height: 70
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                contentHeight: 10
                contentWidth: 10
                onVerticalVelocityChanged: {
                    if (verticalVelocity < -500) {
                        root.active = false
                        exit_Dialog.active = true
                    }
                }
            }
            Coordinate_view_panel {
                id: parameterPanel
                //                width: parent.width / 3
                anchors.top: parent.top
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Image {
            source: "./module_main/home_page_bottom.svg"
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            height: 20
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Flickable {
            //触发底部控制台
            height: 70
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            contentHeight: 10
            contentWidth: 10
            onVerticalVelocityChanged: {
                if (verticalVelocity > 500) {
                    root.openPage("Page_console") //呼叫页面
                }
            }
        }
        Flow {
            id: flower
            spacing: 20
            anchors.fill: parent
            anchors.topMargin: 70
            anchors.leftMargin: 20
            anchors.rightMargin: 0
            anchors.bottomMargin: 0

            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    themeColor: "#2a2424"
                    fontColor: "white"
                    titleText: qsTr("温度")
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/temperature.svg"
                    onClicked: {
                        //                        for (var i = 0; i < 2; i++) {
                        //                            root.remind("Tose测试", Common_RemindDialog.Mode.Tose)
                        //                            root.remind("Lock测试", Common_RemindDialog.Mode.Lock)
                        //                            root.remind("Comfirm测试",
                        //                                        Common_RemindDialog.Mode.Comfirm)
                        //                            root.remind("Select测试",
                        //                                        Common_RemindDialog.Mode.Select)
                        //                        }
                        root.openPage("Page_temperature")
                    }
                }
            }
            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("风速")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/fan.svg"
                    rotate: true
                    onClicked: {
                        root.openPage("Page_fan")
                    }
                }
            }

            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("移动")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/move.svg"
                    onClicked: {
                        root.openPage("Page_move")
                    }
                }
            }
            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("挤出机")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/extruder.svg"
                    onClicked: {
                        root.openPage("Page_extruder")
                    }
                }
            }
            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("调平")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/level.svg"
                    onClicked: {
                        root.openPage("Page_level")
                    }
                }
            }

            //            Rectangle {//多位宽组件
            //                height: parent.height / 2 - 20
            //                width: parent.width / 2 - 20
            //                //                border.width: 1
            //                color: "transparent"
            //                Function_entrance {
            //                    anchors.centerIn: parent
            //                    titleText: qsTr("打印")
            //                    height: parent.height < (parent.width / 2
            //                                             - 10) ? parent.height : (parent.width / 2 - 10)
            //                    width: (parent.width / 2 - 10) < parent.height ? parent.width : (parent.width - (((parent.width - 10) / 2) - parent.height))
            //                    iconImg: "./module_main/print.svg"
            //                }
            //            }
            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("摄像头")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/camera.svg"
                    onClicked: {
                        root.openPage("Page_camera")
                    }
                }
            }
            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("设置")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/settings.svg"
                    rotate: true
                    onClicked: {
                        root.openPage("Page_settings")
                    }
                }
            }

            Item {
                height: parent.height / 2 - 20
                width: parent.width / 4 - 20
                //                color: "transparent"
                //                border.width: 1
                Function_entrance {
                    anchors.centerIn: parent
                    titleText: qsTr("打印")
                    themeColor: "#2a2424"
                    fontColor: "white"
                    height: parent.height < parent.width ? parent.height : parent.width
                    width: parent.width < parent.height ? parent.width : parent.height
                    iconImg: "./module_main/print.svg"
                    onClicked: {
                        root.openPage("Page_print")
                    }
                }
            }
        }
    }
    Exit_Dialog {
        //退出 APP 按钮浮层
        id: exit_Dialog
        anchors.fill: parent
        onBack: root.active = true
    }
}
