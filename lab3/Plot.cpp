#include <QPen>
#include <QColor>
#include <QPainter>
#include <QPainterPath>

#include "Plot.h"

Plot::Plot(QWidget * const parent) :
    QWidget(parent),
    lineColor_(Qt::black),
    lineWidth_(2.0),
    lineStyle_(Qt::SolidLine)
{
}

const QColor& Plot::lineColor() const
{
    return lineColor_;
}

qreal Plot::lineWidth() const
{
    return lineWidth_;
}

Qt::PenStyle Plot::lineStyle() const
{
    return lineStyle_;
}

const QPainterPath& Plot::path() const
{
    return path_;
}

void Plot::setLineColor(const QColor& lineColor)
{
    lineColor_ = lineColor;
}

void Plot::setLineWidth(const qreal lineWidth)
{
    lineWidth_ = lineWidth;
}

void Plot::setLineStyle(const Qt::PenStyle lineStyle)
{
    lineStyle_ = lineStyle;
}

void Plot::setPath(const qreal * const xArray, const qreal * const yArray, const qsizetype pointCount)
{
    auto xMin = xArray[0];
    auto xMax = xMin;
    auto yMin = yArray[0];
    auto yMax = yMin;
    for (qsizetype i = 1; i < pointCount; ++i) {
        const auto x = xArray[i];
        if (x < xMin) {
            xMin = x;
        } else if (x > xMax) {
            xMax = x;
        }

        const auto y = yArray[i];
        if (y < yMin) {
            yMin = y;
        } else if (y > yMax) {
            yMax = y;
        }
    }

    const auto xScale = this->width() / (xMax - xMin);
    const auto yScale = this->height() / (yMax - yMin);

    path_ = QPainterPath(QPointF((xArray[0] - xMin) * xScale, (yArray[0] - yMin) * yScale));
    for (qsizetype i = 1; i < pointCount; ++i) {
        path_.lineTo((xArray[i] - xMin) * xScale, (yArray[i] - yMin) * yScale);
    }
}

void Plot::paintEvent(QPaintEvent * const event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(lineColor_);
    pen.setWidth(lineWidth_);
    pen.setStyle(lineStyle_);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);

    painter.drawPath(path_);
}
