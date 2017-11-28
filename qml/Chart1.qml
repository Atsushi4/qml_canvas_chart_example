import QtQuick 2.4

Item {
    id: chart1Root
    property var chartData: []
    property var colors: [
        'red',
        'blue',
        'green',
        'yellow',
        'pink',
        'orange',
        'darkBlue',
        'lightBlue'
    ]
    property alias pos: chartArea.pos
    onPosChanged: chartArea.requestPaint()
    Canvas {
        id: chartArea
        property int pos: 0
        property double minute: width / 60
        anchors.fill: parent
        renderStrategy: Canvas.Immediate
        // [2]
        onPaint: {
            var ctx = getContext('2d')
            ctx.reset()
            drawTicks();
            chartData.forEach(function(series, i){drawSeries(series, colors[i])})
        }
        function drawTicks() {
            var ctx = getContext('2d')
            ctx.save()
            ctx.strokeStyle = Qt.rgba(0.5, 0.5, 0.5, 1)
            ctx.lineWidth = 1
            var interval = 5 * minute
            var x = (5 - (pos % 5)) * minute
            ctx.beginPath()
            for (var i = 0; i < 12; ++i, x += interval) {
                var p = Math.floor(x)
                ctx.moveTo(p, 0)
                ctx.lineTo(p, height)
            }
            ctx.stroke()
            ctx.restore()
        }
        function drawSeries(series, color) {
            if (!(series.length > pos)) return
            var ctx = getContext('2d')
            ctx.save()
            ctx.strokeStyle = color
            ctx.lineWidth = 1
            var count = Math.min(width / minute + 1, series.length - 1 - pos)
            var current = pos
            ctx.beginPath()
            ctx.moveTo(0, Math.floor(series[current++] * height / 30))
            for (var i = 1; i < count; ++i) {
                ctx.lineTo(Math.floor(i * minute), Math.floor(series[current++] * height / 30))
            }
            ctx.stroke()
            ctx.restore()
        }
        // [2]
    }
}
