#include <iostream>
#include <chrono>
#include <random>

using namespace std;

struct element {
    int key;
    element *next, *prev;
};

class twoWayList {
private:
    element *head = nullptr;
    element *tail = nullptr;
public:
    element *getHead() const {
        return head;
    }

    element *getTail() const {
        return tail;
    }

    static int getLen(element *start, element *end) {
        int counter = 1;
        while (start != end && start->next != nullptr) {
            counter++;
            start = start->next;
        }
        return counter;
    }

    void printHeadTail() {
        element *current = head;
        while (current != nullptr) {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
        delete current;
    }

    void insertTail(int key) {
        auto *new_elem = new element();
        new_elem->key = key;

        new_elem->prev = tail;
        new_elem->next = nullptr;

        if (tail != nullptr)
            tail->next = new_elem;
        else
            head = new_elem;
        tail = new_elem;
    }

    void deleteAllNodes() {
        element *temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            free(temp);
        }
        head = nullptr;
        tail = nullptr;
    }

    bool isSorted() const {
        element *current = head;
        while (current->next != nullptr) {
            if (current->key > current->next->key)
                return false;
            current = current->next;
        }
        return true;
    }

    long getSum() const {
        long sum = 0;
        element *current = head;
        while (current != nullptr) {
            sum += current->key;
            current = current->next;
        }
        free(current);
        return sum;
    }

    static bool haveMet(element *start, element *end) {
        element *current = start;

        //ce sta isti element
        if (current == end) return true;
        while (current != nullptr) {
            //ce najde end element za startom
            if (current == end) return false;
            current = current->next;
        }
        //ce ni naslo end elementa
        return true;
    }

    //                             dno            vrh
    static element *split(element *start, element *end) {
        int pe = start->key;
        element *l = start;
        element *d = end;

        bool met = haveMet(l, d);

        while (!met) {
            while (l->key <= pe && l != end) {
                l = l->next;
                met = haveMet(l, d);
            }
            while (d->key >= pe && d != start) {
                d = d->prev;
                met = haveMet(l, d);
            }

            if (!met)
                swap(l->key, d->key);
        }
        swap(start->key, d->key);
        return d;
    }

    static void quickSort(element *start, element *end) {
        if (start == nullptr || end == nullptr) return;
        if (getLen(start, end) > 1) {
            element *j = split(start, end);
            if (start != j)
                quickSort(start, j->prev);
            if (end != j)
                quickSort(j->next, end);
        }
    }
};

int main() {
    int izbira = 0;
    int vrednost = 0;
    twoWayList arr;

    //seed
    std::mt19937 rng;
    std::uniform_int_distribution<uint32_t> uint_dist(0, 1000000);

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    //meni
    do {
        cout << "\nHitro uredi dvojno povezan seznam:\n"
             << "1) Generiraj nakljucno zaporedje\n"
             << "2) Izpis zaporedja\n"
             << "3) Preveri urejenost zaporedja\n"
             << "4) Izpisi vsoto elementov\n"
             << "5) Uredi\n"
             << "6) Konec\n"
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
                arr.deleteAllNodes();

                cout << "Podaj dolzino zaporedja:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nIzbira:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                for (int i = 0; i < vrednost; ++i) {
                    arr.insertTail((int) uint_dist(rng));
                }

                break;
            case 2:
                //izpis
                arr.printHeadTail();
                break;
            case 3:
                //prevri
                if (arr.isSorted())
                    cout << "urejeno!\n";
                else
                    cout << "ni urejeno!\n";
                break;
            case 4:
                //vsota elementov
                cout << "Vsota: " << arr.getSum() << endl;
                break;
            case 5:
                //uredi

                if (arr.isSorted())
                    break;

                start = std::chrono::steady_clock::now();

                twoWayList::quickSort(arr.getHead(), arr.getTail());

                end = std::chrono::steady_clock::now();

                cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 6:
                cout << "Konec" << endl;
                break;
            default:
                cout << "Napacna izbira" << endl;
                break;
        }
    } while (izbira != 6);

    arr.deleteAllNodes();

    return 0;
}