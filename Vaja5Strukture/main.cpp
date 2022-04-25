#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <fstream>


using namespace std;

struct node {
    int key{};
    list<string> imena_filmov;
    //vector<string> imena_filmov{};
    node *oce{};
    node *leviSin{};
    node *desniSin{};
};

void removeFromVec(vector<string> &imena, const string &ime) {
    if (imena.empty()) return;
    for (int i = 0; i < imena.size(); ++i) if (imena[i] == ime) imena.erase(imena.begin() + i);
}

class binaryTree {
private:
    node *Koren = nullptr;
public:
    node *getKoren() {
        return this->Koren;
    }

    static node *poisci(node *x, int k) {
        if (x == nullptr || x->key == k)
            return x;
        else {
            if (k < x->key)
                return poisci(x->leviSin, k);
            else
                return poisci(x->desniSin, k);
        }
    }

    void vstavi(int k, const string &ime) {
        node *y = nullptr;
        node *x = Koren;

        while (x != nullptr) {
            y = x;
            if (k == x->key) {
                x->imena_filmov.push_back(ime);
                return;
            } else if (k < x->key)
                x = x->leviSin;
            else if (k > x->key)
                x = x->desniSin;
            else {
                cout << "error" << endl;
                return;
            }
        }

        node *z = new node();
        z->key = k;
        z->imena_filmov.push_back(ime);
        z->oce = y;

        if (y == nullptr)
            Koren = z;
        else {
            if (z->key < y->key)
                y->leviSin = z;
            else
                y->desniSin = z;
        }
    }

    void urejeniIzpis(node *x) {
        if (x != nullptr) {
            urejeniIzpis(x->leviSin);

            cout << x->key << "->";
            for (auto &i: x->imena_filmov) {
                cout << i << " ";
            }
            cout << endl;

            urejeniIzpis(x->desniSin);
        }
    }

    void izpisPovezav(node *x) {
        if (x == nullptr) return;
        if (x->leviSin != nullptr) {
            cout << x->key << "->" << x->leviSin->key << endl;
            izpisPovezav(x->leviSin);
        }
        if (x->desniSin != nullptr) {
            cout << x->key << "->" << x->desniSin->key << endl;
            izpisPovezav(x->desniSin);
        }
    }

    static node *minimum(node *y) {
        if (y == nullptr) return nullptr;
        node *x = y;
        while (x->leviSin != nullptr)
            x = x->leviSin;
        return x;
    }

    static node *maximum(node *y) {
        if (y == nullptr) return nullptr;
        node *x = y;
        while (x->desniSin != nullptr)
            x = x->desniSin;
        return x;
    }

    static node *naslednjik(node *x) {
        if (x == nullptr) return nullptr;
        if (x->desniSin != nullptr)
            return minimum(x->desniSin);

        node *y = x->oce;
        while (y != nullptr && x == y->desniSin) {
            x = y;
            y = y->oce;
        }
        return y;
    }

    static node *predhodnik(node *x) {
        if (x == nullptr) return nullptr;
        if (x->leviSin != nullptr)
            return maximum(x->leviSin);
        node *y = x->oce;

        while (y != nullptr && x == y->leviSin) {
            x = y;
            y = y->oce;
        }
        return y;
    }

    void brisiScenarij1_2(node *y) {
        node *x;
        if (y->leviSin != nullptr)
            x = y->leviSin;
        else
            x = y->desniSin;

        if (x != nullptr)
            x->oce = y->oce;
        if (y->oce == nullptr)
            Koren = x;
        else {
            if (y == y->oce->leviSin)
                y->oce->leviSin = x;
            else
                y->oce->desniSin = x;
        }
        y->imena_filmov.clear();
        delete y;
    }

    void brisi(node *z) {
        if (z == nullptr) return;
        if (z->leviSin == nullptr || z->desniSin == nullptr)
            brisiScenarij1_2(z);
        else {
            node *y = naslednjik(z);
            int vrednost = y->key;
            list<string> imena = y->imena_filmov;
            //vector<string> imena = y->imena_filmov;
            brisiScenarij1_2(y);
            z->key = vrednost;
            z->imena_filmov = imena;
        }
    }

    static void brisiFilm(node *z, const string &ime) {
        if (z == nullptr) return;
        //removeFromVec(z->imena_filmov, ime);
        z->imena_filmov.remove(ime);
    }
};

void branjeInput(const string &file, binaryTree &tree) {
    ifstream in(file);
    int N;
    int datum;
    string ime;

    in >> N;
    for (int i = 0; i < N; i++) {
        in >> datum;
        getline(in, ime, '\n');
        tree.vstavi(datum, ime);
        if (i % 1000 == 0) {
            cout << "*" << flush;
        }
    }
}


