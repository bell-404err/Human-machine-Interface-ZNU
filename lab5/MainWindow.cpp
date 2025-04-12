#include <cmath>

#include <QMessageBox>
#include <QList>
#include <QMdiSubWindow>
#include <QSettings>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "SettingsWindow.h"
#include "./ui_SettingsWindow.h"
#include "PlotWindow.h"
#include "./ui_PlotWindow.h"
#include "TableWindow.h"
#include "./ui_TableWindow.h"

MainWindow::MainWindow(QWidget * const parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    auto * const settingsWindow = new SettingsWindow;
    auto * const settingsSubWindow = ui_->mdiArea->addSubWindow(settingsWindow);
    settingsSubWindow->setWindowTitle("Налаштування");
    settingsSubWindow->setAttribute(Qt::WA_DeleteOnClose, false);
    connect(settingsWindow->ui()->calculationButton, SIGNAL(released()), this, SLOT(releaseCalculationButton()));

    auto * const plotSubWindow = ui_->mdiArea->addSubWindow(new PlotWindow);
    plotSubWindow->setWindowTitle("Графік");
    plotSubWindow->setAttribute(Qt::WA_DeleteOnClose, false);

    auto * const tableSubWindow = ui_->mdiArea->addSubWindow(new TableWindow);
    tableSubWindow->setWindowTitle("Таблиця");
    tableSubWindow->setAttribute(Qt::WA_DeleteOnClose, false);

    readState(QSettings(this));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::releaseCalculationButton() const
{
    auto * const settingsWindow = static_cast<SettingsWindow *>(ui_->mdiArea->subWindowList()[0]->widget());
    const auto * const settingsWindowUi = settingsWindow->ui();
    const qreal start = settingsWindowUi->startSpinBox->value();
    const qreal end = settingsWindowUi->endSpinBox->value();
    if (start >= end) {
        QMessageBox::warning(settingsWindow, "Помилка", "Початок має бути меншим за кінець!");
        return;
    }
    const qsizetype pointCount = settingsWindowUi->pointCountSpinBox->value();
    const auto delta = (end - start) / (pointCount - 1);

    int functionNumber;
    if (settingsWindowUi->function1RadioButton->isChecked()) {
        functionNumber = 1;
    } else if (settingsWindowUi->function2RadioButton->isChecked()) {
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

    auto * const plotWindowUi = static_cast<PlotWindow *>(ui_->mdiArea->subWindowList()[1]->widget())->ui();
    plotWindowUi->plot->setPath(xArray, yArray, pointCount);
    plotWindowUi->plot->update();

    auto * const tableWindowUi = static_cast<TableWindow *>(ui_->mdiArea->subWindowList()[2]->widget())->ui();
    tableWindowUi->resultTextEdit->setText(resultText);
}

void MainWindow::triggerSettingsAction() const
{
    static_cast<SettingsWindow *>(ui_->mdiArea->subWindowList()[0]->widget())->show();
}

void MainWindow::triggerPlotAction() const
{
    static_cast<PlotWindow *>(ui_->mdiArea->subWindowList()[1]->widget())->show();
}

void MainWindow::triggerTableAction() const
{
    static_cast<TableWindow *>(ui_->mdiArea->subWindowList()[2]->widget())->show();
}

void MainWindow::triggerSaveAction()
{
    auto fileName = windowTitle();
    if (fileName == "MainWindow") {
        fileName = QFileDialog::getSaveFileName(this, "Зберегти файл як", ".", "Текстові файли (*.ini)");
        if (fileName.isEmpty()) {
            return;
        }

        setWindowTitle(fileName);
    }

    QSettings settings(fileName, QSettings::IniFormat, this);
    settings.clear();
    saveState(settings);
}

void MainWindow::triggerSaveAsAction()
{
    const auto fileName = QFileDialog::getSaveFileName(this, "Зберегти файл як", ".", "Текстові файли (*.ini)");
    if (fileName.isEmpty()) {
        return;
    }
    setWindowTitle(fileName);

    QSettings settings(fileName, QSettings::IniFormat, this);
    settings.clear();
    saveState(settings);
}

void MainWindow::triggerOpenAction()
{
    const auto fileName = QFileDialog::getOpenFileName(this, "Відкрити", ".", "Текстові файли (*.ini)");
    if (fileName.isEmpty()) {
        return;
    }

    readState(QSettings(fileName, QSettings::IniFormat, this));
    setWindowTitle(fileName);
}

void MainWindow::triggerResetAction()
{
    readState(QSettings(this));
    setWindowTitle("MainWindow");
}

void MainWindow::triggerPrintAction()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);

    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() != QDialog::Accepted) {
        return;
    }

    const auto * const tableWindowUi = static_cast<TableWindow *>(ui_->mdiArea->subWindowList()[2]->widget())->ui();
    QTextDocument(tableWindowUi->resultTextEdit->toPlainText(), this).print(&printer);
}

