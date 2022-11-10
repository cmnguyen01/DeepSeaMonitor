#ifndef THRUSTERPOD_H
#define THRUSTERPOD_H
#include <string>

class ThrusterPod
{
private:
    std::string name;
    double temperature;
    double pressure;
    int state;
    bool water;
public:
    ThrusterPod();
    std::string getName();

    void setName(std::string n);
    void setTemperature(double t);
    void setPressure(double p);
    void setState(int s);
    void setWater(bool w);

    double getTemperature();
    double getPressure();
    int getState();
    bool getWater();
};

#endif // THRUSTERPOD_H
