#ifndef INVALIDSAVEWINDOW_H
#define INVALIDSAVEWINDOW_H

#include <QDialog>

namespace Ui {
class InvalidSaveWindow;
}

class InvalidSaveWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InvalidSaveWindow(QWidget *parent = nullptr);
    ~InvalidSaveWindow();

private slots:
    void on_okBtn_released();

private:
    Ui::InvalidSaveWindow *ui;
};

#endif // INVALIDSAVEWINDOW_H
