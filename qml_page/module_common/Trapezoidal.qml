import QtQuick 2.14

Canvas {
    id: canvasId
    property color triangleColor: "#65e7ff"
    property int radius: height / 3 * 2
    property int spacing: 3
    implicitWidth: 800
    implicitHeight: 60
    contextType: "2d"

    onPaint: {
        context.lineWidth = 2
        context.strokeStyle = canvasId.triangleColor
        //            context.fillStyle = "transparent"
        context.beginPath()
        context.moveTo(0, 0)
        context.lineTo(width, 0)
        context.lineTo(
                    width - (height > canvasId.radius ? canvasId.radius : height),
                    height)
        context.lineTo(height > canvasId.radius ? canvasId.radius : height,
                       height)
        context.lineTo(0, 0)
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
            context.moveTo(canvasId.spacing, 0)
            context.lineTo(width - canvasId.spacing, 0)
            context.lineTo(
                        width - (height > canvasId.radius ? canvasId.radius : height),
                        height)
            context.lineTo(height > canvasId.radius ? canvasId.radius : height,
                           height)
            context.lineTo(canvasId.spacing, 0)
            //                        context.closePath()
            //            context.fill()
            context.stroke()
        }
    }
}