void MainWindow::saveState(QSettings& settings) const
{
    const auto * const settingsWindowUi = static_cast<SettingsWindow *>(ui_->mdiArea->subWindowList()[0]->widget())->ui();
    int functionNumber;
    if (settingsWindowUi->function1RadioButton->isChecked()) {
        functionNumber = 1;
    } else if (settingsWindowUi->function2RadioButton->isChecked()) {
        functionNumber = 2;
    } else {
        Q_ASSERT(false);
    }
    settings.setValue("functionNumber", functionNumber);
    settings.setValue("start", settingsWindowUi->startSpinBox->value());
    settings.setValue("end", settingsWindowUi->endSpinBox->value());
    settings.setValue("pointCount", settingsWindowUi->pointCountSpinBox->value());

    const auto * const plotWindowUi = static_cast<PlotWindow *>(ui_->mdiArea->subWindowList()[1]->widget())->ui();
    settings.setValue("lineWidth", plotWindowUi->lineWidthSpinBox->value());
    settings.setValue("lineRed", plotWindowUi->lineRedSlider->value());
    settings.setValue("lineGreen", plotWindowUi->lineGreenSlider->value());
    settings.setValue("lineBlue", plotWindowUi->lineBlueSlider->value());
    settings.setValue("lineAlpha", plotWindowUi->lineAlphaSlider->value());
    settings.setValue("lineStyle", plotWindowUi->lineStyleSlider->value());
}

void MainWindow::readState(const QSettings& settings) const
{
    const auto * const settingsWindowUi = static_cast<SettingsWindow *>(ui_->mdiArea->subWindowList()[0]->widget())->ui();
    const auto functionNumber = settings.value("functionNumber", 1).toInt();
    if (functionNumber == 1) {
        settingsWindowUi->function1RadioButton->setChecked(true);
    } else if (functionNumber == 2) {
        settingsWindowUi->function2RadioButton->setChecked(true);
    } else {
        Q_ASSERT(false);
    }
    settingsWindowUi->startSpinBox->setValue(settings.value("start", 0.0).toDouble());
    settingsWindowUi->endSpinBox->setValue(settings.value("end", 0.0).toDouble());
    settingsWindowUi->pointCountSpinBox->setValue(settings.value("pointCount", 2).toInt());

    const auto * const plotWindowUi = static_cast<PlotWindow *>(ui_->mdiArea->subWindowList()[1]->widget())->ui();
    plotWindowUi->lineWidthSpinBox->setValue(settings.value("lineWidth", 2.0).toDouble());
    plotWindowUi->lineRedSlider->setValue(settings.value("lineRed", 0).toInt());
    plotWindowUi->lineGreenSlider->setValue(settings.value("lineGreen", 0).toInt());
    plotWindowUi->lineBlueSlider->setValue(settings.value("lineBlue", 0).toInt());
    plotWindowUi->lineAlphaSlider->setValue(settings.value("lineAlpha", 255).toInt());
    plotWindowUi->lineStyleSlider->setValue(static_cast<Qt::PenStyle>(settings.value("lineStyle", 1).toInt()));
}
