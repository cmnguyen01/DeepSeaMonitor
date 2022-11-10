#ifndef THRUSTERPODMANAGER_H
#define THRUSTERPODMANAGER_H
#include <thrusterpod.h>

class ThrusterPodManager
{
private:
    double lowestTemp = 0;
    double highestTemp = 0;
    double avgTemp = 0;

    double lowestPress = 0;
    double highestPress = 0;
    double avgPress = 0;

    double avgState = 0;
    bool lastWaterReading = 0;

public:
    ThrusterPodManager();
    void addThrusterPod(ThrusterPod * tPod);
    std::vector<ThrusterPod*> getThrusterPods();
    ThrusterPod * getThrusterPod(int index);
    void calculateAverages();

    double getHighestTemp();
    double getLowestTemp();
    double getAvgTemp();

    double getHighestPress();
    double getLowestPress();
    double getAvgPress();

    int getAvgState();
    bool getWaterStatus();
};

#endif // THRUSTERPODMANAGER_H
