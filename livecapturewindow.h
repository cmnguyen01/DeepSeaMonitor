#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QWidget>

namespace Ui {
class liveCaptureWindow;
}

class liveCaptureWindow : public QWidget
{
    Q_OBJECT

public:
    explicit liveCaptureWindow(QWidget *parent = nullptr);
    ~liveCaptureWindow();

private:
    Ui::liveCaptureWindow *ui;
};

#endif // LIVECAPTUREWINDOW_H
