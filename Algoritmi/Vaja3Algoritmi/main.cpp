#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
    unsigned int count;
    char character;
    vector<bool> codes;

    Element(unsigned int count, char character) : count(count), character(character) {}
};

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

void fillVec(char tmp, vector<Element> &pairs) {
    for (auto &pair: pairs) {
        if (pair.character == tmp) {
            pair.count++;
            return;
        }
    }
    pairs.emplace_back(1, tmp);
}

unsigned int deli(vector<Element> &pairs, unsigned int dno, unsigned int vrh) {
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

void hitroUredi(vector<Element> &pairs, unsigned int dno, unsigned int vrh) {
    if (dno < vrh) {
        unsigned int j = deli(pairs, dno, vrh);
        if (dno != j)
            hitroUredi(pairs, dno, j - 1);
        if (vrh != j)
            hitroUredi(pairs, j + 1, vrh);
    }
}

void sortPairs(vector<Element> &pairs) {
    hitroUredi(pairs, 0, pairs.size() - 1);
    reverse(pairs.begin(), pairs.end());
}

vector<Element> readFile(const string &path) {
    BinReader br(path);
    vector<Element> pairs;

    while (br.f.peek() != EOF) {
        fillVec(br.readByte(), pairs);
    }

    sortPairs(pairs);

    return pairs;
}

void ShannonFano(vector<Element> &elements, int start, int end) {
    unsigned int sum1 = 0, sum2 = 0;
    int diff1, diff2;
    int k, j;

    //dodeli zadnjim elementom vrednosti
    if ((start + 1) == end || start == end || start > end) {
        if (start == end || start > end) return;
        elements[end].codes.push_back(false);
        elements[start].codes.push_back(true);
        return;
    } else {
        for (int i = start; i < end; i++) sum1 += elements[i].count;
        sum2 += elements[end].count;
        diff1 = sum1 - sum2;
        if (diff1 < 0) diff1 *= -1;
        j = 2;
        while (j != end - start + 1) {
            k = end - j;
            sum1 = sum2 = 0;
            for (int i = start; i <= k; ++i) sum1 += elements[i].count;
            for (int i = end; i > k; --i) sum2 += elements[i].count;
            diff2 = sum1 - sum2;
            if (diff2 < 0) diff2 *= -1;
            if (diff2 >= diff1) break;
            diff1 = diff2;
            j++;
        }
        k++;

        for (int i = start; i <= k; i++)
            elements[i].codes.push_back(true);
        for (int i = k + 1; i <= end; i++)
            elements[i].codes.push_back(false);

        //rekurzivni klic
        ShannonFano(elements, start, k);
        ShannonFano(elements, k + 1, end);
    }
}

void Encryption(const string &path) {
    vector<Element> elements = readFile(path);
    /*
    for (auto &element: elements) {
        cout << element.character;
    }

    cout << endl;
    for (auto &element: elements) {
        cout << element.count;
    }
    */
    //get tabela
    ShannonFano(elements, 0, elements.size() - 1);

    /*
    cout << endl;
    for (auto &element: elements) {
        for (auto &&code: element.codes) {
            cout << code;
        }
        cout << endl;
    }
    */

    BinReader br(path);
    BinWriter bw("encrypted.bin");
    char tmp;
    vector<bool> bits;
    int bitsNum = 0;
    int charNum = 0;

    //table

    bw.writeInt(elements.size());
    for (auto &element: elements) {
        bw.writeByte(element.character);
        bw.writeInt(element.count);
    }


    //data encryption

    while (br.f.peek() != EOF) {
        tmp = br.readByte();
        charNum++;

        //find code of the read char
        for (auto &element: elements) {
            if (element.character == tmp) {
                bits = element.codes;
                break;
            }
        }

        //write bits
        for (auto &&bit: bits) {
            bw.writeBit(bit);
            bitsNum++;
        }
    }

    //if left over bits
    if (bw.getK() != 0) {
        for (int i = bw.getK(); i <= 7; ++i) {
            bw.writeBit(false);
            bitsNum++;
        }
    }

    cout << "Razmerje: " << (float) ((float) (charNum * 8) / (float) bitsNum);
}

void Decryption(const string &path) {
    BinReader br(path);
    BinWriter bw("decrypted.bin");

    vector<Element> elements;
    int count;
    char character;
    vector<bool> bits;

    int charNum = br.readInt();
    for (int i = 0; i < charNum; ++i) {
        character = br.readByte();
        count = br.readInt();
        elements.emplace_back(count, character);
    }

    ShannonFano(elements, 0, elements.size() - 1);
    /*
    for (auto &element: elements) {
        cout << element.character;
    }

    cout << endl;
    for (auto &element: elements) {
        cout << element.count;
    }

    cout << endl;
    for (auto &element: elements) {
        for (auto &&code: element.codes) {
            cout << code;
        }
        cout << endl;
    }
    */
    //br.f.ignore(1);
    //cout<<(char)br.readByte();
    br.readByte();
    //bits.push_back(br.readBit());
    while (br.f.good()) {
        bits.push_back(br.readBit());
        for (auto &element: elements) {
            if (element.codes == bits) {
                bw.writeByte(element.character);
                bits.clear();
            }
        }
    }
}


int main(int argc, const char *argv[]) {

    //ce premalo argumentov
    if (argc < 2) {
        return -1;
    }

    string path = argv[2];
    char option = argv[1][0];

    if (option == 'c') Encryption(path);
    else if (option == 'd') Decryption(path);

    /*
    Encryption("alice.txt");
    Decryption("encrypted.bin");
    */

    return 0;
}