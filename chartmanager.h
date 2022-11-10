#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H
#include <mainwindow.h>
#include <vector>
#include <qcustomplot.h>

class ChartManager
{
public:
    ChartManager();
    ~ChartManager();

    void updateCharts(std::map<QString, QCustomPlot*> data);
    std::vector<double> getTPodTemperature();
    std::vector<double> getTPodPressure();
    std::vector<double> getTPodState();
};

#endif // CHARTMANAGER_H
