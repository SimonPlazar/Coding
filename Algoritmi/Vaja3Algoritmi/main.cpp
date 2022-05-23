#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct pairCharCount{
    unsigned int count;
    char character;

    pairCharCount(unsigned int count, char character) : count(count), character(character){}
};

struct pairCharCode{
    char character;
    vector<bool> codes;

    pairCharCode(char character, vector<bool> code) : character(character), codes(std::move(code)){}
    void print() const{
        cout<<character<<"->";
        for (bool code : codes) {
            cout << code;
        }
        cout<<endl;
    }
};

struct Node{
    Node* prev;
    Node* left;
    Node* right;
    vector<pairCharCount> pairs2;
    unsigned int sum = 0;
    vector<bool> code={};
};

class Tree{
public:
    Tree(const vector<pairCharCount>& pairs, vector<pairCharCode> &tabela){
        root = new Node();

        for (auto pair : pairs) {
            root->pairs2.push_back(pair);
        }

        Node* current = root;

        while (current != nullptr){
            if (current->pairs2.size() > 1 && current->left == nullptr){
                unsigned int sum = 0;

                for (auto & pair : pairs) {
                    sum += pair.count;
                }
                current->sum = sum;

                unsigned int left = current->pairs2[0].count;
                unsigned int right = sum - current->pairs2[0].count;
                int diff1 = left - right;
                if(diff1 < 0) diff1 = diff1 * (-1);

                for (int i = 0; i < current->pairs2.size(); ++i) {
                    left += current->pairs2[i+1].count;
                    right -= current->pairs2[i+1].count;
                    int diff2 = left - right;
                    if(diff2 < 0) diff2 = diff2 * (-1);

                    if (diff1 > diff2){
                        swap(diff1, diff2);
                    }else{
                        Node* newLeft = new Node();
                        Node* newRight = new Node();

                        newLeft->prev = current;
                        newLeft->sum = left - current->pairs2[i+1].count;

                        newRight->prev = current;
                        newRight->sum = right + current->pairs2[i+1].count;

                        newLeft->code = current->code;
                        newLeft->code.push_back(false);

                        newRight->code = current->code;
                        newRight->code.push_back(true);

                        current->left = newLeft;
                        current->right = newRight;

                        for (int j = 0; j <= i; ++j) {
                            newLeft->pairs2.push_back(current->pairs2[j]);
                        }

                        for (int j = i+1; j < current->pairs2.size(); ++j) {
                            newRight->pairs2.push_back(current->pairs2[j]);
                        }

                        current = current->left;
                        break;
                    }
                }
            }else{
                if (current->pairs2.size() == 1){
                    tabela.emplace_back(current->pairs2[0].character, current->code);
                }

                if (current->prev != nullptr && current->prev->right != current){
                    current = current->prev->right;
                    continue;
                }else if(current->prev != nullptr && current->prev->right == current){
                    current = current->prev->prev->right;
                    continue;
                }else{
                    break;
                }

            }
        }
    }

    Node* root;
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

void fillVec(char tmp, vector<pairCharCount> &pairs) {
    for (auto & pair : pairs) {
        if (pair.character == tmp) {
            pair.count++;
            return;
        }
    }
    pairs.emplace_back(1,tmp);
}

unsigned int deli(vector<pairCharCount> &pairs, unsigned int dno, unsigned int vrh) {
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

void hitroUredi(vector<pairCharCount> &pairs, unsigned int dno, unsigned int vrh) {
    if (dno < vrh) {
        unsigned int j = deli(pairs, dno, vrh);
        if(dno != j)
            hitroUredi(pairs, dno, j - 1);
        if(vrh != j)
            hitroUredi(pairs, j + 1, vrh);
    }
}

void sortPairs(vector<pairCharCount> &pairs) {
    hitroUredi(pairs, 0, pairs.size()-1);
    reverse(pairs.begin(), pairs.end());
}

vector<pairCharCount> readFile(const string& path) {
    BinReader br(path);
    vector<pairCharCount> pairs;

    while (br.f.peek() != EOF) {
        fillVec(br.readByte(), pairs);
    }

    sortPairs(pairs);

    return pairs;
}

void ShannonFanoEncryption(const string& path){
    vector<pairCharCount> pairs = readFile(path);

    for (auto & pair : pairs) {
        cout <<pair.character;
    }

    cout << endl;
    for (auto & pair : pairs) {
        cout <<pair.count;
    }

    vector<pairCharCode> codes;

    Tree drevo(pairs, codes);

    drevo.root;

    for (auto & code : codes) {
        code.print();
    }
}



int main(int argc, const char* argv[]) {

    /*
    //ce premalo argumentov
    if (argc < 2) {
        return -1;
    }

    string path = argv[2];
    char option = argv[1][0];

    if (option == 'c') ShannonFanoEncryption(path);
    //else if (option == 'd') ShannonFanoDecompression(path);
    */

    ShannonFanoEncryption("test.bin");

    return 0;
}