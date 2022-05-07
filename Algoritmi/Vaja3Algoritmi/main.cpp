// PRIMER za BinReader in BinWriter
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct pair1{
    unsigned int count;
    char character;

    pair1(unsigned int count, char character) : count(count), character(character){}
};

class BinWriter {
public:
    int k;
    ofstream f;
    char x{};

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
    int k;
    ifstream f;
    char x{};

    explicit BinReader(const string &file) : k(0) {
        f.open(file, ios::binary);
    }

    char readByte() {
        f.read((char *) &x, 1);
        return x;
    }

    bool readBit() {
        if (k == 8) {
            readByte();
            k = 0;
        }
        bool b = (x >> k) & 1;
        k++;
        return b;
    }

    int readInt() {
        f.read((char *) &x, 4);
        return x;
    }

    float readFloat() {
        f.read((char *) &x, 4);
        return x;
    }

    char readChar() {
        f.read((char *) &x, 1);
        return x;
    }

    ~BinReader() {
        f.close();
    }
};

void fillVec(char tmp, vector<pair1> &pairs) {
    for (auto & pair : pairs) {
        if (pair.character == tmp) {
            pair.count++;
            return;
        }
    }
    pairs.push_back(pair1(1,tmp));
}

unsigned int deli(vector<pair1> &pairs, unsigned int dno, unsigned int vrh) {
    unsigned int pe = pairs[dno].count;
    unsigned int l = dno;
    unsigned int d = vrh;
    while (l < d) {
        while (pairs[l].count <= pe && l < vrh)
            l++;
        while (pairs[d].count >= pe && d > dno)
            d--;

        if (l < d) {
            swap(pairs[l], pairs[d]);
        }
    }
    swap(pairs[dno], pairs[d]);
    return d;
}

void hitroUredi(vector<pair1> &pairs, unsigned int dno, unsigned int vrh) {
    if (dno < vrh) {
        unsigned int j = deli(pairs, dno, vrh);
        if(dno != j)
            hitroUredi(pairs, dno, j - 1);
        if(vrh != j)
            hitroUredi(pairs, j + 1, vrh);
    }
}

void fixVec(vector<pair1> &pairs) {
    hitroUredi(pairs, 0, pairs.size()-1);
    reverse(pairs.begin(), pairs.end());
}

vector<pair1> readFile() {
    BinReader br("test.bin");
    vector<pair1> pairs;

    while (br.f.peek() != EOF) {
        fillVec(br.readByte(), pairs);
    }

    fixVec(pairs);

    return pairs;
}

int main() {

    /*
    BinWriter bw("test.bin");
    bw.writeBit(1);
    bw.writeBit(0);
    bw.writeBit(0);
    bw.writeBit(0);
    bw.writeBit(0);
    bw.writeBit(0);
    bw.writeBit(1);
    bw.writeBit(0);
    bw.writeByte(bw.x);
    bw.f.close();
    */

    vector<pair1> pairs = readFile();

    for (auto & pair : pairs) {
        cout <<pair.character;
    }

    cout << endl;
    for (auto & pair : pairs) {
        cout <<pair.count;
    }

    //br.readByte();
    //for (int i = 0; i < 8; ++i)
    //cout << (int)br.readBit() << "\n";
    //cout <<endl;

    return 0;
}