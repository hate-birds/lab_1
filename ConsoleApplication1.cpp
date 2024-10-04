#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

#define THRESHOLD 0.5

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Lamp {
private:
    double intensity; // Сила света лампы в люменах
    double power;     // Потребляемая мощность лампы в ваттах
    bool isOn;        // Состояние лампы: включена или выключена

public:
    Lamp() : intensity(0.0), power(0.0), isOn(false) {}

    Lamp(double intensity, double power, bool isOn)
        : intensity(intensity), power(power), isOn(isOn) {
        if (intensity < 0.0 || power < 0.0) {
            throw invalid_argument("Intensity and power must be non-negative.");
        }
    }

    Lamp(const Lamp& other)
        : intensity(other.intensity), power(other.power), isOn(other.isOn) {}

    double getIntensity() const { return intensity; }
    double getPower() const { return power; }
    bool getIsOn() const { return isOn; }

    void setIntensity(double intensity) {
        if (intensity < 0.0) {
            throw invalid_argument("Intensity must be non-negative.");
        }
        this->intensity = intensity;
    }

    void setPower(double power) {
        if (power < 0.0) {
            throw invalid_argument("Power must be non-negative.");
        }
        this->power = power;
    }

    void setIsOn(bool isOn) { this->isOn = isOn; }

    double calculateIllumination(double x, double y, double lampX, double lampY) const {
        if (!isOn) return 0.0;

        double distanceSquared = (x - lampX) * (x - lampX) + (y - lampY) * (y - lampY);
        return intensity / (4 * M_PI * distanceSquared);
    }
};

double calculateTotalIllumination(const vector<Lamp>& lamps, double x, double y) {
    double totalIllumination = 0.0;
    int lampX = 0, lampY = 0;

    for (const Lamp& lamp : lamps) {
        totalIllumination += lamp.calculateIllumination(x, y, lampX, lampY);
        lampX++;
        lampY++;
    }

    return totalIllumination;
}

int main() {
    int numLamps;
    cout << "Enter the number of lamps: ";
    cin >> numLamps;

    vector<Lamp> lamps;
    for (int i = 0; i < numLamps; ++i) {
        double intensity, power;
        bool isOn;
        cout << "Enter intensity (lumens) for lamp " << i + 1 << ": ";
        cin >> intensity;
        cout << "Enter power (watts) for lamp " << i + 1 << ": ";
        cin >> power;
        cout << "Is the lamp on? (1 for yes, 0 for no): ";
        cin >> isOn;
        lamps.push_back(Lamp(intensity, power, isOn));
    }

    double x, y;
    cout << "Enter the x-coordinate of the point: ";
    cin >> x;
    cout << "Enter the y-coordinate of the point: ";
    cin >> y;

    double totalIllumination = calculateTotalIllumination(lamps, x, y);

    cout << "Total illumination at point (" << x << ", " << y << ") is: "
        << totalIllumination << " lumens." << endl;

    return 0;
}
