#include "PlotWindow.h"
#include "ui_PlotWindow.h"

PlotWindow::PlotWindow(QWidget * const parent) :
    QWidget(parent),
    ui_(new Ui::PlotWindow)
{
    ui_->setupUi(this);
    changePlotStyle();
}

PlotWindow::~PlotWindow()
{
    delete ui_;
}

Ui::PlotWindow *PlotWindow::ui() const
{
    return ui_;
}

void PlotWindow::changePlotStyle() const
{
    auto * const plot = ui_->plot;
    plot->setLineColor(QColor(
        ui_->lineRedSlider->value(),
        ui_->lineGreenSlider->value(),
        ui_->lineBlueSlider->value(),
        ui_->lineAlphaSlider->value()
    ));
    plot->setLineWidth(ui_->lineWidthSpinBox->value());
    plot->setLineStyle(static_cast<Qt::PenStyle>(ui_->lineStyleSlider->value()));
    plot->update();
}
