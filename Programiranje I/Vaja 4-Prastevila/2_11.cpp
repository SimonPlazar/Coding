#include <iostream>
#include <cmath>

using namespace std;

bool praStevilo(int st);

int praInterval(int start, int end);

double povprecjePra(int polje[], int st);

bool isFirstClosest(int val1, int val2, double target);

void Najblizje(int st[]);

int main(int argc, char **argv) {
    int test;
    int st[20];
    double stevilo;

    cout << "Podaj stevilo za povprecje prvih 20 prastevil vecjih od tega stevila: ";
    cin >> test;

    cout << "Povprecje prvih 20 prastevil vecjih od tega stevila: " << povprecjePra(st, test) << endl;

    cout << "Stevilo prastevil v razponu od vkljucno -217 do vkljucno 9001 je " << praInterval(-217, 9001) << endl;

    Najblizje(st);

    return 0;
}

bool praStevilo(int st) {
    if (st == 0 || st == 1 || st < 0) {
        return false;
    } else {
        for (int i = 2; i <= (st / 2); i++) {
            if (st % i == 0) {
                return false;
            }
        }
    }
    return true;
}

int praInterval(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (praStevilo(i)) {
            count++;
        }
    }
    return count;
}

double povprecjePra(int polje[], int st) {
    int vsota = 0;
    int count = 0;

    for (int i = st; count < 20; i++) {
        if (praStevilo(i)) {
            polje[count] = i;
            vsota += i;
            count++;
            cout << i << ", ";
        }
    }
    cout << endl;
    return round((vsota / 20));
}

bool isFirstClosest(int val1, int val2, double target) {
    if (target - val2 >= val1 - target) {
        return false;
    } else {
        return true;
    }
}

void Najblizje(int st[]) {
    int najblizje;
    double stevilo;

    cout << "Podaj stevilo za koren: ";
    cin >> stevilo;

    stevilo = sqrt(stevilo);

    for (int i = 0; i < 20; i++) {
        if (stevilo <= st[0]) {
            najblizje = st[0];
        } else if (stevilo >= st[19]) {
            najblizje = st[19];
        } else if (st[i] <= stevilo && st[i + 1] >= stevilo) {
            if (isFirstClosest(st[i], st[i + 1], stevilo)) {
                najblizje = st[i];
            } else {
                najblizje = st[i + 1];
            }
        }
    }
    cout << "Najblizje stevilo: " << najblizje << endl;
}
