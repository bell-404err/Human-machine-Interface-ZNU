#pragma once

#include <QWidget>

namespace Ui {
class TableWindow;
}

class TableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = nullptr);
    ~TableWindow();

    Ui::TableWindow *ui() const;

private:
    Ui::TableWindow * const ui_;
};
