#include "invalidsavewindow.h"
#include "ui_invalidsavewindow.h"

InvalidSaveWindow::InvalidSaveWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvalidSaveWindow)
{
    ui->setupUi(this);
    ui->errorText->setAlignment(Qt::AlignCenter);
    ui->errorText2->setAlignment(Qt::AlignCenter);
}

InvalidSaveWindow::~InvalidSaveWindow()
{
    delete ui;
}

void InvalidSaveWindow::on_okBtn_released()
{
    InvalidSaveWindow::close();
}
