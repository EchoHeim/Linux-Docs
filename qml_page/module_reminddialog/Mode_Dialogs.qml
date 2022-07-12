import QtQuick 2.14

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    //引入对话信号
    signal remind(var mode, var text)
    //执行对话信号
    signal execRemind
    signal output(var result)
    onOutput: {
        remindQueue.removeFirst()
        root.execQueue() //检测执行
    }
    enum Key {
        Yes = 0,
        No = 1,
        Comfirm = 2
    }
    enum Mode {
        Select = 2,
        Comfirm = 3
    }
    onRemind: {
        remindQueue.append({
                               "mode": mode,
                               "text": text
                           })
    }
    onExecRemind: {
        switch (remindQueue.get(0).mode) {
        case Mode_Dialogs.Mode.Select:
            mode_Dialog_Two.execRemind(remindQueue.get(0).text)
            mode_Dialog_Two.active = true
            break
        case Mode_Dialogs.Mode.Comfirm:
            mode_Dialog_One.execRemind(remindQueue.get(0).text)
            mode_Dialog_One.active = true
            break
        }
    }
    function execQueue() {
        //存在队列
        if (remindQueue.count > 0)
            root.execRemind()
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
    Mode_Dialog_One {
        id: mode_Dialog_One
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        onOutput: root.output(result)
    }
    Mode_Dialog_Two {
        id: mode_Dialog_Two
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        onOutput: root.output(result)
    }
}
