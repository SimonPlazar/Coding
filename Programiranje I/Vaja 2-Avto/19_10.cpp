#include <iostream>

using namespace std;

int main(int argc, char **argv) {

    double hitrost, trajanje, dolzina, mankajoce;

    cout << "Vnesi hitrost(km/h)! ";
    cin >> hitrost;

    cout << "Vnesi trajanje(h)! ";
    cin >> trajanje;

    cout << "Vnesi dolzina(km)! ";
    cin >> dolzina;

    cout << hitrost << " " << trajanje << " " << dolzina << endl;
    mankajoce = dolzina - trajanje * hitrost;
    if (mankajoce > 0) {
        cout << "Dolzina do cilja: " << dolzina - trajanje * hitrost << " km";
    }
    if (mankajoce < 0) {
        cout << "Kolesar je ze prevozil cilj";
    }
    if (mankajoce == 0) {
        cout << "Kolesar je na cilju";
    }

    return 0;
}
