#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <stack>
#include <list>

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

struct Pot {
    unsigned int starting;
    unsigned int ending;
    unsigned int cost;
    vector<bool> mnozica; // size st vozlisc // S

    Pot()= default;

    Pot(unsigned int starting, unsigned int ending, unsigned int cena, unsigned int st) : starting(starting),
                                                                                          ending(ending),
                                                                                          cost(cena) {
        for (int i = 0; i < st; ++i) {
            mnozica.push_back(false);
        }
    }

    void print() const {
        cout << endl << starting + 1 << " -" << cost << "-> " << ending + 1 << "  ";
        for (bool i: mnozica) cout << i;
        cout << endl;
    }
};

class Graph {
private:
    vector<vector<unsigned int>> matrix;
    vector<Vozlisce *> seznamVozlisc;
    unsigned int verticesCount = 0;
    unsigned int start = 0;
    vector<vector<Pot>> nivoji; // list<Pot> -> nivo je seznam poti
    default_random_engine generator;

public:
    Graph() = default;

    static void printNivo(vector<Pot> nivo) {
        for (auto &i: nivo) {
            i.print();
            cout << endl;
        }
        cout << endl;
    }

    vector<Pot> VSTAVI_PRVA_VOZLIŠČA() {
        vector<Pot> nivo;

        for (int i = 1; i < verticesCount; ++i)
            if (matrix[i][0] != 0)
                nivo.emplace_back(i, 0, matrix[i][0], verticesCount);

        return nivo;
    }

    void NAPRAVI_SEZNAM(unsigned int vozlisce, vector<Pot> &nivo, unsigned int nivoNum) {
        vector<Pot> tmpNivo;

        if (nivoNum == 1) {
            for (unsigned int i = 1; i < verticesCount; ++i) {
                if (i == vozlisce) continue;

                nivo.emplace_back(vozlisce, i, matrix[vozlisce][i] + matrix[i][0], verticesCount);
                nivo.back().mnozica[i] = true;
            }
            return;
        }

        vector<Pot> prev = nivoji[nivoNum - 1];
        vector<Pot> viable;
        vector<bool> mnozicaViable;
        Pot pot;

        for (auto &i: prev)
            if (i.starting == vozlisce)
                viable.push_back(i);

        //doda vozlisce
        for (int i = 1; i < verticesCount; ++i) {
            for (auto & j : viable) {
                mnozicaViable = j.mnozica;
                // ce je isto vozlisce ali ce je ze sla skozi to vozlisce
                if (i == vozlisce || mnozicaViable[i]) continue;

                for (auto & k : viable) {
                    if (k.ending == i && !mnozicaViable[i])
                        pot = k;
                }

                mnozicaViable[i] = true;
                nivo.emplace_back(vozlisce, i, matrix[vozlisce][i] + pot.cost, verticesCount);
                nivo.back().mnozica = mnozicaViable;
            }
        }
    }

    void Potnik(/* Matrix and st_vozlisc*/) {
        nivoji = {};
        vector<Pot> nivo = VSTAVI_PRVA_VOZLIŠČA();
        nivoji.push_back(nivo);

        printNivo(nivo);

        for (int st_nivoja = 1; st_nivoja < verticesCount - 1; ++st_nivoja) {
            nivo = {};
            for (unsigned int vozlisce = 1; vozlisce < verticesCount; ++vozlisce) {
                NAPRAVI_SEZNAM(vozlisce, nivo, st_nivoja);
            }
            nivoji.push_back(nivo);
            printNivo(nivo);
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
            }
        }
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

        cout << "\nTrgovski potnik:\n"
             << "1) Preberi matriko\n"
             << "2) Resi problem trgovskega potnika\n"
             << "3) Izpisi dobljen seznam nivojev\n"
             << "4) Rekonstrukcija poti\n"
             << "5) Izhod\n"
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
                graf.readFromFile("graf1.txt");
                graf.printMatrix();
                break;
            case 2:
                //resi problem
                graf.Potnik();
                break;
            case 3:
                //izpis

                break;
            case 4:
                //rekonstruacija poti

                break;
            case 5:
                cout << "Konec" << endl;
                break;
            default:
                cout << "Napacna izbira!" << endl;
                break;
        }


    } while (choice != 5);

    return 0;
}
