import QtQuick 2.14
import "module_reminddialog"

Item {
    id: root
    implicitHeight: 480
    implicitWidth: 800
    signal remind(var text, var mode)
    signal exitRemind
    signal output(var result)
    onRemind: {
        switch (mode) {
            //判断对话类型
        case Common_RemindDialog.Mode.Tose:
            mode_Tose.remind(text)
            break
        case Common_RemindDialog.Mode.Lock:
            mode_Lock.remind(text)
            break
        case Common_RemindDialog.Mode.Select:
        case Common_RemindDialog.Mode.Comfirm:
            mode_Dialogs.remind(mode, text)
            break
        }
    }
    enum Mode {
        Tose = 0,
        Lock = 1,
        Select = 2,
        Comfirm = 3
    }
    enum Key {
        Yes = 0,
        No = 1,
        Comfirm = 2
    }
    Mode_Lock {
        id: mode_Lock
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        //        Connections {
        //            target: root
        //            onExitRemind: {
        //                mode_Lock.exitRemind() //外围发起退出对话信号
        //            }
        //        }
        Component.onCompleted: {
            root.exitRemind.connect(mode_Lock.exitRemind)
        }
    }
    Mode_Dialogs {
        id: mode_Dialogs
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        onOutput: root.output(result)
    }
    Mode_Tose {
        id: mode_Tose
        //        width: parent.width
        //        height: parent.height
        //        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
    }
}
