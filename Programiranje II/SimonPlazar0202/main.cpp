#include <iostream>
#include <vector>
#include <ctime>
#include "WaterIntake.h"
#include <cmath>

using namespace std;

void menu() {
    cout << "============================" << endl;
    cout << "=========== MENU ===========" << endl;
    cout << "============================" << endl;
    cout << "1 ... GENERATE WATER INTAKES" << endl;
    cout << "2 ... PRINT WATER INTAKES" << endl;
    cout << "3 ... PRINT AVERAGE INTAKES" << endl;
    cout << "4 ... PRINT < AVERAGE INTAKES DAYS" << endl;
    cout << "5 ... MAX INTAKES DAY" << endl;
    cout << "6 ... INBOUNDS DAYS" << endl;
    cout << "7 ... Increase intake by 20%" << endl;
    cout << "8 ... days over 2l" << endl;
    cout << "0 ... EXIT" << endl;
    cout << "============================" << endl;
    cout << "Select:";
}

float randomDouble() {
    //random double from 0-1
    return ((float) rand()) / ((float) RAND_MAX);
}

float randomDoubleInterval(float start, float end) {
    //random number on a given interval
    return randomDouble() * (end - start) + start;
}

float oneDecimalPlace(float number) {
    //trunc rounds to the closest integer
    return trunc(number * 10) / 10;
}

void fillVector(vector<WaterIntake *> &waterIntakes) {
    for (unsigned int i = 0; i < waterIntakes.size(); i++) {
        waterIntakes.push_back(new WaterIntake(i + 1, 3, 2022, oneDecimalPlace(randomDoubleInterval(0.5, 3.5))));
    }
}

void printVector(const vector<WaterIntake *> &waterIntakes) {
    for (unsigned int i = 0; i < waterIntakes.size(); i++)
        cout << waterIntakes[i]->toString() << ((i < waterIntakes.size() - 1) ? ", " : ".") << std::endl;
}

float getAvg(vector<WaterIntake *> &waterIntakes) {
    float sum = 0;
    for (unsigned int i = 0; i < waterIntakes.size(); i++) {
        sum += waterIntakes[i]->getQuantity();
    }
    return sum / waterIntakes.size();
}

void printLessThanAvg(vector<WaterIntake *> &waterIntakes, float avg) {
    cout << "Days below average water intakes:" << endl;
    for (unsigned int i = 0; i < waterIntakes.size(); i++) {
        if (waterIntakes[i]->getQuantity() < avg)
            cout << "Day " << waterIntakes[i]->getDay() << endl;
    }
}

void printMax(vector<WaterIntake *> &waterIntakes) {
    float max = 0;
    for (unsigned int i = 0; i < waterIntakes.size(); i++) {
        if (waterIntakes[i]->getQuantity() > max)
            max = waterIntakes[i]->getQuantity();
    }
    cout << "Max water intake in a single day: " << max << endl;
}

void printInbounds(vector<WaterIntake *> &waterIntakes) {
    for (unsigned int i = 0; i < waterIntakes.size(); i++) {
        if (waterIntakes[i]->getQuantity() < 2.5 && waterIntakes[i]->getQuantity() > 2)
            cout << "Day " << waterIntakes[i]->getDay() << endl;
    }
}

void increseIntake(vector<WaterIntake *> &waterIntakes, float percentage) {
    for (int i = 0; i < waterIntakes.size(); i++) {
        waterIntakes[i]->addQuantity(waterIntakes[i]->getQuantity() * percentage);
    }
}

vector<WaterIntake *> getMoreThan(vector<WaterIntake *> &waterIntakes, float limit) {
    vector<WaterIntake *> inLimit;
    for (int i = 0; i < waterIntakes.size(); i++) {
        if (waterIntakes[i]->getQuantity() > limit)
            inLimit.push_back(waterIntakes[i]);
    }
    return inLimit;
}

void delWater(vector<WaterIntake *> &waterIntakes){
    for (int i = 0; i < waterIntakes.size(); ++i) {
        delete waterIntakes[i];
    }
    waterIntakes.clear();
}

int main() {
    const unsigned int days = 30;
    vector<WaterIntake *> waterIntakes;

    srand(time(nullptr));

    bool running = true;
    int selection;

    do {
        menu();
        cin >> selection;
        switch (selection) {
            case 1:
                fillVector(waterIntakes);
                break;
            case 2:
                printVector(waterIntakes);
                break;
            case 3:
                cout << "Average water intakes: " << getAvg(waterIntakes);
                break;
            case 4:
                printLessThanAvg(waterIntakes, getAvg(waterIntakes));
                break;
            case 5:
                printMax(waterIntakes);
                break;
            case 6:
                printInbounds(waterIntakes);
                break;
            case 7:
                increseIntake(waterIntakes, 0.2);
                break;
            case 8:
                waterIntakes = getMoreThan(waterIntakes, 2);
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "Wrong selection!" << endl;
                break;
        }
        cout << endl;
    } while (running);

    delWater(waterIntakes);

    return 0;
}