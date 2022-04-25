#include <iostream>
#include <list>
#include <chrono>

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
    void deleteElement(int key) {
        element *elem = find(key);
        if (elem == nullptr) {
            cout << "Element ne obstaja" << endl;
            delete elem;
            return;
        } else {
            if (elem->prev == nullptr && elem->next == nullptr) {
                head = nullptr;
                tail = nullptr;
            } else {
                if (elem->prev != nullptr)
                    elem->prev->next = elem->next;
                else {
                    head = elem->next;
                    (head)->prev = nullptr;
                }
                if (elem->next != nullptr) {
                    elem->next->prev = elem->prev;
                } else {
                    tail = elem->prev;
                    (tail)->next = nullptr;
                }
            }
        }
        delete elem;
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

    void printTailHead() {
        element *current = tail;
        while (current != nullptr) {
            cout << current->key << " ";
            current = current->prev;
        }
        cout << endl;
        delete current;
    }

    element *find(int key) {
        element *current = head;
        while (current != nullptr && current->key != key) {
            current = current->next;
        }
        return current;
    }

    void insertHead(int key) {
        auto *new_elem = new element();
        new_elem->key = key;
        new_elem->next = head;
        new_elem->prev = nullptr;
        if (head != nullptr)
            head->prev = new_elem;
        else
            tail = new_elem;
        head = new_elem;
    }

    void insertAfter(element *elem, int key) {
        if (elem == nullptr) {
            cout << "Element ne obstaja" << endl;
            delete elem;
            return;
        }
        auto *next_elem = new element;
        next_elem->key = key;
        next_elem->prev = elem;
        next_elem->next = elem->next;
        elem->next = next_elem;
        if (next_elem->next != nullptr)
            next_elem->next->prev = next_elem;
        else
            tail = next_elem;
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
};

void pushFrontList(long long size) {
    auto *std_list = new list<long long>;

    auto start=chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        std_list->push_front(i+1);

    auto end=chrono::steady_clock::now();

    cout<<"pushFrontList ("<<size<<"): "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete std_list;
}

void pushFrontArr(long long size) {
    auto *arr = new long long[size];

    auto start=chrono::steady_clock::now();

    for (int i = 0; i < size; i++){
        //push back all by 1
        for(int j = i;j>0 && j != size;j--){
            arr[j+1] = arr[j];
        }
        arr[0] = i+1;
    }
    auto end=chrono::steady_clock::now();

    cout<<"pushFrontArr ("<<size<<"): "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete[] arr;
}

void pushBackList(long long size) {
    auto *std_list = new list<long long>;

    auto start=chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        std_list->push_back(i+1);

    auto end=chrono::steady_clock::now();

    cout<<"pushBackList ("<<size<<"): "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete std_list;
}

void pushBackArr(long long size) {
    auto *arr = new long long[size];

    auto start=chrono::steady_clock::now();


    for (int i = 0; i < size; i++)
        arr[i] = i+1;

    auto end=chrono::steady_clock::now();

    cout<<"pushBackArr ("<<size<<"): "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete[] arr;
}

void getAvgList(long long size){
    auto *std_list = new list<long long>;

    for (int i = 0; i < size; i++)
        std_list->push_front(i+1);

    auto start=chrono::steady_clock::now();

    long long sum = 0;
    for(long long & it : *std_list)
        sum += it;

    auto end=chrono::steady_clock::now();

    cout<<"getAvgList ("<<size<<"): sum: "<<sum<<", "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete std_list;
}

void getAvgArr(long long size){
    auto *arr = new long long[size];
    long long sum = 0;

    for (int i = 0; i < size; i++)
        arr[i] = i+1;

    auto start=chrono::steady_clock::now();

    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    auto end=chrono::steady_clock::now();

    cout<<"getAvgArr ("<<size<<"): sum: "<<sum<<", "<<chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" ns"<<endl;
    delete[] arr;
}

int main() {
    int izbira = 0;
    int vrednost = 0;
    int vrednost2 = 0;
    long long size;

    twoWayList my_list;

    //meni
    do {
        cout << "\n"
             << "1) Iskanje podatka\n"
             << "2) Vnos podatka v glavo\n"
             << "3) Vnos podatka za elementom\n"
             << "4) Vnos podatka za repom\n"
             << "5) Brisanje podatka\n"
             << "6) Izpis seznama od glave proti repu\n"
             << "7) Izpis seznama od repa proti glavi\n"
             << "8) Testiraj hitrost\n"
             << "9) Konec\n"
             << "\n"
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

                if (my_list.find(vrednost) == nullptr || my_list.find(vrednost)->key != vrednost)
                    cout << "Key ne obstaja" << endl;
                else
                    cout << "Key obstaja" << endl;
                break;
            case 2:
                cout << "Vnesi key za vnos v glavo:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key za vnos v glavo:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                my_list.insertHead(vrednost);
                break;
            case 3:
                cout << "Vnesi key za vnos:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key za vnos:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                cout << "Vnesi key elementa:";
                cin >> vrednost2;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key elementa:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost2;
                }

                my_list.insertAfter(my_list.find(vrednost2), vrednost);
                break;
            case 4:
                cout << "Vnesi key za vnos v rep:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key za vnos v rep:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                my_list.insertTail(vrednost);
                break;
            case 5:
                cout << "Vnesi key za element:";
                cin >> vrednost;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi key za element:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> vrednost;
                }

                my_list.deleteElement(vrednost);
                break;
            case 6:
                my_list.printHeadTail();
                break;
            case 7:
                my_list.printTailHead();
                break;
            case 8:
                cout << "Vnesi stevilo elementov:";
                cin >> size;

                while (cin.fail()) {
                    cout << "Napacna izbira\nVnesi stevilo elementov:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> size;
                }

                pushFrontList(size);
                pushFrontArr(size);
                pushBackList(size);
                pushBackArr(size);
                getAvgList(size);
                getAvgArr(size);

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