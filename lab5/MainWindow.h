#pragma once

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSettings>

#include "SettingsWindow.h"
#include "PlotWindow.h"
#include "TableWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void releaseCalculationButton() const;

    void triggerSettingsAction() const;
    void triggerPlotAction() const;
    void triggerTableAction() const;
    void triggerSaveAction();
    void triggerSaveAsAction();
    void triggerOpenAction();
    void triggerResetAction();
    void triggerPrintAction();

private:
    Ui::MainWindow * const ui_;

    void saveState(QSettings& settings) const;
    void readState(const QSettings& settings) const;
};
