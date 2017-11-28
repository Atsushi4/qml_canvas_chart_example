import QtQuick 2.4

Item {
    property var chartData: []
    Component.onCompleted: {
        var newData = []
        for (var i = 0; i < 8; ++i) {
            var count = 60 * 5
            newData.push(createData(count));
        }
        chartData = newData
    }
    function createData(count) {
        var series = []
        var value = Math.floor(Math.random() * 30);
        for (var i = 0; i < count; ++i) {
            var delta = Math.floor((Math.random() - 0.5) * 5)
            value += delta
            if (value < 0 || value >= 30)
                value -= 2 * delta
            series.push(value)
        }
        return series
    }
}
