#pragma once

#include <QWidget>
#include <QColor>
#include <QPainterPath>

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);

    const QColor& lineColor() const;
    qreal lineWidth() const;
    Qt::PenStyle lineStyle() const;
    const QPainterPath& path() const;

    void setLineColor(const QColor& lineColor);
    void setLineWidth(qreal lineWidth);
    void setLineStyle(Qt::PenStyle lineStyle);
    void setPath(const qreal *xArray, const qreal *yArray, qsizetype pointCount);

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QColor lineColor_;
    qreal lineWidth_;
    Qt::PenStyle lineStyle_;
    QPainterPath path_;
};
