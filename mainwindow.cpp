#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "fileutils.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include "udphandler.h"
#include <QDebug>
#include <ctime>
#include <QtConcurrent/QtConcurrent>
#include <chartmanager.h>
#include <passworddialog.h>
#include <qthread.h>
#include <thread>
#include <invalidsavewindow.h>
#include <map>
#include <tablebuilder.h>

using std::string;

static QTimer * timer;
static ChartManager * chartManager;
static thread * listenerThread;
static std::map<QString, QCustomPlot*> chartMap;
static DataManager * dataManager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    dataManager = DataManager::getInstance();

    ui->setupUi(this);
    ui->LiveCapture->hide();
    ui->settingsMenu->hide();
    ui->logMenu->hide();

    connect(ui->tPodLeftChart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(tPodLeftChartClick(QMouseEvent*)));
    connect(ui->tPodRightChart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(tPodRightChartClick(QMouseEvent*)));

    init();
}

void MainWindow::tPodLeftChartClick(QMouseEvent * e)
{   
    QString left = ui->tPodLeftLabel->text();
    QString top = ui->tPodBigLabel->text();

    ui->tPodBigLabel->setText(left);
    ui->tPodLeftLabel->setText(top);

    chartMap.erase(top);
    chartMap.erase(left);

    chartMap[top] = ui->tPodLeftChart;
    chartMap[left] = ui->tPodBigChart;

    chartManager->updateCharts(chartMap);
}

void MainWindow::tPodRightChartClick(QMouseEvent * e)
{
    QString right = ui->tPodRightLabel->text();
    QString top = ui->tPodBigLabel->text();

    ui->tPodBigLabel->setText(right);
    ui->tPodRightLabel->setText(top);

    chartMap.erase(top);
    chartMap.erase(right);

    chartMap[top] = ui->tPodRightChart;
    chartMap[right] = ui->tPodBigChart;

    chartManager->updateCharts(chartMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    chartMap[ui->tPodBigLabel->text()] = ui->tPodBigChart;
    chartMap[ui->tPodLeftLabel->text()] = ui->tPodLeftChart;
    chartMap[ui->tPodRightLabel->text()] = ui->tPodRightChart;

    listenerThread = new class thread(&MainWindow::run, this);
}


void MainWindow::main()
{
    chartManager->updateCharts(chartMap);
    QJsonObject obj = FileUtils::readDevicesFile()["Thruster Pod"].toObject();
    QJsonObject settings = obj["settings"].toObject();
    QJsonObject temp = settings["temperature"].toObject();
    QJsonObject press = settings["pressure"].toObject();
    QJsonObject state = settings["state"].toObject();

    ui->tPodTempLabel->setText(QString::number(dataManager->getTPodManager().getAvgTemp()) + " " + temp["unit"].toString());
    ui->tPodPressLabel->setText(QString::number(dataManager->getTPodManager().getAvgPress()) + " " + press["unit"].toString());
    ui->tPodStateLabel->setText(QString::number(dataManager->getTPodManager().getAvgState()));
    ui->tPodWaterLabel->setText(QString::number(dataManager->getTPodManager().getWaterStatus()));
}

// Pressing the Exit button closes the application
void MainWindow::on_pushButton_Exit_released()
{
    QMainWindow::close();
}

void MainWindow::on_pushButton_LiveCapture_released()
{
    ui->LiveCapture->show();
    ui->mainMenu->hide();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(main()));
    timer->start(1000);
}

void MainWindow::on_pushButton_Settings_released()
{
    ui->settingsMenu->show();
    ui->mainMenu->hide();
}

void MainWindow::on_pushButton_Log_released()
{
    ui->logMenu->show();
    ui->mainMenu->hide();
}

void MainWindow::on_pushButton_Exit_2_released()
{
    ui->mainMenu->show();
    ui->logMenu->hide();
}

void MainWindow::on_ePodBtn_Log_released()
{
    QTableWidget * table = ui->table;
    QStringList tableHeader;

    table->setRowCount(1);
    table->setColumnCount(1000);
    table->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 21px;"
                                             "font-weigh: bold;"
                                             "background-color: rgb(47, 161, 228);}");
    table->horizontalHeader()->font().bold();

    for(int i = 0; i < 1000; i++)
    {
        tableHeader<< QString::number(i);
    }

    table->setHorizontalHeaderLabels(tableHeader);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    table->setStyleSheet("QTableView {background-color: rgb(59, 120, 216);"
                         "color: rgb(20, 26, 85);"
                         "font-size:20px;}"
                         "border: 2px solid black;");


    for(int i = 0; i < 1000; i++)
    {
        table->setItem(0, i, new QTableWidgetItem("test"));
    }
}

void MainWindow::run()
{
    qDebug() << "running";
}

// Function for loading all the current device settings
// from the config files into their appropriate textboxes
void MainWindow::loadSettings(QString deviceName)
{
    ui->deviceName_Label->setText(deviceName);
    ui->deviceName_Label->setAlignment(Qt::AlignCenter);
    TableBuilder::buildTable(ui->settingsTable, deviceName);
}

void MainWindow::on_mainMenuBtn_released()
{
    ui->mainMenu->show();
    ui->LiveCapture->hide();
    timer->stop();
}

void MainWindow::on_tPod_Settings_released()
{
    loadSettings("Thruster Pod");
}

// Save button on the Settings window
void MainWindow::on_pushButton_Save_3_released()
{
    if(!ui->deviceName_Label->text().isEmpty()) {
        QJsonObject obj = FileUtils::readDevicesFile();
        QJsonObject tPod = obj["Thruster Pod"].toObject();
        QJsonObject settings = obj["settings"].toObject();

        QStringList list;
        list << "temperature" << "pressure" << "state" << "water";

        for(int i = 0; i < ui->settingsTable->rowCount(); i++)
        {
            QJsonObject temp = settings[list.at(i)].toObject();

            temp["upperBound"] = ui->settingsTable->item(i, 0)->text().toDouble();
            temp["lowerBound"] = ui->settingsTable->item(i, 1)->text().toDouble();
            temp["upperThreshold"] = ui->settingsTable->item(i, 2)->text().toDouble();
            temp["lowerThreshold"] = ui->settingsTable->item(i, 3)->text().toDouble();
            temp["unit"] = ui->settingsTable->item(i, 4)->text();

            settings[list.at(i)] = temp;
        }

        tPod["settings"] = settings;
        obj["Thruster Pod"] = tPod;

        PasswordDialog passwordDialog;
        passwordDialog.setJsonObject(obj);
        passwordDialog.setFilePath("/Users/vitaliytrach/Desktop/School/Capstone2/capstone/config/config.json");
        passwordDialog.setModal(true);
        passwordDialog.exec();
    }
}

// Clearing the table when going back to main menu
void MainWindow::on_mainMenuSettings_released()
{
    ui->settingsTable->setRowCount(0);
    ui->settingsTable->setColumnCount(0);
    ui->settingsTable->clear();
    ui->settingsTable->clearContents();
    ui->mainMenu->show();
    ui->settingsMenu->hide();
}

void MainWindow::on_ePod_Settings_released()
{

}

void MainWindow::on_aeBoard_Settings_released()
{

}

void MainWindow::on_strain_Settings_released()
{

}

void MainWindow::on_rBoard_Settings_released()
{

}
