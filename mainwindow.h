#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    void init();
    void loadSettings(QString deviceName);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setChartManager();

    ~MainWindow();

protected:
    void run();

private slots:
    void main();
    void on_pushButton_Exit_released();
    void on_pushButton_LiveCapture_released();
    void on_pushButton_Settings_released();
    void on_pushButton_Log_released();
    void on_pushButton_Exit_2_released();
    void on_ePodBtn_Log_released();
    void on_mainMenuBtn_released();
    void tPodLeftChartClick(QMouseEvent*);
    void tPodRightChartClick(QMouseEvent*);
    void on_ePod_Settings_released();
    void on_tPod_Settings_released();
    void on_aeBoard_Settings_released();
    void on_strain_Settings_released();
    void on_rBoard_Settings_released();
    void on_pushButton_Save_3_released();
    void on_mainMenuSettings_released();
};

#endif // MAINWINDOW_H
