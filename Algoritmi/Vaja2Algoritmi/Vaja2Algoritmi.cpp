#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ofstream out;

string inputText(const string &pot) {
    ifstream input(pot);
    stringstream sstream;

    if (!input.is_open()) {
        return {};
    }

    sstream << input.rdbuf();
    return sstream.str();
}

void izpis_KMP(const vector<int>& arr) {
    for (int i : arr) {
        out << i << ' ';
    }
    out << endl;
}

void KMP(const string &text, const string &vzorec) {
    int size = (int)vzorec.length();
    int length = (int)text.length();
    bool same;

    vector<int> indexi;
    vector<int> kmpNext(size,0);
    kmpNext[0] = -1;
    kmpNext[1] = 0;

    for (int i = 2; i < size; ++i) {
        same = false;
        for (int k = 0; k < i - 1 && !same; ++k) {
            if (vzorec.substr(0,i - 1 - k) == vzorec.substr(k + 1,i - 1 - k)){
                same = true;
                kmpNext[i] = i - 1 - k;
            }
        }
    }

    izpis_KMP(kmpNext);

    int k = 0;
    for (int j = 0; j < length; j++) {
        while(vzorec[k] != '\0'){
            if (vzorec[k] != text[j + k]) {
                j += k - kmpNext[k];
                k = 0;
                break;
            }
            k++;
        }
        //popolni ujem
        if (vzorec == text.substr(j, size)) {
            indexi.push_back(j);
            j += size;
        }
    }

    izpis_KMP(indexi);
}

int main(int argc, const char *const argv[]) {

    if (argc != 3) {
        return -1;
    }

    string text = inputText(argv[2]);
    string vzorec = argv[1];

    out.open("out.txt");

    if (!out) {
        return -2;
    }

    KMP(text, vzorec);
    return 0;
}