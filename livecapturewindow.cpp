#include "livecapturewindow.h"
#include "ui_livecapturewindow.h"

liveCaptureWindow::liveCaptureWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liveCaptureWindow)
{
    ui->setupUi(this);
}

liveCaptureWindow::~liveCaptureWindow()
{
    delete ui;
}
