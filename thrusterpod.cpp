#include "thrusterpod.h"
#include <string>


ThrusterPod::ThrusterPod()
{

}

// SETTERS

void ThrusterPod::setName(std::string n)
{
    name = n;
}

void ThrusterPod::setTemperature(double t)
{
    temperature = t;
}

void ThrusterPod::setPressure(double p)
{
    pressure = p;
}

void ThrusterPod::setState(int s)
{
    state = s;
}

void ThrusterPod::setWater(bool w)
{
    water = w;
}

// GETTERS

std::string ThrusterPod::getName()
{
    return name;
}

double ThrusterPod::getTemperature()
{
    return temperature;
}

double ThrusterPod::getPressure()
{
    return pressure;
}

int ThrusterPod::getState()
{
    return state;
}

bool ThrusterPod::getWater()
{
    return water;
}
