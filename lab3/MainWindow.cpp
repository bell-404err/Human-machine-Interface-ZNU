#include <cmath>
#include <QMessageBox>
#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget * const parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    changePlotStyle();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::releaseCalculationButton()
{
    const qreal start = ui_->startSpinBox->value();
    const qreal end = ui_->endSpinBox->value();
    if (start >= end) {
        QMessageBox::warning(this, "Помилка", "Початок має бути меншим за кінець!");
        return;
    }
    const qsizetype pointCount = ui_->pointCountSpinBox->value();
    const auto delta = (end - start) / (pointCount - 1);

    int functionNumber;
    if (ui_->function1RadioButton->isChecked()) {
        functionNumber = 1;
    } else if (ui_->function2RadioButton->isChecked()) {
        functionNumber = 2;
    } else {
        functionNumber = 0;
    }

    auto * const xArray = new qreal[pointCount];
    auto * const yArray = new qreal[pointCount];
    QString resultText;
    auto x = start;
    for (qsizetype i = 0; i < pointCount; ++i, x += delta) {
        qreal f;
        if (functionNumber == 1) {
            f = 3 * sin(5 * x) - 2 * cos(3 * x) + 3;
        } else if (functionNumber == 2) {
            f = pow(5, 34 + pow(x, 5)) - pow(5, 1 - pow(x, 2));
        } else {
            Q_ASSERT(false);
        }

        xArray[i] = x;
        yArray[i] = f;
        resultText.append(QString("f(%1) = %2\n").arg(QString::number(x, 'g', 10), QString::number(f, 'g', 10)));
    }
    ui_->plot->setPath(xArray, yArray, pointCount);
    ui_->plot->update();
    ui_->resultTextEdit->setText(resultText);
}

void MainWindow::changePlotStyle()
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
