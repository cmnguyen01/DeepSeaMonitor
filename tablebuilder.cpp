#include "tablebuilder.h"
#include <QTableWidget>
#include <QJsonObject>
#include <fileutils.h>
#include <QDebug>

TableBuilder::TableBuilder()
{

}

// TODO:: Unhardcode this
void TableBuilder::buildTable(QTableWidget * table, QString deviceName)
{
    QJsonObject jsonObj = FileUtils::readDevicesFile();
    QJsonValue val = jsonObj.value(deviceName);

    QJsonObject device = val.toObject();
    QJsonObject settings = device["settings"].toObject();

    table->setRowCount(4);
    table->setColumnCount(5);
    QStringList listH, listV;
    listH << "Upper Bound" << "Lower Bound" << "Upper Threshold" << "Lower Threshold" << "Unit";
    listV << "Temperature     " << "Pressure     " << "State     " << "Water     ";

    table->setEditTriggers(QAbstractItemView::DoubleClicked);
    table->setShowGrid(true);
    table->setVerticalHeaderLabels(listV);
    table->setHorizontalHeaderLabels(listH);

    QStringList list;
    list << "temperature" << "pressure" << "state" << "water";
    int col = 0;

    for(int i = 0; i < list.size(); i ++)
    {
        QJsonObject o = settings[list.at(i)].toObject();

        double upperB = o["upperBound"].toDouble();
        table->setItem(col, 0, new QTableWidgetItem(QString::number(upperB)));

        double lowerB = o["lowerBound"].toDouble();
        table->setItem(col, 1, new QTableWidgetItem(QString::number(lowerB)));

        double upperT = o["upperThreshold"].toDouble();
        table->setItem(col, 2, new QTableWidgetItem(QString::number(upperT)));

        double lowerT = o["lowerThreshold"].toDouble();
        table->setItem(col, 3, new QTableWidgetItem(QString::number(lowerT)));

        QString unit = o["unit"].toString();
        table->setItem(col, 4, new QTableWidgetItem(unit));

        col++;
    }

    int cols = 5;
    int rows = 4;

    for(int i = 0; i < cols; i++)
    {
        table->setColumnWidth(i, (table->width() - 110) / cols);
    }

    for(int i = 0; i < rows; i++)
    {
        table->setRowHeight(i, (table->height() - 30) / rows);
    }
}


