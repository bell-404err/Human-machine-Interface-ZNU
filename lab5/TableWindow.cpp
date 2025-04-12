#include "TableWindow.h"
#include "ui_TableWindow.h"

TableWindow::TableWindow(QWidget * const parent) :
    QWidget(parent),
    ui_(new Ui::TableWindow)
{
    ui_->setupUi(this);
}

TableWindow::~TableWindow()
{
    delete ui_;
}

Ui::TableWindow *TableWindow::ui() const
{
    return ui_;
}
