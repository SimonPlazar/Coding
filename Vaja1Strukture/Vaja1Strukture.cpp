#include <iostream>

using namespace std;

struct sklad {
    int *arr;
    int vrh = -1;
    int MAX;

    void push(int x) {
        vrh++;
        arr[vrh] = x;
    }

    int pop() {
        vrh--;
        return arr[vrh + 1];
    }

    void izpis() {
        for (int i = 0; i <= vrh; i++) {
            if (i == 0) cout << arr[i];
            else cout << " " << arr[i];
        }
        cout << endl;
    }
};

struct vrsta {
    int glava = 0;
    int rep = 0;
    int MAX;
    int *arr;

    bool push(int x) {
        int newRep = rep + 1;
        if (newRep == MAX) newRep = 0;
        if (glava == newRep) return false;
        arr[rep] = x;
        rep = newRep;
        return true;
    }

    int pop() {
        int x = glava;
        glava++;
        if (glava == MAX) glava = 0;
        return arr[x];
    }

    void izpis() {
        int tmpG = glava;
        int x;
        while (tmpG != rep) {
            x = tmpG;
            tmpG++;
            if (tmpG == MAX) tmpG = 0;
            cout << arr[x] << " ";
        }
        cout << endl;
    }
};

int main() {
    int maxSklad;
    int maxVrsta;
    int izbira = 0;
    int vrednost = 0;

    cout << "Podaj velikost polja sklad:";
    cin >> maxSklad;

    while(cin.fail()){
        cout<<"Napacna izbira\nPodaj velikost polja sklad:";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> maxSklad;
    }

    cout << "Podaj velikost polja vrsta:";
    cin >> maxVrsta;

    while(cin.fail()){
        cout<<"Napacna izbira\nPodaj velikost polja vrsta:";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> maxVrsta;
    }

    //sklad
    sklad s;
    s.MAX = maxSklad;
    s.arr = new int[s.MAX];

    //vrsta
    vrsta v;
    v.MAX = maxVrsta;
    v.arr = new int[v.MAX];

    //meni
    do {
        cout << "\n"
             << "Sklad izbira:\n"
             << "1. Vnos podatka\n"
             << "2. Branje podatka in izpis\n"
             << "3. Izpis vsebine sklada\n"
             << "\n"
             << "Krozna vrsta izbira:\n"
             << "4. Vnos podatka\n"
             << "5. Branje podatka in izpis\n"
             << "6. Izpis vrste od glave do repa\n"
             << "\n"
             << "7. Konec\n"
             << "\n"
             << "Izbira:";
        cin >> izbira;
        cout << endl;

        while(cin.fail()){
            cout<<"Napacna izbira\nIzbira:";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> izbira;
        }

        switch (izbira) {
            case 1:
                if (s.vrh == s.MAX - 1) cout << "Napaka: Polno" << endl;
                else {
                    cout << "Podaj vrednost za vnos v polje:";
                    cin >> vrednost;

                    while(cin.fail()){
                        cout<<"Napacna izbira\nPodaj vrednost za vnos v polje:";
                        cin.clear();
                        cin.ignore(256,'\n');
                        cin >> vrednost;
                    }

                    s.push(vrednost);
                }
                break;
            case 2:
                if (s.vrh == -1) cout << "Napaka: Prazno" << endl;
                else cout << "Podatek: " << s.pop() << endl;
                break;
            case 3:
                if (s.vrh == -1) cout << "Napaka: Prazno" << endl;
                else s.izpis();
                break;
            case 4:
                cout << "Podaj vrednost za vnos v polje:";
                cin >> vrednost;

                while(cin.fail()){
                    cout<<"Napacna izbira\nPodaj vrednost za vnos v polje:";
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> vrednost;
                }

                if (v.push(vrednost));
                else cout << "Polno" << endl;
                break;
            case 5:
                if (v.glava == v.rep) cout << "Napaka: Prazno" << endl;
                else cout << "Podatek: " << v.pop() << endl;
                break;
            case 6:
                if (v.glava == v.rep) cout << "Napaka: Prazno" << endl;
                else v.izpis();
                break;
            case 7:
                break;
            default:
                cout << "Napacna izbira" << endl;
                break;
        }
    } while (izbira != 7);


    return 0;
}
