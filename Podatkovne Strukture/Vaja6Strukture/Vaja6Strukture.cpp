#include <iostream>
#include <chrono>
#include <random>

using namespace std;

//dno = start  vrh = end
int deli(vector<int> &arr, int dno, int vrh) {
    int pe = arr[dno];
    int l = dno;
    int d = vrh;
    while (l < d) {
        while (arr[l] <= pe && l < vrh)
            l++;
        while (arr[d] >= pe && d > dno)
            d--;

        if (l < d) {
            swap(arr[l], arr[d]);
        }
    }
    swap(arr[dno], arr[d]);
    return d;
}

void hitroUrediMedian(vector<int> &arr, int dno, int vrh) {
    if (dno >= vrh) return;

    int m = dno + (vrh - dno) / 2;
    swap(arr[dno], arr[m]);

    int j = deli(arr, dno, vrh);
    hitroUrediMedian(arr, dno, j - 1);
    hitroUrediMedian(arr, j + 1, vrh);
}

void hitroUredi(vector<int> &arr, int dno, int vrh) {
    if (dno < vrh) {
        double x[10000];
        x[0] = 0;

        int j = deli(arr, dno, vrh);
        hitroUredi(arr, dno, j - 1);
        hitroUredi(arr, j + 1, vrh);
    }
}

bool preveri(vector<int> arr, int dno, int vrh) {
    for (int i = dno; i < vrh - 1; ++i) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

void urediZIzbiranjem(vector<int> &arr, int velikost) {
    for (int i = 0; i < velikost - 1; ++i) {
        int minIX = i;

        //iskanje min elementa desno od i
        for (int j = i + 1; j < velikost; ++j) {
            if (arr[j] < arr[minIX])
                minIX = j;
        }

        if (minIX != i)
            swap(arr[i], arr[minIX]);
    }
}

int main() {
    int izbira = 0;
    int vrednost = 0;

    vector<int> arr;

    //seed
    std::mt19937 rng;
    std::uniform_int_distribution<uint32_t> uint_dist(0, 1000000);

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    //meni
    do {
        cout << "\nHitro uredi:\n"
             << "1) Generiraj nakljucno zaporedje\n"
             << "2) Generiraj narascajoce zaporedje\n"
             << "3) Generiraj padajoce zaporedje\n"
             << "4) Izpis zaporedja\n"
             << "5) Preveri ali je zaporedje urejeno\n"
             << "6) Uredi s hitrim urejanjem brez mediane\n"
             << "7) Uredi s hitrim urejanjem z mediano\n"
             << "8) Uredi z drugim algoritmom za urejanjem\n"
             << "9) Konec\n"
             << "Izbira:";
        cin >> izbira;

        while (cin.fail()) {
            cout << "Napacna izbira\nIzbira:";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> izbira;
        }

        switch (izbira) {
            case 1:
                arr.clear();

                cout << "Podaj dolzino zaporedja:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nIzbira:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                for (int i = 0; i < vrednost; ++i) {
                    arr.push_back((int) uint_dist(rng));
                }

                break;
            case 2:
                arr.clear();

                cout << "Podaj dolzino zaporedja:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nIzbira:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                for (int i = 0; i < vrednost; ++i) {
                    arr.push_back((int) uint_dist(rng));
                }

                hitroUrediMedian(arr, 0, (int) arr.size() - 1);
                break;
            case 3:
                arr.clear();

                cout << "Podaj dolzino zaporedja:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nIzbira:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                for (int i = 0; i < vrednost; ++i) {
                    arr.push_back((int) uint_dist(rng));
                }

                hitroUrediMedian(arr, 0, (int) arr.size() - 1);

                for (int i = 0; i < arr.size() / 2; ++i) {
                    swap(arr[i], arr[arr.size() - i - 1]);
                }

                break;
            case 4:
                for (int rndNum: arr) {
                    cout << rndNum << " ";
                }
                cout << endl;
                break;
            case 5:
                if (preveri(arr, 0, (int) arr.size()))
                    cout << "urejeno!\n";
                else
                    cout << "ni urejeno!\n";
                break;
            case 6:
                start = std::chrono::steady_clock::now();

                hitroUredi(arr, 0, (int) arr.size() - 1);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                break;
            case 7:
                start = std::chrono::steady_clock::now();

                hitroUrediMedian(arr, 0, (int) arr.size() - 1);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 8:
                start = std::chrono::steady_clock::now();

                urediZIzbiranjem(arr, (int) arr.size());

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 9:
                cout << "Konec" << endl;
                break;
            default:
                cout << "Napacna izbira" << endl;
                break;
        }
    } while (izbira != 9);

    return 0;
}