int main() {
    binaryTree tree;
    int izbira = 0;
    int vrednost = 0;
    string ime_filma;
    node *tmp;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;


    //meni
    do {
        cout << "Meni:\n"
             << "1) Vnos filma na datum izdaje\n"
             << "2) Urejen izpis vseh filmov\n"
             << "3) Izpis filmov na datum izdaje\n"
             << "4) Izpisi najstarejse in najnovejse filme\n"
             << "5) Poisci sosednja datuma\n"
             << "6) Brisi datum\n"
             << "7) Brisi film na izbran datum\n"
             << "8) Nalaganje filmov iz datoteke\n"
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
                cout << "Vnesi datum (YYYYMMDD):";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi datum (YYYYMMDD):";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                cout << "Vnesi ime filma:";
                cin >> ime_filma;

                tree.vstavi(vrednost, ime_filma);

                break;
            case 2:
                tree.urejeniIzpis(tree.getKoren());
                cout << endl;
                break;
            case 3:
                cout << "Vnesi datum (YYYYMMDD):";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi datum (YYYYMMDD):";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), vrednost);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                if (tmp == nullptr) {
                    cout << "Ne najde";
                    break;
                }

                if (tmp->imena_filmov.empty()) break;
                cout << "Filmi:" << endl;
                for (auto &i: tmp->imena_filmov) {
                    cout << i << endl;
                }
                cout << endl;

                break;
            case 4:
                tmp = binaryTree::maximum(tree.getKoren());
                if (tmp != nullptr) {
                    cout << "Najstarejsi datum: " << tmp->key << endl;
                    if (!tmp->imena_filmov.empty()) {
                        cout << "Filmi:\n";
                        for (auto &i: tmp->imena_filmov) {
                            cout << i << endl;
                        }
                    }
                }

                tmp = binaryTree::minimum(tree.getKoren());
                if (tmp != nullptr) {
                    cout << "Najmlajsi datum: " << tmp->key << endl;
                    if (tmp->imena_filmov.empty()) break;
                    cout << "Filmi:" << endl;
                    for (auto &i: tmp->imena_filmov) {
                        cout << i << endl;
                    }
                }
                cout << endl;

                break;
            case 5:
                cout << "Vnesi datum (YYYYMMDD):";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi datum (YYYYMMDD):";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tmp = binaryTree::predhodnik(binaryTree::poisci(tree.getKoren(), vrednost));
                if (tmp != nullptr) {
                    cout << "Predhodni datum: " << tmp->key << endl;
                    if (!tmp->imena_filmov.empty()) {
                        cout << "Filmi:\n";
                        for (auto &i: tmp->imena_filmov) {
                            cout << i << endl;
                        }
                    }
                }

                tmp = binaryTree::naslednjik(binaryTree::poisci(tree.getKoren(), vrednost));
                if (tmp != nullptr) {
                    cout << "Naslednji datum: " << tmp->key << endl;
                    if (tmp->imena_filmov.empty()) break;
                    cout << "Filmi:\n";
                    for (auto &i: tmp->imena_filmov) {
                        cout << i << endl;
                    }
                }
                cout << endl;

                break;
            case 6:
                cout << "Vnesi datum (YYYYMMDD):";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi datum (YYYYMMDD):";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tree.brisi(binaryTree::poisci(tree.getKoren(), vrednost));

                cout << endl;

                break;
            case 7:
                cout << "Vnesi datum (YYYYMMDD):";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi datum (YYYYMMDD):";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                cout << "Vnesi ime filma:";
                cin >> ime_filma;

                binaryTree::brisiFilm(binaryTree::poisci(tree.getKoren(), vrednost), ime_filma);

                cout << endl;

                break;
            case 8:
                while (tree.getKoren() != nullptr) {
                    tree.brisi(tree.getKoren());
                }

                cout << "Podaj ime datoteke:";
                ime_filma = "";
                cin >> ime_filma;

                //vstavljanje
                start = std::chrono::steady_clock::now();

                branjeInput(ime_filma, tree);

                end = std::chrono::steady_clock::now();

                cout << "\nCas vstavljanja: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
                     << " ns" << endl;

                //datum1
                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), 20141022);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                //datum2
                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), 20090908);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                //datum3
                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), 20090310);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                //datum4
                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), 20161024);

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;

                //datum5
                start = std::chrono::steady_clock::now();

                tmp = binaryTree::poisci(tree.getKoren(), 20050505);

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