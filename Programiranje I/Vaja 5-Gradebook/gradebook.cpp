#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

bool isFirstClosest(int val1, int val2, double target) {
    if (target - val2 >= val1 - target) {
        return false;
    } else {
        return true;
    }
}

int IdClosest(int arr[166][6], double stevilo) {
    int najblizje;
    for (int i = 0; i < 166; i++) {
        if (stevilo <= arr[0][5]) {
            najblizje = arr[0][0];
        } else if (stevilo >= arr[165][5]) {
            najblizje = arr[165][0];
        } else if (arr[i][5] <= stevilo && arr[i + 1][5] >= stevilo) {
            if (isFirstClosest(arr[i][5], arr[i + 1][5], stevilo)) {
                najblizje = arr[i][0];
            } else {
                najblizje = arr[i + 1][0];
            }
        }
    }

}

void IzpisClosest(int arr[166][6], string Imena[166]) {
    double avg = 0;
    int id;
    for (int i = 0; i < 166; i++) {
        avg += arr[i][5];
    }
    id = IdClosest(arr, avg);
    cout << "\nPovprecje % OC vseh studentov: " << avg / 166 << endl;
    cout << "Najblizji student: " << Imena[arr[id][1]] << " s " << arr[id][5] << "%" << endl;
}

int cutDecimal(float original) {
    int tmp = (int) (original * 10);
    return (tmp / 10);
}

int random(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(nullptr));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void genPolnaImena(string polnaImena[166], string imena[30], string priimki[20]) {
    for (int i = 0; i < 166; i++) {
        polnaImena[i] = imena[random(0, 29)] + " " + priimki[random(0, 19)];
    }
}

void napolni(int arr[166][6]) {
    for (int i = 0; i < 166; i++) {
        arr[i][0] = i;
        arr[i][1] = (165 - i);
        arr[i][2] = cutDecimal((float) random(1, 100));
        arr[i][3] = cutDecimal((float) random(1, 100));
        arr[i][4] = cutDecimal((float) random(1, 100));
        arr[i][5] = cutDecimal((float) (arr[i][2] + arr[i][3] + arr[i][4]) / 3);
    }
}

void sortBook(int arr[166][6]) {
    int temp[6];
    for (int i = 0; i < 166; i++) {
        for (int j = i + 1; j < 166; j++) {
            if (arr[j][5] > arr[i][5]) {
                for (int k = 0; k < 6; k++) {
                    temp[k] = arr[i][k];
                    arr[i][k] = arr[j][k];
                    arr[j][k] = temp[k];
                }
            }
        }
    }
}

void izpis(int gradebook[166][6], string polnaImena[166]) {
    string tmp;
    cout << "\nID\tNAME\t\t";
    cout << setw(10) << "\tKV\tRV\tVI\tOC\n------------------------------------------------------------\n";
    for (int i = 0; i < 166; i++) {
        tmp = polnaImena[gradebook[i][1]];
        cout << gradebook[i][0] << "\t";//ID
        if (tmp.length() > 15)
            cout << polnaImena[gradebook[i][1]] << "\t";//NAME
        else
            cout << polnaImena[gradebook[i][1]] << "\t\t";//NAME
        cout << gradebook[i][2] << "\t";//KV
        cout << gradebook[i][3] << "\t";//RV
        cout << gradebook[i][4] << "\t";//VI
        if (gradebook[i][3] < 50 && gradebook[i][4] < 50) {
            cout << "RV,VI" << endl;
        } else if (gradebook[i][4] < 50) {
            cout << "VI" << endl;
        } else if (gradebook[i][3] < 50) {
            cout << "RV" << endl;
        } else if (gradebook[i][5] <= 50) {
            cout << "5" << endl;
        } else if (gradebook[i][5] > 50 && gradebook[i][5] <= 60) {
            cout << "6" << endl;
        } else if (gradebook[i][5] > 60 && gradebook[i][5] <= 70) {
            cout << "7" << endl;
        } else if (gradebook[i][5] > 70 && gradebook[i][5] <= 80) {
            cout << "8" << endl;
        } else if (gradebook[i][5] > 80 && gradebook[i][5] <= 90) {
            cout << "9" << endl;
        } else if (gradebook[i][5] > 90) {
            cout << "10" << endl;
        }
    }
}

int main(int argc, char **argv) {
    string imena[30] = {"Hong", "Nigel", "Malik", "Tyrone", "Melba", "Hoyt", "Jacques", "Brad", "Emilia", "Stan",
                        "Darrell", "Sophie", "Kris", "Meghan", "Ricky", "Edwardo", "Berta", "Theo", "Jamey", "Dan",
                        "Mose", "Roderick", "Lauren", "Brooke", "Ebony", "Angeline", "Ramona", "Young", "Polly",
                        "Armand"};
    string priimki[20] = {"Boone", "Rangel", "Bradley", "Daniel", "Maxwell", "Brady", "Hurley", "Romero", "Myers",
                          "Ross", "Wood", "Bruce", "Whitaker", "Ware", "David", "Meyer", "Randall", "Solomon",
                          "Guerrero", "Haney"};
    string polnaImena[166];
    int gradebook[166][6];

    genPolnaImena(polnaImena, imena, priimki);
    napolni(gradebook);

    for (int i = 0; i < 166; i++) {
        cout << i + 1 << " ime: " << polnaImena[165 - i] << endl;
    }

    izpis(gradebook, polnaImena);

    sortBook(gradebook);
    cout << "\nSORTED";

    izpis(gradebook, polnaImena);
    IzpisClosest(gradebook, polnaImena);

    return 0;
}
