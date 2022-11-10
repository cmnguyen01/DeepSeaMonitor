#include "chartmanager.h"
#include <mainwindow.h>
#include <qdebug.h>
#include <time.h>
#include <map>
#include <datamanager.h>
#include <fileutils.h>
#include <QJsonObject>

static DataManager * dm;

ChartManager::ChartManager()
{
    srand(time(0));
    dm = DataManager::getInstance();
}

ChartManager::~ChartManager()
{

}

void ChartManager::updateCharts(std::map<QString, QCustomPlot*> data)
{
    QVector<double> chart1, chart2, chart3, x(100);

    chart1 = QVector<double>::fromStdVector(getTPodState());
    chart2 = QVector<double>::fromStdVector(getTPodPressure());
    chart3 = QVector<double>::fromStdVector(getTPodTemperature());

    QJsonObject tPod = FileUtils::readDevicesFile()["Thruster Pod"].toObject();
    QJsonObject settings = tPod["settings"].toObject();

    for (std::map<QString, QCustomPlot*>::iterator it = data.begin(); it != data.end(); ++it)
    {
        QJsonObject obj;

        QCustomPlot * chart = it->second;

        QVector<double> y;

        chart->addGraph();

        if(it->first.compare("Temperature") == 0)
        {
            obj = settings["temperature"].toObject();
            y = chart3;
            chart->yAxis->setRange(obj["lowerBound"].toDouble(), obj["upperBound"].toDouble());
        }
        else if(it->first.compare("Pressure") == 0)
        {
            obj = settings["pressure"].toObject();
            y = chart2;
            chart->yAxis->setRange(obj["lowerBound"].toDouble(), obj["upperBound"].toDouble());
        }
        else if(it->first.compare("State") == 0)
        {
            obj = settings["state"].toObject();
            y = chart1;
            chart->yAxis->setRange(obj["lowerBound"].toDouble(), obj["upperBound"].toDouble());
        }

        for(int i = 0; i < 100; i++) {
            x[i] = i;
        }

        chart->graph(0)->setData(x, y);
        chart->xAxis->setLabel("time");
        chart->yAxis->setLabel(it->first);
        chart->xAxis->setRange(0, 100);
        chart->replot();
    }
}

// Getting Temperature of TPods
std::vector<double> ChartManager::getTPodTemperature()
{
    std::vector<ThrusterPod*> tPods = dm->getTPodManager().getThrusterPods();
    std::vector<double> temp;

    for(ThrusterPod * tPod : tPods)
    {
        temp.push_back(tPod->getTemperature());
    }

    if(temp.size() < 100)
    {
        for(int i = temp.size(); i < 100; i++)
        {
            temp.push_back(1);
        }
    }

    return temp;
}

// Getting thruster pod pressure
std::vector<double> ChartManager::getTPodPressure()
{
    std::vector<ThrusterPod*> tPods = dm->getTPodManager().getThrusterPods();
    std::vector<double> press;

    for(ThrusterPod * tPod : tPods)
    {
        press.push_back(tPod->getPressure());
    }

    if(press.size() < 100)
    {
        for(int i = press.size(); i < 100; i++)
        {
            press.push_back(1);
        }
    }

    return press;
}

// Getting Thruster Pod State
std::vector<double> ChartManager::getTPodState()
{
    std::vector<ThrusterPod*> tPods = dm->getTPodManager().getThrusterPods();
    std::vector<double> state;

    for(ThrusterPod * tPod : tPods)
    {
        state.push_back((double) tPod->getState());
    }

    if(state.size() < 100)
    {
        for(int i = state.size(); i < 100; i++)
        {
            state.push_back(1);
        }
    }

    return state;
}
