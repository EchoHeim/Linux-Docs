import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    opacity: active ? 1 : 0
    property bool active: false
    //引入对话信号
    signal remind(var text)
    //执行对话信号
    signal execRemind
    //发起退出信号
    signal exitRemind
    property int autoTime: 2000 /*自动收缩时间ms*/
    onRemind: {
        remindQueue.append({
                               "text": text
                           })
    }
    onExecRemind: {
        root.active = true
        dialog.text = remindQueue.get(0).text
    }
    onExitRemind: {
        remindQueue.removeFirst() //删除条目
        entity.yChanged.connect(destroy_obj) //绑定退出动画
        root.active = false
    }
    Behavior on opacity {
        NumberAnimation {
            duration: 150
        }
    }
    function destroy_obj() {
        //动画终止位置
        if (entity.y === (-dialog.height - 70 - 10 - 5)) {
            entity.yChanged.disconnect(destroy_obj)
            root.execQueue() //检测执行
        }
    }
    function execQueue() {
        if (root.active === false) //队列未运行(需要激活队列)
        {
            //存在队列
            if (remindQueue.count > 0)
                root.execRemind()
        }
    }
    ListModel {
        //对话队列模型
        id: remindQueue
        function removeFirst() {
            remove(0)
        }
        onRowsInserted: {
            root.execQueue() //检测执行
        }
    }
    Timer {
        //自动收缩
        running: root.active
        interval: root.autoTime
        repeat: false
        onTriggered: root.exitRemind()
    }
    //    Image {
    //        //单元测试
    //        anchors.fill: parent
    //        source: "/Users/shine/Desktop/刘大师.jpg"
    //        MouseArea {
    //            anchors.fill: parent
    //            onClicked: {
    //                if (root.active)
    //                    root.exitRemind()
    //                else
    //                    root.remind("测试测试测试测试测试测试测试测测试测试测测试测试测试测试测试测试测试测测试测试测")
    //            }
    //        }
    //    }
    Item {
        id: entity
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: root.active ? 0 : -dialog.height - 70 - 10 - 5
        Behavior on y {
            NumberAnimation {
                duration: 150
            }
        }
        Rectangle {
            id: backgroundRectangle
            anchors.centerIn: dialog
            height: dialog.contentHeight + 20
            width: dialog.contentWidth + 50
            radius: 25
            color: "black"
            border.color: "#65e7ff"
            opacity: 0.8
            layer.enabled: true
            layer.effect: DropShadow {
                //                horizontalOffset: 2
                //                verticalOffset: 4
                radius: 12
                color: "#65e7ff"
                samples: 25 /*20*/
            }
            MouseArea {
                anchors.fill: parent
                onReleased: {
                    root.exitRemind()
                }
            }
        }
        Label {
            id: dialog
            anchors.top: parent.top
            anchors.topMargin: 70
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width / 5 * 4
            wrapMode: Text.WrapAnywhere
            color: "white"
        }
    }
}
