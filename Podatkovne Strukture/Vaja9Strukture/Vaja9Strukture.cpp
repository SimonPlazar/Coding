#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

struct povezava {
    int p;
    int q;
    int cost;

    povezava(int p, int q, int cost) : p(p), q(q), cost(cost) {}

    void print() const {
        cout << p << " " << q << " " << cost << endl;
    }
};

int deli(vector<povezava *> &arr, int dno, int vrh) {
    int pe = arr[dno]->cost;
    int l = dno;
    int d = vrh;
    while (l < d) {
        while (arr[l]->cost <= pe && l < vrh)
            l++;
        while (arr[d]->cost >= pe && d > dno)
            d--;

        if (l < d) {
            swap(arr[l], arr[d]);
        }
    }
    swap(arr[dno], arr[d]);
    return d;
}

int maximum(vector<int> vec) {
    int max = vec[0];
    for (int i = 1; i < vec.size(); ++i)
        if (vec[i] > max)
            max = vec[i];
    return max;
}

void hitroUredi(vector<povezava *> &arr, int dno, int vrh) {
    if (dno < vrh) {

        int j = deli(arr, dno, vrh);
        hitroUredi(arr, dno, j - 1);
        hitroUredi(arr, j + 1, vrh);
    }
}

bool checkIfUgodnaPovezava(const vector<povezava *> &vec, povezava *povezava) {
    for (auto i: vec) {
        //povezaza s samim sabo
        if (povezava->p == povezava->q)
            return false;
        //enaka povezava obstaja
        else if(i->p == povezava->q && i->q == povezava->p)
            return false;
        //obratna povezava obstaja
        else if (i->p == povezava->p && i->q == povezava->q)
            return false;
    }
    return true;
}

default_random_engine generator;

class Tree {
private:
    vector<povezava *> seznam;
    vector<int> seznamMnozic;
    int verticesCount = 0;
    int edgesCount = 0;
public:
    void clear() {
        for (auto &item: seznam) {
            free(item);
        }
        seznam = {};
        seznamMnozic = {};
        verticesCount = 0;
        edgesCount = 0;
    }

    void printPovezave() const {
        for (auto povez: seznam) {
            povez->print();
        }
    }

    void readFromFile() {
        int point1, point2, cost;
        ifstream f("grafRot.txt");

        f >> verticesCount;
        f >> edgesCount;

        for (int i = 0; i < verticesCount; ++i) {
            seznamMnozic.push_back(0);
        }

        for (int i = 0; i < edgesCount; ++i) {
            f >> point1 >> point2 >> cost;
            seznam.push_back(new povezava(point1, point2, cost));
        }
    }

    void randomPovezave(int n) {
        int cost = 0, p = 0, q = 0;

        uniform_int_distribution<int> randomVertice(1, n);
        uniform_int_distribution<int> randomCost(1, 20);
        uniform_int_distribution<int> randomEdgesCount(1, n * n);

        verticesCount = n;

        do {
            edgesCount = (int) randomEdgesCount(generator);
        } while (verticesCount > edgesCount);

        for (int i = 0; i < verticesCount; ++i) {
            seznamMnozic.push_back(0);
        }

        for (int i = 0; i < edgesCount; ++i) {
            p = (int) randomVertice(generator);
            q = (int) randomVertice(generator);
            cost = (int) randomCost(generator);

            auto tmp = new povezava(p, q, cost);

            //ni ugodna povezava
            if (!checkIfUgodnaPovezava(seznam, tmp)) {
                free(tmp);
                continue;
            }

            seznam.push_back(tmp);
        }
    }

    // 1 2 3 4 5 6 7 8
    // 2 4 2 2 3 2 3 4

    vector<povezava *> kruskal() {
        hitroUredi(seznam, 0, (int) seznam.size() - 1);
        vector<povezava *> output;
        int max = 0;
        int vrMN1 = 0;
        int vrMN2 = 0;

        for (auto &povezav: seznam) {
            vrMN1 = seznamMnozic[povezav->p - 1];
            vrMN2 = seznamMnozic[povezav->q - 1];

            //ce je vozljisce v mnozici potem ima vr >0
            if (((vrMN1 != 0) && (vrMN2 != 0)) && (vrMN1 == vrMN2)) {
                //oba dva sta v mnozici in oba v enaki mnozici
                continue;
            } else if (((vrMN1 != 0) && (vrMN2 != 0)) && (vrMN1 != vrMN2)) {
                //oba sta v mnozici in mnozici nista enaki
                output.push_back(povezav);
                for (int &i: seznamMnozic) {
                    if (i == vrMN2)
                        i = vrMN1;
                }
            } else if (((vrMN1 != 0) && (vrMN2 == 0)) || ((vrMN1 == 0) && (vrMN2 != 0))) {
                //ena je v mnozici druga pa ne
                output.push_back(povezav);
                if (vrMN1 == 0) {
                    //ce prva ni v mnozici
                    seznamMnozic[povezav->p - 1] = vrMN2;
                } else {
                    //ce druga ni v mnozici
                    seznamMnozic[povezav->q - 1] = vrMN1;
                }
            } else if ((vrMN1 == 0) && (vrMN2 == 0)) {
                //noben ni v mnozici
                output.push_back(povezav);
                max = maximum(seznamMnozic);
                seznamMnozic[povezav->p - 1] = max + 1;
                seznamMnozic[povezav->q - 1] = max + 1;
            }

            if (output.size() == verticesCount - 1) {
                return output;
            }
        }
        cout << "ni resitve" << endl;
        return {};
    }
};

int main() {
    int choice = 0;
    int value1 = 0;

    Tree drevo;
    vector<povezava *> tmp;

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    do {
        cout << "\nKruskalov algoritem\n"
                "1) Preberi graf iz datoteke\n"
                "2) Generiraj nakljucni graf\n"
                "3) Pozeni\n"
                "4) Izpis sprejetih povezav\n"
                "5) Konec\n"
                "Izbira:";
        cin >> choice;

        while (cin.fail()) {
            cout << "Napacna izbira\nIzbira:";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                drevo.clear();
                drevo.readFromFile();
                break;
            case 2:
                drevo.clear();
                //rand graf
                cout << "Podaj stevilo vozlisc:";
                cin >> value1;
                while (cin.fail() || value1 > 1500 || value1 < 0) {
                    cout << "Napacna izbira\nPodaj stevilo vozlisc:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> value1;
                }
                drevo.randomPovezave(value1);
                break;
            case 3:
                start = std::chrono::steady_clock::now();
                tmp = drevo.kruskal();
                end = std::chrono::steady_clock::now();

                for (auto povez: tmp) {
                    povez->print();
                }

                cout << "\nCas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 4:
                drevo.printPovezave();
                break;
            case 5:
                cout << "Konec" << endl;
                break;
            default:
                cout << "Napacna value!" << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
