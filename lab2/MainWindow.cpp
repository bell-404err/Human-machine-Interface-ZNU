#include <QMessageBox>

#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget * const parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::releaseCalculationButton() {
    const auto start = ui_->startSpinBox->value();
    const auto end = ui_->endSpinBox->value();
    if (start >= end) {
        QMessageBox::warning(this, "Помилка", "Початок має бути меншим за кінець!");
        return;
    }
    const auto pointCount = ui_->pointCountSpinBox->value();
    const auto delta = (end - start) / (pointCount - 1.0);

    int functionNumber;
    if (ui_->function1RadioButton->isChecked()) {
        functionNumber = 1;
    } else if (ui_->function2RadioButton->isChecked()) {
        functionNumber = 2;
    }

    QString resultText;
    auto x = start;
    for (auto i = 0; i < pointCount; ++i, x += delta) {
        double f;
        if (functionNumber == 1) {
            f = 3 * sin(5 * x) - 2 * cos(3 * x) + 3;
        } else if (functionNumber == 2) {
            f = pow(5, 34 + pow(x, 5)) - pow(5, 1 - pow(x, 2));
        } else {
            Q_ASSERT(false);
        }

        resultText.append(QString("f(%1) = %2\n").arg(QString::number(x, 'g', 10), QString::number(f, 'g', 10)));
    }
    ui_->resultTextEdit->setText(resultText);
}
