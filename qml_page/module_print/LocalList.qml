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
    signal callMenu(var currentPath, var json)
    signal goFolder(var currentPath, var path)
    property int selectedIndex: -1
    Connections {
        target: page_print
        onActiveChanged: {
            if (page_print.active) {
                goPath()
            }
        }
    }
    property var jsonId: 5644
    onGoFolder: {
        var tree = root.item_path.split("/")
        tree.push(path)
        root.item_path = tree.join("/")
        root.goPath()
    }
    function goPath() {
        var data = JSON.parse(
                    webSocket.readFile(
                        "moonraker/API/server/files/get_directory_request_rpc.json"))
        data.params.path = root.item_path
        root.jsonId = data.id
        webSocket.sendTextMessage(JSON.stringify(data))
    }
    Connections {
        target: webSocket
        onNewData: {
            if (message.id === root.jsonId) {
                item_json = message.result
                buildPath()
            }
        }
    }
    Connections {
        target: webSocket
        onNewData: {
            if (message.hasOwnProperty("result"))
                if (message.result.hasOwnProperty("action"))
                    if (message.result.action === "delete_file") {
                        goPath()
                    }
        }
    }
    function buildPath() {
        root.selectedIndex = -1 //选项复位
        listModel.clear()
        for (var dirs in root.item_json.dirs) {
            listModel.append({
                                 "inputJson": root.item_json.dirs[dirs],
                                 "inputType": Submodule.ItemType.Folder
                             })
        }
        for (var files in root.item_json.files) {
            listModel.append({
                                 "inputJson": root.item_json.files[files],
                                 "inputType": Submodule.ItemType.File
                             })
        }
    }
    property var item_json: {
        "dirs": [{
                     "modified": 1615768162.0412788,
                     "size": 4096,
                     "dirname": "test"
                 }, {
                     "modified": 1613569827.489749,
                     "size": 4096,
                     "dirname": "Cura"
                 }, {
                     "modified": 1615767459.6265886,
                     "size": 4096,
                     "dirname": "thumbs"
                 }],
        "files": [{
                      "modified": 1615578004.9639666,
                      "size": 7300692,
                      "filename": "Funnel_0.2mm_PLA_Ender2_2h4m.gcode"
                  }, {
                      "modified": 1589156863.9726968,
                      "size": 4214831,
                      "filename": "CE2_Pi3_A+_CaseLID.gcode"
                  }, {
                      "modified": 1615030592.7722695,
                      "size": 2388774,
                      "filename": "CE2_calicat.gcode"
                  }],
        "disk_usage": {
            "total": 7522213888,
            "used": 4280369152,
            "free": 2903625728
        }
    }
    property string item_path: "gcodes"
    property bool active: false

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
    Item {
        anchors.fill: parent
        anchors.topMargin: 70
        ColumnLayout {
            anchors.fill: parent
            spacing: 0
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Item {
                    id: tree_tap
                    width: parent.width - 40
                    height: parent.height
                    anchors.centerIn: parent
                    RowLayout {
                        anchors.fill: parent
                        spacing: 0
                        Function_Button {
                            iconImg: "./main_page.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            onClicked: {
                                root.item_path = "gcodes"
                                root.goPath()
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 10
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.preferredWidth: contentWidth < tree_tap.width - 2 * height
                                                   - 20 ? contentWidth : tree_tap.width
                                                          - 2 * height - 20
                            font.pixelSize: parent.height / 3 * 2
                            horizontalAlignment: contentWidth
                                                 < width ? Text.AlignLeft : Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            text: root.item_path
                            font.bold: true
                            color: "white"
                            clip: true
                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 10
                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                        Function_Button {
                            iconImg: "./back.svg"
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            visible: root.item_path !== "gcodes"
                            onClicked: {
                                var tree = root.item_path.split("/")
                                tree.pop()
                                root.item_path = tree.join("/")
                                root.goPath()
                            }
                        }
                    }
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 2
                Rectangle {
                    width: parent.width - 40
                    height: parent.height
                    anchors.centerIn: parent
                    color: "gray"
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Item {
                    width: parent.width - 40
                    height: parent.height
                    anchors.centerIn: parent
                    ListView {
                        id: listView
                        anchors.fill: parent
                        orientation: ListView.Vertical
                        clip: true
                        model: listModel
                        delegate: listDel

                        move: Transition {
                            NumberAnimation {
                                properties: "x,y"
                                duration: 500
                                easing.type: Easing.InOutExpo
                            }
                        }
                        //                        Component.onCompleted: {
                        //                            var metadata = root.item_json
                        //                            for (var dirs in metadata.dirs) {
                        //                                listModel.append({
                        //                                                     "inputJson": metadata.dirs[dirs],
                        //                                                     "inputType": Submodule.ItemType.Folder
                        //                                                 })
                        //                            }
                        //                            for (var files in metadata.files) {
                        //                                listModel.append({
                        //                                                     "inputJson": metadata.files[files],
                        //                                                     "inputType": Submodule.ItemType.File
                        //                                                 })
                        //                            }
                        //                        }
                    }
                    ListModel {
                        id: listModel
                    }
                    Component {
                        id: listDel
                        Submodule {
                            width: listView.width
                            height: 70
                            item_type: inputType
                            item_json: inputJson
                            selected: root.selectedIndex === index
                            onCallMenu: {
                                root.selectedIndex = index
                                root.callMenu(root.item_path, json)
                            }
                            onGoFolder: {
                                root.selectedIndex = -1
                                root.goFolder(root.item_path, path)
                            }
                        }
                    }
                }
            }
        }
    }
}
