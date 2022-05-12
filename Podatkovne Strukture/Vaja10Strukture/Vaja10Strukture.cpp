#include <iostream>
#include <fstream>
#include <vector>
#include <random>

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

    void print() const{
        cout << endl << u + 1 << " -" << cena << "-> " << v + 1 << endl;
    }
};

bool checkIfUgodnaPovezava(const vector<Povezava *> &vec, Povezava *povezava) {
    for (auto i: vec) {
        //povezaza s samim sabo
        if (povezava->v == povezava->u )
            return false;
            //enaka povezava obstaja
        else if(i->v == povezava->u && i->u == povezava->v)
            return false;
            //obratna povezava obstaja
        else if (i->v == povezava->v && i->u == povezava->u)
            return false;
    }
    return true;
}

class Graph {
private:
    vector<vector<unsigned int>> matrix;
    vector<Povezava *> seznamPovezav;
    vector<Vozlisce *> seznamVozlisc;
    unsigned int verticesCount = 0;
    unsigned int start = 0;
    default_random_engine generator;

public:
    const vector<Vozlisce *> &getSeznamVozlisc() const {
        return seznamVozlisc;
    }

    unsigned int getVerticesCount() const {
        return verticesCount;
    }

    int getVerticesNum() const {
        return (int) seznamVozlisc.size();
    }

    void printMatrix() {
        cout << endl;
        for (auto &row: matrix) {
            for (unsigned int column: row) {
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

    void randomGraf(unsigned int stVozlisc, unsigned int costMin, unsigned int costMax) {
        unsigned int cost, p, q, edgesCount;
        Povezava* tmp;

        uniform_int_distribution<unsigned int> randomVertice(0, stVozlisc-1);
        uniform_int_distribution<unsigned int> randomCost(costMin, costMax);
        uniform_int_distribution<unsigned int> randomEdgesCount(2*stVozlisc, stVozlisc * stVozlisc);

        verticesCount = stVozlisc;

        edgesCount = (unsigned int) randomEdgesCount(generator);


        for (int i = 0; i < edgesCount; ++i) {
            p = (int) randomVertice(generator);
            q = (int) randomVertice(generator);
            cost = (int) randomCost(generator);

            tmp = new Povezava(p, q, cost);

            //ni ugodna povezava
            while (!checkIfUgodnaPovezava(seznamPovezav, tmp)){
                p = (int) randomVertice(generator);
                q = (int) randomVertice(generator);
                cost = (int) randomCost(generator);

                tmp = new Povezava(p, q, cost);
            }

            seznamPovezav.push_back(tmp);
        }

        matrix.clear();

        //za posamezno vrstico
        for (int i = 0; i < verticesCount; ++i) {
            matrix.emplace_back();
            //za posamezno vozljisce v vrstici
            for (int j = 0; j < verticesCount; ++j) {
                matrix[i].push_back(0);
            }
        }

        for (auto & i : seznamPovezav) {
            matrix[i->u][i->v] = i->cena;
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
    int count;

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
                while (cin.fail() || stVozlisc > 1500 || stVozlisc < 1) {
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
                graf.randomGraf(stVozlisc, valA, valB);
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
                cout << "\nCena poti: " << graf.getSeznamVozlisc()[valA - 1]->cena_poti << endl;
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
