#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <thrusterpod.h>
#include <thrusterpodmanager.h>
#include <vector>

class DataManager
{
private:
    DataManager();

public:
    static DataManager * getInstance();
    void addThrusterPod(ThrusterPod * tPod);
    ThrusterPodManager getTPodManager();
};

#endif // DATAMANAGER_H
