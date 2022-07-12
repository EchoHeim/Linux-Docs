import QtQuick 2.14

Canvas {
    id: canvasId
    property color triangleColor: "#65e7ff"
    property int radius: 10
    property int spacing: 3
    implicitWidth: 800
    implicitHeight: 60
    contextType: "2d"

    onPaint: {
        context.lineWidth = 2
        context.strokeStyle = canvasId.triangleColor
        //            context.fillStyle = "transparent"
        context.beginPath()
        context.moveTo(
                    0,
                    height / 3 > canvasId.radius ? canvasId.radius : height / 3)
        context.lineTo(
                    height / 3 > canvasId.radius ? canvasId.radius : height / 3,
                    0)
        context.lineTo(width, 0)
        context.lineTo(
                    width,
                    height - (height / 3 > canvasId.radius ? canvasId.radius : height / 3))
        context.lineTo(
                    width - (height / 3 > canvasId.radius ? canvasId.radius : height / 3),
                    height)
        context.lineTo(0, height)
        context.lineTo(
                    0,
                    height / 3 > canvasId.radius ? canvasId.radius : height / 3)
        //                        context.closePath()
        //            context.fill()
        context.stroke()
    }
    Canvas {
        anchors.fill: parent
        anchors.margins: canvasId.spacing
        contextType: "2d"

        onPaint: {
            context.lineWidth = 2
            context.strokeStyle = canvasId.triangleColor
            //            context.fillStyle = "transparent"
            context.beginPath()
            context.moveTo(
                        0,
                        height / 3 > canvasId.radius ? canvasId.radius : height / 3)
            context.lineTo(
                        height / 3 > canvasId.radius ? canvasId.radius : height / 3,
                        0)
            context.lineTo(width, 0)
            context.lineTo(
                        width,
                        height - (height / 3 > canvasId.radius ? canvasId.radius : height / 3))
            context.lineTo(
                        width - (height / 3 > canvasId.radius ? canvasId.radius : height / 3),
                        height)
            context.lineTo(0, height)
            context.lineTo(
                        0,
                        height / 3 > canvasId.radius ? canvasId.radius : height / 3)
            //                        context.closePath()
            //            context.fill()
            context.stroke()
        }
    }
}
