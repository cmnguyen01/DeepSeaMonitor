#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <fileutils.h>
#include <string>
#include <QJsonObject>

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_loginBtn_released()
{
    std::string username = ui->usernameTextBox->text().toStdString();
    std::string password = ui->passwordTextBox->text().toStdString();
    checkCredentials(username, password);
}

void PasswordDialog::checkCredentials(std::string username, std::string password)
{
    ui->errorLabel->setAlignment(Qt::AlignCenter);

    if(FileUtils::verifyCredentials(username, password) != 1)
    {
        ui->errorLabel->setText("Incorrect username or password!");
    }
    else
    {
        FileUtils::writeJson(jsonObject, QString::fromStdString(filePath));
        PasswordDialog::close();
    }
}

void PasswordDialog::on_cancelBtn_released()
{
    PasswordDialog::close();
}

void PasswordDialog::setFilePath(string filePath)
{
    this->filePath = filePath;
}

void PasswordDialog::setJsonObject(QJsonObject &jsonObject)
{
    this->jsonObject = jsonObject;
}
