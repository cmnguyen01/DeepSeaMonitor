#include "datadecoder.h"
#include <string>
#include <vector>
#include <fileutils.h>

#include <QDebug>

using namespace std;
using std::string;

dataDecoder::dataDecoder()
{
    dataManager = DataManager::getInstance();
}

dataDecoder::~dataDecoder()
{

}

void dataDecoder::updateBuffer(char * newBuffer, int size)
{
    buffer = new char[size];
    this->size = size;

    for(int i = 0; i < size; i++)
    {
        if(newBuffer[i] != '\0')
        {
            buffer[i] = newBuffer[i];
        }
    }
}

void dataDecoder::parseData()
{
    string deviceName = "";

    bufferIndex = 0;

    while(buffer[bufferIndex] != '/')
    {
        deviceName += buffer[bufferIndex];
        bufferIndex++;
    }

    if(deviceName.compare("ThrusterPodA") == 0)
    {
        bufferIndex++;
        parseThrusterPod();
    }
}

void dataDecoder::parseThrusterPod()
{
    ThrusterPod * tPod = new ThrusterPod();

    std::string name, temp, pressure, water, state;

    name = "ThrusterPodA";
    tPod->setName(name);

    water = findNextItem().c_str();
    tPod->setWater(std::stoi(water));

    temp = findNextItem();
    tPod->setTemperature(std::stod(temp));

    pressure = findNextItem();
    tPod->setPressure(std::stod(pressure));

    state = findNextItem();
    tPod->setState(std::stoi(state));

    dataManager->addThrusterPod(tPod);
    std::string data = name + "/" + water +"/" + temp + "/" + pressure + "/" + state + "\n";
    FileUtils::writeToBinaryFile(QString::fromStdString(data), "");
}

std::string dataDecoder::findNextItem()
{
    string item = "";

    while(buffer[bufferIndex] != '/')
    {
        item += buffer[bufferIndex];
        bufferIndex++;
    }

    bufferIndex++;
    return item;
}

