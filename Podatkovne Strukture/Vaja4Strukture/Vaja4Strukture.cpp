#include <iostream>

using namespace std;

struct node {
    int key;
    node *oce;
    node *leviSin;
    node *desniSin;
};

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

    void vstavi(int k) {
        node *y = nullptr;
        node *x = Koren;

        while (x != nullptr) {
            y = x;
            if (k < x->key)
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
            cout << x->key << " ";
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
        delete y;
    }

    void brisi(node *z) {
        if (z == nullptr) return;
        if (z->leviSin == nullptr || z->desniSin == nullptr)
            brisiScenarij1_2(z);
        else {
            node *y = naslednjik(z);
            int vrednost = y->key;
            brisiScenarij1_2(y);
            z->key = vrednost;
        }
    }
};

int main() {
    binaryTree tree;
    binaryTree testiranje;
    int izbira = 0;
    int vrednost = 0;
    node *tmp;

    //meni
    do {
        cout << "Binarno iskalno drevo\n"
             << "\n"
             << "1) Vnos podatka\n"
             << "2) Urejen izpis vrednosti\n"
             << "3) Izpis povezav\n"
             << "4) Iskanje\n"
             << "5) Izpisi minimum in maksimum\n"
             << "6) Izpisi predhodnika in naslednika\n"
             << "7) Brisi vrednost\n"
             << "8) Testiraj pravilnost delovanja\n"
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
                cout << "Vnesi key:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tree.vstavi(vrednost);

                break;
            case 2:
                tree.urejeniIzpis(tree.getKoren());
                cout << endl;
                break;
            case 3:
                tree.izpisPovezav(tree.getKoren());

                break;
            case 4:
                cout << "Vnesi key:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tmp = binaryTree::poisci(tree.getKoren(), vrednost);

                if(tmp != nullptr) cout << "Obstaja" << endl;
                else cout << "Ne obstaja" << endl;

                break;
            case 5:
                tmp = binaryTree::maximum(tree.getKoren());
                if (tmp != nullptr) cout << tmp->key << " ";

                tmp = binaryTree::minimum(tree.getKoren());
                if (tmp != nullptr) cout << tmp->key << endl;

                break;
            case 6:
                cout << "Vnesi key:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tmp = binaryTree::predhodnik(binaryTree::poisci(tree.getKoren(), vrednost));
                if (tmp != nullptr) cout << tmp->key << " ";

                tmp = binaryTree::naslednjik(binaryTree::poisci(tree.getKoren(), vrednost));
                if (tmp != nullptr) cout << tmp->key << endl;

                break;
            case 7:
                cout << "Vnesi key:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                tree.brisi(binaryTree::poisci(tree.getKoren(), vrednost));

                break;
            case 8:
                cout << "Preveri izjeme:\n";

                testiranje.vstavi(5);
                testiranje.vstavi(3);
                testiranje.vstavi(2);
                testiranje.vstavi(4);
                testiranje.vstavi(7);
                testiranje.vstavi(6);
                testiranje.vstavi(8);

                cout<<" Vstavljeno!"<<endl;

                testiranje.brisi(binaryTree::poisci(tree.getKoren(), 9));

                cout<<" Brinsanje 9!"<<endl;

                testiranje.brisi(tree.getKoren());

                cout<<" Brisanje korena!"<<endl;

                tmp = binaryTree::naslednjik(binaryTree::poisci(testiranje.getKoren() ,8));
                if(tmp != nullptr) cout<< tmp->key;
                cout<<" naslednjik zadnjega elementa" <<endl;

                tmp = binaryTree::predhodnik(binaryTree::poisci(testiranje.getKoren() ,5));
                if(tmp != nullptr) cout<< tmp->key;
                cout<<" predhodnik prvega elementa" <<endl;

                tmp = binaryTree::poisci(testiranje.getKoren() ,9);
                if(tmp == nullptr) cout<<"iskanje 9 ki ne obstaja"<<endl;

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