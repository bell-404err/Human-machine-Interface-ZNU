#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget * const parent) :
    QWidget(parent),
    ui_(new Ui::SettingsWindow)
{
    ui_->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui_;
}

Ui::SettingsWindow *SettingsWindow::ui() const
{
    return ui_;
}
