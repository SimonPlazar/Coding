#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

class BinWriter {
public:
    int k;
    ofstream f;
    char x{};

    int getK() const {
        return k;
    }

    explicit BinWriter(const string &file) : k(0) {
        f.open(file, ios::binary);
    }

    ~BinWriter() {
        if (k > 0) writeByte(x);
        f.close();
    }

    void writeByte(char i) {
        f.write((char *) &i, 1);
    }

    void writeInt(int y) {
        f.write((char *) &y, 4);
    }

    void writeBit(bool b) {
        if (k == 8) {
            writeByte(x);
            k = 0;
        }
        x ^= (-b ^ x) & (1 << k);
        k++;
    }

    void writeFloat(float y) {
        f.write((char *) &y, 4);
    }
};

class BinReader {
public:
    int bitCount;
    ifstream f;
    char byte;
    int integer;
    float floating;

    explicit BinReader(const string &file) : bitCount(0) {
        f.open(file, ios::binary);
    }

    char readByte() {
        f.read((char *) &byte, 1);
        return byte;
    }

    bool readBit() {
        if (bitCount == 8) {
            readByte();
            bitCount = 0;
        }
        bool b = (byte >> bitCount) & 1;
        bitCount++;
        return b;
    }

    int readInt() {
        f.read((char *) &integer, 4);
        return integer;
    }

    float readFloat() {
        f.read((char *) &floating, 4);
        return floating;
    }

    ~BinReader() {
        f.close();
    }
};

string readFile(const string &path) {
    BinReader br(path);
    string niz;

    while (br.f.peek() != EOF) {
        niz.push_back(br.readByte());
    }

    return niz;
}

void Encryption(const string &path, int max) {
    std::unordered_map<string, int> slovar(max);
    string T;
    string C;
    string niz = readFile(path);
    int count = 0;
    int indexCount = 0;
    BinWriter bw("encrypted.bin");

    for (int i = 0; i < 256; ++i) {
        string str;
        str = (char) i;
        slovar[str] = i;
    }

    for (int i = 0; i < niz.size() + 1; ++i) {
        C = niz[i];
        if (slovar.find(T + C) != slovar.end()) {
            //je v slovaru
            T += C;
        } else if (slovar.find(T + C) != slovar.end() && i == niz.size()) {
            //nadnji element
            bw.writeInt(slovar.find(T)->second);
            indexCount++;
        } else {
            //ni v slovaru
            bw.writeInt(slovar.find(T)->second);
            indexCount++;
            slovar[T + C] = 256 + count++;
            T = C;
        }
    }

    cout << "Razmerje: " << (float) ((niz.size() - 1) * 8) / (float) ((indexCount) * (4 * 8)) << endl;
}

bool findEntry(const std::unordered_map<int, string> &slovar, const string &entry) {
    for (auto &n: slovar)
        if (n.second == entry) return true;
    return false;
}


void Decryption(const string &path, int max) {
    std::unordered_map<int, string> slovar(max);
    BinReader br(path);
    BinWriter bw("decrypted.bin");
    string P, T;
    int count = 0;

    for (int i = 0; i < 256; ++i) {
        string str;
        str = (char) i;
        slovar[i] = str;
    }

    while (br.f.peek() != EOF) {
        int index = br.readInt();

        if (slovar.find(index) != slovar.end()) {
            T = slovar.find(index)->second;
        } else {
            T = P + P[0];
            slovar[256 + count++] = T;
        }
        for (char i: T) {
            bw.writeByte(i);
        }
        if (!T.empty()) {
            if (!findEntry(slovar, P + T[0])) {
                slovar[256 + count++] = P + T[0];
            }
        }
        P = T;
    }
}

int main(int argc, const char *argv[]) {

    //ce premalo argumentov
    if (argc < 3) {
        return -1;
    }

    string path = argv[3];
    int max = stoi(argv[2]);
    char option = argv[1][0];

    if (option == 'c') Encryption(path, max);
    else if (option == 'd') Decryption(path, max);
    else return -2;
    /*
    int max = 300;

    Encryption("lena512.bmp", max);
    Decryption("encrypted.bin", max);
    */
    return 0;
}