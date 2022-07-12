import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    opacity: active ? 1 : 0
    enabled: active
    property bool active: false
    //引入对话信号
    signal remind(var text)
    //执行对话信号
    signal execRemind
    //发起退出信号
    signal exitRemind
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
        root.opacityChanged.connect(destroy_obj) //绑定退出动画
        root.active = false
    }
    Behavior on opacity {
        NumberAnimation {
            duration: 150
        }
    }
    Timer {
        //测试：自动关闭
        running: false
        interval: 5000
        repeat: false
        onTriggered: root.exitRemind()
    }
    function destroy_obj() {
        //动画终止位置
        if (root.opacity === 0) {
            root.opacityChanged.disconnect(destroy_obj)
            //            console.debug(remindQueue.count)
            root.execQueue() //检测执行
        }
    }
    function execQueue() {
        //        console.debug("remindQueue.count:" + remindQueue.count)
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
            root.execQueue() //触发检测执行
        }
    }
    Rectangle {
        //锁定区域
        id: background
        anchors.fill: parent
        color: "black"
        opacity: background_lockArea.pressed ? 0.85 : 0.7 //不支持操作提醒
        Behavior on opacity {
            NumberAnimation {
                duration: 150
            }
        }
        MouseArea {
            id: background_lockArea
            anchors.fill: parent
        }
    }
    Rectangle {
        id: backgroundRectangle
        anchors.centerIn: dialog
        height: dialog.contentHeight + 20
        width: dialog.contentWidth + 50
        radius: 25
        color: "#101011"
        border.color: "#65e7ff"
        opacity: 1
        layer.enabled: true
        layer.effect: DropShadow {
            //            horizontalOffset: 2
            //            verticalOffset: 4
            radius: background_lockArea.pressed ? 24 : 12
            color: background_lockArea.pressed ? "#65e7ff" : "black"
            samples: 25 /*20*/
            Behavior on radius {
                NumberAnimation {
                    duration: 150
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 150
                }
            }
        }
        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
    }
    Label {
        id: dialog
        anchors.centerIn: parent
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width / 5 * 4
        wrapMode: Text.WrapAnywhere
        color: "white"
    }
}
