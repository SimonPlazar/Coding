#include <iostream>
#include <cmath>
#include <ctime>

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
    cout << "7 ... Print last 5" << endl;
    cout << "8 ... Print back" << endl;
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

void fillArray(float *array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        array[i] = oneDecimalPlace(randomDoubleInterval(0.5, 2.5));
    }
}

void printArray(const float *array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        cout << ((i > 0) ? ", " : "") << array[i];
    }
}

void printArrayBack(const float *array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        cout << ((i > 0) ? ", " : "") << *(array+size-i-1);
    }
}

float getAvg(const float *array, const unsigned int size) {
    float sum = 0;
    for (unsigned int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

void printLessThanAvg(const float *array, const unsigned int size, float avg) {
    cout << "Days below average water intakes:" << endl;
    for (unsigned int i = 0; i < size; i++) {
        if (array[i] < avg)
            cout << "Day " << i + 1 << endl;
    }
}

void printMax(const float *array, const unsigned int size) {
    float max = 0;
    for (unsigned int i = 0; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }
    cout << "Max water intake in a single day: " << max;
}

void printInbounds(const float *array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        if (array[i] < 2.5 && array[i] > 2)
            cout << "Day " << i + 1 << endl;
    }
}

void printLastIXs(const float *array, const unsigned int size, int num) {
    for (unsigned int i = size; i < size+num; i++) {
        cout << "Day " << i-num+1 << " " << array[i-num] << endl;
    }
}

int main() {
    const unsigned int days = 30;
    float *waterIntakes = new float[days];

    srand(time(nullptr));

    bool running = true;
    int selection;

    do {
        menu();
        cin >> selection;
        switch (selection) {
            case 1:
                fillArray(waterIntakes, days);
                break;
            case 2:
                printArray(waterIntakes, days);
                break;
            case 3:
                cout << "Average water intakes: " << getAvg(waterIntakes, days);
                break;
            case 4:
                printLessThanAvg(waterIntakes, days, getAvg(waterIntakes, days));
                break;
            case 5:
                printMax(waterIntakes, days);
                break;
            case 6:
                printInbounds(waterIntakes, days);
                break;
            case 7:
                printLastIXs(waterIntakes, days, 5);
                break;
            case 8:
                printArrayBack(waterIntakes, days);
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

    delete[] waterIntakes;

    return 0;
}