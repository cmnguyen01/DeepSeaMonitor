#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include <string>
#include <QJsonObject>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    void setFilePath(std::string filePath);
    void setJsonObject(QJsonObject &jsonObject);
    ~PasswordDialog();

private slots:
    void on_loginBtn_released();

    void on_cancelBtn_released();

private:
    Ui::PasswordDialog *ui;
    std::string filePath;
    QJsonObject jsonObject;
    void checkCredentials(std::string username, std::string password);
};

#endif // PASSWORDDIALOG_H
