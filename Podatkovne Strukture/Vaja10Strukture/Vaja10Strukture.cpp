#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Vozlisce {
    int predhodnik;
    unsigned int cena_poti;

    Vozlisce() : predhodnik(-1), cena_poti(INT32_MAX) {};

    Vozlisce(int predhodnik, unsigned int cena_poti) : predhodnik(predhodnik), cena_poti(cena_poti) {};

    void print() const {
        cout << "\npredhodnik: ";
        if (predhodnik == -1) cout << "NULL";
        else cout << predhodnik + 1;
        cout << "\ncena poti: " << cena_poti << endl;
    }
};

struct Povezava {
    unsigned int u;
    unsigned int v;
    unsigned int cena;

    Povezava(unsigned int u, unsigned int v, unsigned int cena) : u(u), v(v), cena(cena) {}

    void print() {
        cout << endl << u + 1 << " -" << cena << "-> " << v + 1 << endl;
    }
};

class Graph {
private:
    vector<vector<int>> matrix;
    vector<Povezava *> seznamPovezav;
    vector<Vozlisce *> seznamVozlisc;
    int verticesCount = 0;
    unsigned int start = 0;

public:
    const vector<Vozlisce *> &getSeznamVozlisc() const {
        return seznamVozlisc;
    }

    int getVerticesCount() const {
        return verticesCount;
    }

    int getVerticesNum() const {
        return (int) seznamVozlisc.size();
    }

    void printMatrix() {
        cout << endl;
        for (auto &row: matrix) {
            for (int column: row) {
                cout << column << " ";
            }
            cout << endl;
        }
    }

    void readFromFile(const string &fileName) {
        int verticeCost;

        ifstream f(fileName);

        f >> verticesCount;

        matrix.clear();

        //za posamezno vrstico
        for (int i = 0; i < verticesCount; ++i) {
            matrix.emplace_back();
            //za posamezno vozljisce v vrstici
            for (int j = 0; j < verticesCount; ++j) {
                f >> verticeCost;
                matrix[i].push_back(verticeCost);

                if (verticeCost != 0)
                    seznamPovezav.push_back(new Povezava(i, j, verticeCost));
                verticeCost = 0;
            }
        }
    }

    void resetSeznamVozlisc() {
        for (auto &vozlisc: seznamVozlisc) {
            delete vozlisc;
        }
        seznamVozlisc.clear();

        for (int i = 0; i < verticesCount; ++i) {
            seznamVozlisc.push_back(new Vozlisce);
        }
    }

    void bellmanFord(unsigned int vozlisce) {
        start = vozlisce;

        resetSeznamVozlisc();

        seznamVozlisc[vozlisce]->cena_poti = 0;

        for (int i = 0; i < seznamVozlisc.size(); ++i) {
            for (auto &povezava: seznamPovezav) {
                if (seznamVozlisc[povezava->u]->cena_poti + povezava->cena < seznamVozlisc[povezava->v]->cena_poti) {
                    if (i != seznamVozlisc.size() - 1) {
                        seznamVozlisc[povezava->v]->cena_poti = seznamVozlisc[povezava->u]->cena_poti + povezava->cena;
                        seznamVozlisc[povezava->v]->predhodnik = (int) povezava->u;
                    } else {
                        cout << "Napaka!";
                        return;
                    }
                }
            }
        }
    }

    void printSeznamVozlisc() {
        for (int i = 0; i < seznamVozlisc.size(); ++i) {
            cout << endl << "Vozlisce " << i + 1 << ":";
            seznamVozlisc[i]->print();
        }
    }

    void printSeznamPovezav() {
        for (auto &povezava: seznamPovezav) {
            povezava->print();
        }
    }

    void printPath(int point) {
        if (point == start) {
            cout << "\nPot je: " << point + 1 << " ";
        } else {
            if (seznamVozlisc[point]->predhodnik == -1) {
                cout << "Med " << start + 1 << " in " << point + 1 << " ni poti!" << endl;
                return;
            } else {
                printPath(seznamVozlisc[point]->predhodnik);
                cout << point + 1 << " ";
                return;
            }
        }
    }
};


int main() {
    int choice = 0;
    int stVozlisc = 0;
    int valA = 0;
    int valB = 0;
    int count = 0;

    Graph graf;

    do {
        count = 0;

        cout << "\nBellman Fordov algoritem\n"
             << "1) Preberi graf iz datoteke\n"
             << "2) Generiraj nakljucni graf z n vozlisci in cenami od a do b\n"
             << "3) Pozeni algoritem\n"
             << "4) Izpisi seznam vozlisc\n"
             << "5) Izpisi najkrajso pot\n"
             << "6) Izpis povezav in matrice\n"
             << "7) Konec\n"
             << "Izbira:";
        cin >> choice;

        while (cin.fail()) {
            cout << "Napacna izbira\nIzbira:";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                graf.readFromFile("grafBig.txt");
                break;
            case 2:
                //rand graf
                cout << "Podaj stevilo vozlisc:";
                cin >> stVozlisc;
                while (cin.fail()) {
                    count++;
                    if (count >= 3) {
                        goto err;
                    }
                    cout << "Napacna izbira\nPodaj stevilo vozlisc:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> stVozlisc;
                }

                cout << "Podaj spodnjo mejo cen:";
                cin >> valA;
                while (cin.fail()) {
                    count++;
                    if (count >= 3) {
                        goto err;
                    }
                    cout << "Napacna izbira\nPodaj spodnjo mejo cen:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> valA;
                }

                cout << "Podaj spodnjo zgornjo cen:";
                cin >> valB;
                while (cin.fail()) {
                    count++;
                    if (count >= 3) {
                        goto err;
                    }
                    cout << "Napacna izbira\nPodaj spodnjo zgornjo cen:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> valB;
                }

                //random

                break;
            case 3:
                //algoritem
                cout << "Podaj vozlisce:";
                cin >> valA;
                while (cin.fail() || valA > graf.getVerticesCount() || valA < 1) {
                    count++;
                    if (count >= 3) {
                        goto err;
                    }
                    cout << "Napacna izbira\nPodaj vozlisce:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> valA;
                }

                graf.bellmanFord(valA - 1);

                break;
            case 4:
                //print seznam vozljisc
                graf.printSeznamVozlisc();
                break;
            case 5:
                //print najkrajso pot
                cout << "Podaj vozlisce:";
                cin >> valA;
                while (cin.fail() || valA > graf.getVerticesNum() || valA < 1) {
                    count++;
                    if (count >= 3) {
                        goto err;
                    }
                    cout << "Napacna izbira\nPodaj vozlisce:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> valA;
                }

                graf.printPath(valA - 1);
                cout << "\nCena poti: " << graf.getSeznamVozlisc()[valA-1]->cena_poti<<endl;
                break;
            case 6:
                graf.printSeznamPovezav();
                graf.printMatrix();
                break;
            case 7:
                cout << "Konec" << endl;
                break;
            default:
            err:
                cout << "Napacna izbira!" << endl;
                break;
        }


    } while (choice != 7);

    return 0;
}
