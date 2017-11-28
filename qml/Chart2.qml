import QtQuick 2.4
import atsushi.examples 0.1

Item {
    id: chart2Root
    property alias chartData: chartArea.chartData
    property alias pos: chartArea.pos
    // [5]
    PainterChart {
        id: chartArea
        anchors.fill: parent
    }
}
