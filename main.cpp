#include "Lamp.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    testLamp();

    testLedLamp();

    int numLamps, numLedLamps;

    cout << "Enter the number of regular lamps: ";
    cin >> numLamps;

    vector<Lamp*> lamps;

    for (int i = 0; i < numLamps; ++i) {
        double intensity, power;
        bool isOn;
        cout << "Enter intensity in lumens for regular lamp " << i + 1 << ": ";
        cin >> intensity;
        cout << "Enter power in watts for regular lamp " << i + 1 << ": ";
        cin >> power;
        cout << "Is the lamp on? (1 for yes, 0 for no): ";
        cin >> isOn;
        lamps.push_back(new Lamp(intensity, power, isOn));
    }

    cout << "Enter the number of LED lamps: ";
    cin >> numLedLamps;

    for (int i = 0; i < numLedLamps; ++i) {
        double redMax, greenMax, blueMax, redInt, greenInt, blueInt, power;
        bool isOn;
        cout << "Enter max red intensity for LED lamp " << i + 1 << ": ";
        cin >> redMax;
        cout << "Enter max green intensity for LED lamp " << i + 1 << ": ";
        cin >> greenMax;
        cout << "Enter max blue intensity for LED lamp " << i + 1 << ": ";
        cin >> blueMax;
        cout << "Enter current red intensity for LED lamp " << i + 1 << ": ";
        cin >> redInt;
        cout << "Enter current green intensity for LED lamp " << i + 1 << ": ";
        cin >> greenInt;
        cout << "Enter current blue intensity for LED lamp " << i + 1 << ": ";
        cin >> blueInt;
        cout << "Enter power in watts for LED lamp " << i + 1 << ": ";
        cin >> power;
        cout << "Is the LED lamp on? (1 for yes, 0 for no): ";
        cin >> isOn;

        lamps.push_back(new LedLamp(redMax, greenMax, blueMax, redInt, greenInt, blueInt, power, isOn));
    }

    double x, y;
    cout << "Enter the x-coordinate of the point: ";
    cin >> x;
    cout << "Enter the y-coordinate of the point: ";
    cin >> y;

    double totalIllumination = calculateTotalIllumination(lamps, x, y);
    cout << "Total illumination at point (" << x << ", " << y << ") is: "
        << totalIllumination << " lumens." << endl;

    for (Lamp* lamp : lamps) {
        delete lamp;
    }

    return 0;
}
