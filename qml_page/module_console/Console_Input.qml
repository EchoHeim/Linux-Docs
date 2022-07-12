import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

TextField {
    id: root
    property color checkedColor: "#65e7ff"
    signal callKeybroad(var currentText)

    placeholderText: enabled ? notice_phrase.Console_Input_input[config.language] : notice_phrase.Console_Input_disable[config.language]
    font.pixelSize: height / 2
    antialiasing: true
    implicitWidth: 213
    implicitHeight: 42

    background: Rectangle {
        id: background_area
        anchors.fill: root
        anchors.margins: 5
        radius: height / 4
        color: root.enabled ? "white" : "tranparent"
        border.color: root.enabled ? root.checkedColor : "#999999"
        border.width: 1
        //        opacity: root.enabled ? 1 : 0.7
        //        Behavior on anchors.margins {
        //            NumberAnimation {
        //                duration: 250
        //            }
        //        }
        Behavior on border.color {
            ColorAnimation {
                duration: 250
            }
        }
        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }

        layer.enabled: true
        layer.effect: DropShadow {
            id: dropShadow
            transparentBorder: true
            color: root.focus ? "#65e7ff" : "transparent"
            Behavior on samples {
                NumberAnimation {
                    duration: 75
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 250
                }
            }
            samples: root.focus ? 20 : 0 /*20*/
        }
    }
    onReleased: root.callKeybroad(root.text)
    onPressAndHold: selectAll()
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

