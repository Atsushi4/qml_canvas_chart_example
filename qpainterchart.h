#ifndef QPAINTERCHART_H
#define QPAINTERCHART_H

#include <QQuickPaintedItem>

// [3]
class QPainterChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList chartData READ chartData WRITE setChartData NOTIFY chartDataChanged)
    Q_PROPERTY(int pos READ pos WRITE setPos NOTIFY posChanged)
public:
    QPainterChart(QQuickItem *parent = Q_NULLPTR);
    ~QPainterChart() Q_DECL_OVERRIDE;
    QVariantList chartData() const;
    int pos() const;

signals:
    void chartDataChanged(QVariantList chartData);
    void posChanged(int pos);

public slots:
    void setChartData(QVariantList chartData);
    void setPos(int pos);

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter) Q_DECL_OVERRIDE;

private:
    class Private;
    Private *d;
};

#endif // QPAINTERCHART_H
