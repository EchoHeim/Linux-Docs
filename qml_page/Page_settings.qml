import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "module_settings"
//具有公共抬头组件
import "module_common"

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
    onActiveChanged: {
        if (active) {
            listModel.clear()
            for (var settinglist in config.settings) {
                if (!(config.settings[settinglist].hasOwnProperty("visable")
                      && !config.settings[settinglist]["visable"]))
                    listModel.append(config.settings[settinglist])
            }
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
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        x: root.active ? 0 : root.width
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
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
                text: qsTr("设置")
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
            width: parent.width
            height: parent.height - 70
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            Item {
                //页脚
                id: page_item
                width: parent.width - 20
                height: parent.height - 10
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 10
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
                        height: visible ? (!style.hasOwnProperty(
                                               "height") ? 70 : style.height) : 0
                        //                        titleText: qsTr(displayName)
                        titleText: displayName[config.language]
                        visible: !style.hasOwnProperty("type")
                                 || style["type"] === "Std_Button"
                        enabled: visible
                        mode: method.name
                        Component.onCompleted: {
                            //                            console.debug(config.language)
                            if (sectionId === "language") {
                                subpage_language.page_data = method.page_data
                            }
                        }
                        onClicked: {
                            //功能分配处理
                            if (method.name === "script") {
                                webSocket.sendScript(method.script)
                            }
                            if (method.name === "json") {
                                var json_Data = JSON.parse(webSocket.readFile(
                                                               method.path))
                                if (method.hasOwnProperty("params"))
                                    json_Data.params = method.params
                                webSocket.sendTextMessage(JSON.stringify(
                                                              json_Data))
                            }
                            if (method.name === "json_path") {
                                var json_path_get = JSON.parse(
                                            webSocket.readFile(
                                                method.get.method.path))
                                method.get.id = json_path_get.id //获取执行ID
                                if (method.get.method.name === "json")
                                    if (method.get.method.hasOwnProperty(
                                                "params"))
                                        json_path_get.params = method.get.method.params
                                webSocket.newData.connect(json_path_receiver)
                                webSocket.sendTextMessage(JSON.stringify(
                                                              json_path_get))
                            }
                            if (method.name === "pageActive") {
                                if (method.page === "Page_Language") {
                                    subpage_language.active = true
                                }
                            }
                            if (method.name === "test") {
                                //测试方法
//                                for (var i = 0; i < 20; i++)
//                                    console.debug("<!>")
//                                console.debug(JSON.stringify(
//                                                  combineJson(
//                                                      method.params_Combine,
//                                                      method.params)))
                            }
                        }
                        function json_path_receiver(message) {
                            if (message.hasOwnProperty("id")) {
                                if (message.id === method.get.id) {
                                    //                                    for (var i = 0; i < 20; i++)
                                    //                                        console.debug("<!>")
                                    webSocket.newData.disconnect(
                                                json_path_receiver)
                                    var json_Data = JSON.parse(
                                                webSocket.readFile(method.path))
                                    json_Data.params = combineJson(
                                                message.result,
                                                method.params) //合并JSON
                                    webSocket.sendTextMessage(JSON.stringify(
                                                                  json_Data))
                                }
                            }
                        }
                        function combineJson(json_all, json_combine) {
                            for (var key in json_all) {
//                                console.debug(key)
                                if (Array.isArray(json_all[key])) {
                                    if (json_combine.hasOwnProperty(key))
                                        for (var itemKey in json_combine[key]) {
                                            json_all[key][itemKey] = combineJson(
                                                        json_all[key][itemKey],
                                                        json_combine[key][itemKey])
                                        }
                                } else {
                                    if (json_combine.hasOwnProperty(key))
                                        json_all[key] = json_combine[key]
                                }
                            }
                            return json_all
                        }
                    }
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 1
                color: "#2a2424"
                opacity: 1
                layer.enabled: true
                layer.effect: DropShadow {
                    spread: 0.9
                    radius: 12
                    samples: 25
                    color: listView.atYEnd ? "#2a2424" : "#65e7ff"
                    Behavior on color {
                        ColorAnimation {
                            duration: 250
                        }
                    }
                }
            }
        }
    }
    Subpage_language {
        id: subpage_language
        anchors.fill: parent
    }
}
