#include <cmath>

#include <QMessageBox>
#include <QList>
#include <QMdiSubWindow>

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
}

MainWindow::~MainWindow()
{
    delete ui_;
}

template <typename T>
static T * findSubWindowWidget(const QList<QMdiSubWindow *>& subWindows)
{
    for (auto * const subWindow : subWindows) {
        auto * const widget = dynamic_cast<T*>(subWindow->widget());
        if (widget != nullptr) {
            return widget;
        }
    }

    Q_ASSERT(false);
}

void MainWindow::releaseCalculationButton() const
{
    auto * const settingsWindow = findSubWindowWidget<SettingsWindow>(ui_->mdiArea->subWindowList());
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

    auto * const plotWindowUi = findSubWindowWidget<PlotWindow>(ui_->mdiArea->subWindowList())->ui();
    plotWindowUi->plot->setPath(xArray, yArray, pointCount);
    plotWindowUi->plot->update();

    auto * const tableWindowUi = findSubWindowWidget<TableWindow>(ui_->mdiArea->subWindowList())->ui();
    tableWindowUi->resultTextEdit->setText(resultText);
}

void MainWindow::triggerSettingsAction() const
{
    findSubWindowWidget<SettingsWindow>(ui_->mdiArea->subWindowList())->show();
}

void MainWindow::triggerPlotAction() const
{
    findSubWindowWidget<PlotWindow>(ui_->mdiArea->subWindowList())->show();
}

void MainWindow::triggerTableAction() const
{
    findSubWindowWidget<TableWindow>(ui_->mdiArea->subWindowList())->show();
}
