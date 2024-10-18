#pragma once
#ifndef LAMP_H
#define LAMP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

#define THRESHOLD 0.5

#define M_PI 3.14159265358979323846
#endif

class Lamp {
protected:
    double intensity;
    double power;
    bool isOn;

public:
    Lamp();
    Lamp(double intensity, double power, bool isOn);
    Lamp(const Lamp& other);
    virtual ~Lamp() = default;

    double getIntensity() const;
    double getPower() const;
    bool getIsOn() const;

    void setIntensity(double intensity);
    void setPower(double power);
    void setIsOn(bool isOn);

    virtual string identify() const;
    virtual double calculateIllumination(double x, double y, double lampX, double lampY) const;
};

class LedLamp : public Lamp {
private:
    double redMaxIntensity;
    double greenMaxIntensity;
    double blueMaxIntensity;
    double redIntensity;
    double greenIntensity;
    double blueIntensity;

public:
    LedLamp();
    LedLamp(double redMax, double greenMax, double blueMax, double redInt, double greenInt, double blueInt, double power, bool isOn);

    double calculateCurrentIntensity() const;
    string identify() const override;

    void setRedIntensity(double intensity);
    void setGreenIntensity(double intensity);
    void setBlueIntensity(double intensity);

    double calculateIllumination(double x, double y, double lampX, double lampY) const override;
};

double calculateTotalIllumination(const vector<Lamp*>& lamps, double x, double y);

void testLamp();
void testLedLamp();


