import QtQuick 2.14
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    implicitHeight: 20
    implicitWidth: 250
    color: "#2a2424"
    radius: 10
    border.color: "#65e7ff"
    property alias slider: sliderBase
    Item {
        height: parent.height
        width: 70
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        SuperSliderButton {
            width: 50
            height: 50
            anchors.centerIn: parent
            titleImg: "minus.svg"
            onClicked: {
                sliderBase.value -= sliderBase.stepSize
            }
            enabled: sliderBase.value > sliderBase.from
        }
    }
    SliderBase {
        id: sliderBase
        height: parent.height
        width: parent.width - 140
        anchors.centerIn: parent
    }
    Item {
        height: parent.height
        width: 70
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        SuperSliderButton {
            width: 50
            height: 50
            anchors.centerIn: parent
            titleImg: "add.svg"
            onClicked: {
                sliderBase.value += sliderBase.stepSize
            }
            enabled: sliderBase.value < sliderBase.to
        }
    }
    layer.enabled: false
    layer.effect: DropShadow {
        //        horizontalOffset: 2
        //        verticalOffset: 2
        radius: 12
        samples: 25
        color: "#65e7ff"
    }
}
