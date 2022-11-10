#include "datamanager.h"
#include <thrusterpod.h>
#include <vector>
#include <QDebug>
#include <thrusterpodmanager.h>

static DataManager * dataManager = nullptr;
static std::vector<ThrusterPod*> thrusterPods;
static ThrusterPodManager tPodManager;

DataManager::DataManager()
{}

DataManager * DataManager::getInstance()
{
    if(dataManager == nullptr)
    {
        dataManager = new DataManager();
    }

    return dataManager;
}

void DataManager::addThrusterPod(ThrusterPod *tPod)
{
    tPodManager.addThrusterPod(tPod);
}

ThrusterPodManager DataManager::getTPodManager()
{
    return tPodManager;
}



