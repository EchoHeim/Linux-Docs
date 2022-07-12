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
    property bool callKeybroad_doEvent: false
    property var page_data
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
    onActiveChanged: {
        if (active) {
            listModel.clear()
            for (var languagelist in page_data.language) {
                //                console.debug(page_data.language[languagelist].displayName)
                listModel.append(page_data.language[languagelist])
            }
        }
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
        x: active ? 0 : width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
        //底色
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        color: "#2a2424"
        Item {
            //页眉
            height: 70
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            Public_Back_Button {
                height: 47
                width: 47
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                onClicked: root.back()
            }
            Label {
                Trapezoidal {
                    anchors.fill: parent
                    //                    anchors.topMargin: 5
                    //                    anchors.bottomMargin: 5
                }
                id: mylabel
                height: contentHeight + 20
                width: contentWidth + height * 3
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("语言切换")
                //                font.underline: true
                font.pixelSize: 30
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 1
                color: "#65e7ff"
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
            ListView {
                id: listView
                anchors.topMargin: 10
                anchors.fill: parent
                orientation: ListView.Vertical
                model: listModel
                delegate: listDel
                move: Transition {
                    NumberAnimation {
                        properties: "x,y"
                        duration: 500
                        easing.type: Easing.InOutExpo
                    }
                }
            }
            ListModel {
                id: listModel
            }
            Component {
                id: listDel
                Std_Button {
                    width: listView.width - 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 70
                    titleText: displayName
                    enabled: visible
                    onClicked: {
                        var myconfig = config
                        myconfig.language = lang_id
                        qmlLanguage.setLanguage(myconfig.language)
                        //                        console.debug(lang_id)
                        //                        console.debug(myconfig.language)
                        config = myconfig
                        //                        console.debug(JSON.stringify(config))
                        webSocket.writeFile("config/UserDefine.json",
                                            JSON.stringify(config))
                    }
                }
            }
        }
    }
    Rectangle {
        MouseArea {
            //阻止层
            anchors.fill: parent
            enabled: root.callKeybroad_doEvent
        }
        //底色
        anchors.fill: parent
        color: "black"
        opacity: root.callKeybroad_doEvent ? 0.8 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 100
            }
        }
    }
}
