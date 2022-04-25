#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

ofstream out;

vector<char> getUniqueChars(const string &basicString);

string inputText(const string &pot) {
    ifstream input(pot);
    stringstream sstream;

    if (!input.is_open()) {
        return {};
    }

    sstream << input.rdbuf();
    return sstream.str();
}

vector<char> getUniqueChars(const string &basicString) {
    vector<char> chars;

    for (char i: basicString)
        if (!any_of(chars.begin(), chars.end(), [&i](char charsChar) { return i == charsChar; }))chars.push_back(i);

    return chars;
}

void Sunday(const string &text, const string &vzorec) {
    int size = (int) vzorec.length();

    vector<char> crke;
    crke = getUniqueChars(vzorec);
    crke.push_back('*');

    int sizeBCH = (int) crke.size();

    vector<int> BCH(crke.size());

    for (int i = 0; i < BCH.size(); ++i) {
        for (int j = 0; j < vzorec.size(); ++j) {
            if (crke[i] == vzorec[j]) {
                BCH[i] = size - j;
            }
        }
    }

    BCH[BCH.size() - 1] = size + 1;

    for (int i = 0; i < crke.size(); ++i) {
        out << crke[i] << " ";
        for (int j = 1; (BCH[i] / pow(10, j)) >= 1; ++j) {
            out << " ";
        }
    }

    out << endl;

    for (int i: BCH) {
        out << i << " ";
    }

    out << endl << endl;

    vector<int> indexi;

    for (int j = 0; j < text.size(); ++j) {
        for (int i = (int) size - 1; i >= 0; --i) {
            if (vzorec[i] != text[j + i]) {
                for (int k = 0; k < sizeBCH; ++k) {
                    if (crke[k] == text[j + size]) {
                        //-1 zato ker se v naslednmji iteraciji loopa poveca j za 1.
                        j += BCH[k] - 1;
                        k = sizeBCH;
                    }
                }
                //konca loop
                i = 0;
                //ni naslo neujema do zadnejga znaka -> nasli ujem
            } else if (i == 0) {
                indexi.push_back(j);
                //ce najde match preskoci za celoten vzorec
                j += size - 1;
                i = 0;
            }
        }
    }

    for (int i: indexi) {
        out << i << " ";
    }
}

int main(int argc, const char *const argv[]) {

    if (argc != 3) {
        return -1;
    }

    string vzorec = argv[1];
    string text = inputText(argv[2]);

    out.open("out.txt");

    if (!out) {
        return -2;
    }

    Sunday(text, vzorec);
    return 0;
}