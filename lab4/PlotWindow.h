#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlotWindow;
}
QT_END_NAMESPACE

class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

    Ui::PlotWindow *ui() const;

private slots:
    void changePlotStyle() const;

private:
    Ui::PlotWindow * const ui_;
};
