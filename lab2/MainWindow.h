#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * const parent = nullptr);
    ~MainWindow();

private slots:
    void releaseCalculationButton();

private:
    Ui::MainWindow * const ui_;
};
