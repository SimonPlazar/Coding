#include <fstream>
#include <vector>
#include <iostream>
#include <array>
#include <string>

using namespace std;

bool Branje_Stevil(vector<unsigned char> &polje, const char s[]) {
    ifstream input(s);

    if (!input.is_open()) {
        return false;
    }

    int st = 0;

    while (!input.eof()) {
        input >> st;

        polje.push_back((int) st);

        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(const vector<unsigned char> &input, const char s[]) {
    ofstream output(s);

    for (unsigned char i: input)
        output << (int) i << " ";
}

unsigned char boolToChar(const array<bool, 8> bits) {
    unsigned char number = 0;

    for (int i = 0; i < 8; i++) if (bits[i]) number |= 1 << (i);

    return number;
}

void boolToChar(const vector<array<bool, 8>> &input, vector<unsigned char> &output) {
    output.clear();
    for (auto i: input) {
        output.push_back(boolToChar(i));
    }
}

array<bool, 8> charToBool(const unsigned char &stevilo) {
    array<bool, 8> bits{};

    //Delitev na bite
    bits = {false};
    for (int j = 0; j < 8; ++j)
        if ((stevilo & (1 << j)) != 0)
            bits[j] = true;

    return bits;
}

void charToBool(const vector<unsigned char> &input, vector<array<bool, 8>> &output) {
    //Delitev na bite
    output.clear();
    for (unsigned char i: input) output.push_back(charToBool(i));
}

void radixSort(vector<unsigned char> &input) {
    //vektor z polji bitov
    vector<array<bool, 8>> Bytes(input.size());
    charToBool(input, Bytes);

    //vrednosti za counting sort
    int velikost = input.size();

    for (int j = 0; j < 8; ++j) {
        //nov vektor c velikosti max+1
        unsigned int Indexs[2] = {0, 0};

        //inkrementiramo index vrednosti vecA[i] v polju c
        for (int i = 0; i < velikost; ++i) Indexs[(int) Bytes[i][j]]++;

        //sestejemo trenutno in prejsno vrednost v vektorju c
        Indexs[1] += Indexs[0];

        //izhodni vektor b
        vector<array<bool, 8>> Sorted(velikost);

        //Postavi vrednost
        for (int i = velikost - 1; i >= 0; i--)
            Sorted[--Indexs[(int) Bytes[i][j]]] = Bytes[i];

        //preslikava nazaj v originalni vektor
        Bytes.operator=(Sorted);
    }

    boolToChar(Bytes, input);
}


int main(int argc, const char *argv[]) {
    vector<unsigned char> Polje;

    if (argc < 2) return 0;

    if (!Branje_Stevil(Polje, argv[1])) return 0;

    //radix sort
    radixSort(Polje);

    Izpis_Stevil(Polje, "out.txt");

    return 0;
}
