#include <iostream>

using namespace std;

void init_state(int **state, int n);

void skakac(int x, int y, int level, int &calls, int **state, int n);

void print_solution(int **state, int n, int calls);

bool pos_okay(int x, int y, int n);

bool visited(int x, int y, int **state);

int deltax[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int deltay[] = {-2, -1, 1, 2, 2, 1, -1, -2};

int main() {
    int calls = 0;        //st klicov rekurzije
    int x, y, n;        //zacetna pozicija in dimenzije

    cout << "Vnesi dimenzije (n): ";
    cin >> n;

    cout << "Vnesi parametne (x): ";
    cin >> x;

    cout << "Vnesi parametne (y): ";
    cin >> y;

    int **state = new int *[n];    //rezerviramo toliko kazalcev kot je vrstic
    for (int i = 0; i < n; i++) {
        state[i] = new int[n];    //stolpci
    }

    //inicializacija stanja preiskovanja
    init_state(state, n);

    //klic rekurzivne funkcije
    skakac(x, y, 1, calls, state, n);

    return 0;
}

void skakac(int x, int y, int level, int &calls, int **state, const int n) {
    if (level == n * n) {
        print_solution(state, n, calls);
        exit(0);
    }

    state[x][y] = level;    //oznaci novo stanje

    calls++;

    for (int k = 0; k < 8; k++) {
        if (pos_okay(x + deltax[k], y + deltay[k], n) && !visited(x + deltax[k], y + deltay[k], state)) {
            skakac(x + deltax[k], y + deltay[k], level + 1, calls, state, n);
        }
    }
    state[x][y] = 0;
}

bool pos_okay(int x, int y, const int n) {
    if (x < 0 || x >= n || y < 0 || y >= n) {    //ce je na igriscu
        return false;
    }

    return true;
}

bool visited(int x, int y, int **state) {
    return state[x][y] != 0;
}

void print_solution(int **state, const int n, int calls) {
    cout << "\nIzpis:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (state[i][j] < 10) {
                cout << "0";
            }
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nStevilo skokov: " << calls;
}

void init_state(int **state, const int n) {
    for (int i = 0; i < n; i++) {        //vrstice
        for (int j = 0; j < n; j++) {    //stolpce
            state[i][j] = 0;
        }
    }
}
