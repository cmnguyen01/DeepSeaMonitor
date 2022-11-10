#include "thrusterpodmanager.h"
#include <vector>
#include <cmath>

static std::vector<ThrusterPod*> thrusterPods;

ThrusterPodManager::ThrusterPodManager()
{

}

void ThrusterPodManager::addThrusterPod(ThrusterPod *tPod)
{
    if(thrusterPods.size() >= 100)
    {
        thrusterPods.erase(thrusterPods.begin());
    }

    thrusterPods.push_back(tPod);
    calculateAverages();
}

std::vector<ThrusterPod*> ThrusterPodManager::getThrusterPods()
{
    return thrusterPods;
}

ThrusterPod * ThrusterPodManager::getThrusterPod(int index)
{
    return thrusterPods.at(index);
}

void ThrusterPodManager::calculateAverages()
{
    avgTemp = 0;
    avgPress = 0;

    lowestTemp = 100;
    highestTemp = 0;

    lowestPress = 100;
    highestPress = 0;

    for(unsigned int i = 0; i < thrusterPods.size(); i++)
    {
        if(thrusterPods.at(i)->getTemperature() > highestTemp)
        {
            highestTemp = thrusterPods.at(i)->getTemperature();
        }

        if(thrusterPods.at(i)->getTemperature() < lowestTemp)
        {
            lowestTemp = thrusterPods.at(i)->getTemperature();
        }

        if(thrusterPods.at(i)->getPressure() > highestPress)
        {
            highestPress = thrusterPods.at(i)->getPressure();
        }

        if(thrusterPods.at(i)->getPressure() < lowestPress)
        {
            lowestPress = thrusterPods.at(i)->getPressure();
        }

        avgTemp += thrusterPods.at(i)->getTemperature();
        avgPress += thrusterPods.at(i)->getPressure();
        avgState += thrusterPods.at(i)->getState();
        lastWaterReading = thrusterPods.at(i)->getWater();
    }

    if(thrusterPods.size() > 0)
    {
        avgTemp = avgTemp / thrusterPods.size();
        avgPress = avgPress / thrusterPods.size();
        avgState = avgState / thrusterPods.size();
    }
}

// GETTERS

double ThrusterPodManager::getHighestTemp()
{
    return highestTemp;
}

double ThrusterPodManager::getLowestTemp()
{
    return lowestTemp;
}

double ThrusterPodManager::getAvgTemp()
{
    return avgTemp;
}

double ThrusterPodManager::getHighestPress()
{
    return highestPress;
}

double ThrusterPodManager::getLowestPress()
{
    return lowestPress;
}

double ThrusterPodManager::getAvgPress()
{
    return avgPress;
}

int ThrusterPodManager::getAvgState()
{
    return std::round(avgState);
}

bool ThrusterPodManager::getWaterStatus()
{
    return lastWaterReading;
}


