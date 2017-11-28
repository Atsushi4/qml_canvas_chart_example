#include "qpainterchart.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>

class QPainterChart::Private
{
public:
    explicit Private(QPainterChart *parent) : q{parent} {}
    void drawTicks(QPainter *painter) const;
    void drawSeries(QPainter *painter, int index) const;

private:
    QPainterChart *q;
public:
    QVariantList chartData;
    int pos = 0;
};

QPainterChart::QPainterChart(QQuickItem *parent)
    : QQuickPaintedItem{parent}
    , d{new Private{this}}
{

}

QPainterChart::~QPainterChart()
{
    delete d;
}

QVariantList QPainterChart::chartData() const
{
    return d->chartData;
}

int QPainterChart::pos() const
{
    return d->pos;
}

void QPainterChart::setChartData(QVariantList chartData)
{
    qDebug() << "set" << chartData;
    if (d->chartData == chartData)
        return;

    d->chartData = chartData;
    emit chartDataChanged(d->chartData);
}

void QPainterChart::setPos(int pos)
{
    if (d->pos == pos)
        return;

    d->pos = pos;
    emit posChanged(d->pos);
    this->update();
}

void QPainterChart::paint(QPainter *painter)
{
    d->drawTicks(painter);
    qDebug() << d->pos << d->chartData;
    for (int i = 0; i < d->chartData.size(); ++i)
        d->drawSeries(painter, i);
}

void QPainterChart::Private::drawTicks(QPainter *painter) const
{
    painter->save();
    auto size = q->boundingRect().size().toSize();
    auto minute = size.width() / 60.;
    auto interval = 5 * minute;
    painter->setPen(QPen(QColor::fromRgbF(0.5, 0.5, 0.5)));
    qreal x = (5 - (pos % 5)) * minute;
    for (auto i = 0; i < 12; ++i, x += interval) {
        painter->drawLine(x, 0, x, size.height());
    }
    painter->restore();
}

void QPainterChart::Private::drawSeries(QPainter *painter, int index) const
{
    if (index >= chartData.size() || chartData[index].toList().size() <= pos) return;
    const QList<QColor> colors = {
        QColor(QLatin1Literal("red")),
        QColor(QLatin1Literal("blue")),
        QColor(QLatin1Literal("green")),
        QColor(QLatin1Literal("yellow")),
        QColor(QLatin1Literal("pink")),
        QColor(QLatin1Literal("orange")),
        QColor(QLatin1Literal("darkBlue")),
        QColor(QLatin1Literal("lightBlue")),
    };
    painter->save();
    auto series = chartData[index].toList();
    auto size = q->boundingRect().size().toSize();
    auto width = size.width();
    auto height = size.height();
    auto minute = width / 60.;
    auto count = qMin<int>(width / minute + 1, series.size() - 1 - pos);
    auto current = pos;
    painter->setPen(QPen(colors[index]));
    QPainterPath path;
    path.moveTo(0, series[current++].toInt() * height / 30.);
    for (auto i = 1; i < count; ++i) {
        path.lineTo(i * minute, series[current++].toInt() * height / 30.);
    }
    painter->drawPath(path);
    painter->restore();
}
