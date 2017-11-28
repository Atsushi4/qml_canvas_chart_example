import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.0

Item {
    id: mainRoot
    anchors.fill: parent
    ColumnLayout {
        anchors.fill: parent
        Repeater {
            Layout.fillWidth: true
            id: buttons
            model: [
                {text: 'Canvas', source: 'Chart1.qml'},
                {text: 'QPainter', source: 'Chart2.qml'}
            ]
            delegate: Button {
                Layout.fillWidth: true
                text: modelData.text
                onClicked: loader.setSource(modelData.source)
            }
        }
        Loader {
            id: loader
            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors {
                top: buttons.bottom;
                left: parent.left;
                bottom: parent.bottom;
                right: parent.right
            }
            source: 'Chart1.qml'
        }
    }
    DataSource {
        id: dataSource
        Binding {
            target: loader.item
            property: 'chartData'
            value: dataSource.chartData
        }
    }
    Timer {
        id: updateTimer
        repeat: true
        running: true
        interval: 100
        property int delta: 1
        property int pos: 0
        onTriggered: {
            pos += delta
            if (pos <= 0 || pos >= 60 * 4)
                delta *= -1
        }
    }
    Binding {
        target: loader.item
        property: 'pos'
        value: updateTimer.pos
    }
}
