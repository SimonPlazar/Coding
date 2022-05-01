#include <iostream>

using namespace std;

unsigned int sumDigits(int number) {
    int sum = 0;
    do {
        sum += (number % 10);
        number /= 10;
    } while (number > 0);

    return sum;
}

bool checkFull(unsigned int number) {
    int sumDivs = 0;
    for (int i = 1; i <= (number / 2); ++i) {
        if (number % i == 0) {
            sumDivs += i;
        }
    }

    if (number == sumDivs)
        return true;
    else
        return false;
}

int main() {
    int input;
    unsigned int sumDigitsVal;

    do {
        cout << "Podaj stevlo:";
        cin >> input;
    } while (input <= 0);

    sumDigitsVal = sumDigits(input);

    cout << "\nVsota stevk: " << sumDigitsVal << endl;

    if (checkFull(sumDigitsVal))
        cout << "Stevlo " << sumDigitsVal << " je polno stevilo";
    else
        cout << "Stevlo " << sumDigitsVal << " ni polno stevilo";
    return 0;
}
