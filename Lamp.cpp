#include "Lamp.h"
#include <cassert>


Lamp::Lamp() : intensity(0.0), power(0.0), isOn(false) {}

Lamp::Lamp(double intensity, double power, bool isOn)
    : intensity(intensity), power(power), isOn(isOn) {
    if (intensity < 0.0 || power < 0.0) {
        throw invalid_argument("Intensity and power must be non-negative.");
    }
}

Lamp::Lamp(const Lamp& other)
    : intensity(other.intensity), power(other.power), isOn(other.isOn) {}

double Lamp::getIntensity() const { return intensity; }
double Lamp::getPower() const { return power; }
bool Lamp::getIsOn() const { return isOn; }

void Lamp::setIntensity(double intensity) {
    if (intensity < 0.0) {
        throw invalid_argument("Intensity must be non-negative.");
    }
    this->intensity = intensity;
}

void Lamp::setPower(double power) {
    if (power < 0.0) {
        throw invalid_argument("Power must be non-negative.");
    }
    this->power = power;
}

void Lamp::setIsOn(bool isOn) {
    this->isOn = isOn;
}

string Lamp::identify() const {
    return "Lamp";
}

double Lamp::calculateIllumination(double x, double y, double lampX, double lampY) const {
    if (!isOn) return 0.0;
    double distanceSquared = (x - lampX) * (x - lampX) + (y - lampY) * (y - lampY);
    return intensity / (4 * M_PI * distanceSquared);
}


LedLamp::LedLamp()
    : Lamp(), redMaxIntensity(0.0), greenMaxIntensity(0.0), blueMaxIntensity(0.0),
    redIntensity(0.0), greenIntensity(0.0), blueIntensity(0.0) {}

LedLamp::LedLamp(double redMax, double greenMax, double blueMax, double redInt, double greenInt, double blueInt, double power, bool isOn)
    : Lamp(redInt + greenInt + blueInt, power, isOn),
    redMaxIntensity(redMax), greenMaxIntensity(greenMax), blueMaxIntensity(blueMax),
    redIntensity(redInt), greenIntensity(greenInt), blueIntensity(blueInt) {
    if (redInt < 0.0 || greenInt < 0.0 || blueInt < 0.0 ||
        redMax < 0.0 || greenMax < 0.0 || blueMax < 0.0) {
        throw invalid_argument("Intensities must be non-negative.");
    }
}

double LedLamp::calculateCurrentIntensity() const {
    return redMaxIntensity * redIntensity + greenMaxIntensity * greenIntensity + blueMaxIntensity * blueIntensity;
}

string LedLamp::identify() const {
    return "LED Lamp";
}

void LedLamp::setRedIntensity(double intensity) {
    if (intensity < 0.0 || intensity > redMaxIntensity) {
        throw invalid_argument("Invalid red intensity.");
    }
    redIntensity = intensity;
}

void LedLamp::setGreenIntensity(double intensity) {
    if (intensity < 0.0 || intensity > greenMaxIntensity) {
        throw invalid_argument("Invalid green intensity.");
    }
    greenIntensity = intensity;
}

void LedLamp::setBlueIntensity(double intensity) {
    if (intensity < 0.0 || intensity > blueMaxIntensity) {
        throw invalid_argument("Invalid blue intensity.");
    }
    blueIntensity = intensity;
}

double LedLamp::calculateIllumination(double x, double y, double lampX, double lampY) const {
    if (!isOn) return 0.0;
    double currentIntensity = calculateCurrentIntensity();
    double distanceSquared = (x - lampX) * (x - lampX) + (y - lampY) * (y - lampY);
    return currentIntensity / (4 * M_PI * distanceSquared);
}

double calculateTotalIllumination(const vector<Lamp*>& lamps, double x, double y) {
    double totalIllumination = 0.0;
    int lampX = 0, lampY = 0;

    for (const Lamp* lamp : lamps) {
        totalIllumination += lamp->calculateIllumination(x, y, lampX, lampY);
        lampX++;
        lampY++;
    }

    return totalIllumination;
}

void testLamp() {
    Lamp lamp1;
    assert(lamp1.getIntensity() == 0.0);
    assert(lamp1.getPower() == 0.0);
    assert(!lamp1.getIsOn());

    Lamp lamp2(800.0, 60.0, true);
    assert(lamp2.getIntensity() == 800.0);
    assert(lamp2.getPower() == 60.0);
    assert(lamp2.getIsOn());

    Lamp lamp3(lamp2);
    assert(lamp3.getIntensity() == 800.0);
    assert(lamp3.getPower() == 60.0);
    assert(lamp3.getIsOn());

    lamp3.setIntensity(1000.0);
    lamp3.setPower(70.0);
    lamp3.setIsOn(false);
    assert(lamp3.getIntensity() == 1000.0);
    assert(lamp3.getPower() == 70.0);
    assert(!lamp3.getIsOn());

    double illumination = lamp2.calculateIllumination(1.0, 1.0, 0.0, 0.0);
    assert(illumination > THRESHOLD);

    cout << "All regular lamps tests passed successfully!" << endl;
}

void testLedLamp() {
    LedLamp led(100.0, 200.0, 150.0, 0.5, 0.7, 0.6, 50.0, true);
    assert(led.calculateCurrentIntensity() > 0);
    assert(led.getPower() == 50.0);
    assert(led.getIsOn());
    assert(led.identify() == "LED Lamp");

    led.setRedIntensity(0.3);
    assert(led.calculateCurrentIntensity() > 0);

    cout << "LED Lamp tests passed successfully!" << endl;
}
