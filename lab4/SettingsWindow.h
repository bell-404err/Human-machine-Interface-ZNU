#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    Ui::SettingsWindow *ui() const;

private:
    Ui::SettingsWindow * const ui_;
};
