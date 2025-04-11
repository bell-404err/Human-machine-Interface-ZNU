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
    const auto x = ui_->argumentSpinBox->value();
    const QRadioButton *checkedRadioButton;
    double result;
    if ((checkedRadioButton = ui_->function1RadioButton)->isChecked()) {
        result = 3 * sin(5 * x) - 2 * cos(3 * x) + 3;
    } else if ((checkedRadioButton = ui_->function2RadioButton)->isChecked()) {
        result = pow(5, 34 + pow(x, 5)) - pow(5, 1 - pow(x, 2));
    } else {
        Q_ASSERT(false);
    }
    const auto functionText = checkedRadioButton->text();
    const auto resultText = QString::number(result, 'g', 10);

    ui_->resultLineEdit->setText(resultText);
    const auto messageText = QString("Функція: %1\nАргумент: %2\nРезультат: %3").arg(
        functionText,
        QString::number(x, 'g', 10),
        resultText
    );
    QMessageBox::information(this, "Успіх!", messageText);
}
