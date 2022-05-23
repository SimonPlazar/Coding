//
// Created by simon on 16/05/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Vozlisce {
    vector<int> V;
    vector<int> znak;
    //char vrednost;
    vector<int> vrednost2;
    Vozlisce* oce = nullptr;
    Vozlisce* leviSin = nullptr;
    Vozlisce* desniSin = nullptr;
    int sum;
};

class BinReader {
public:
    int bitCount;
    ifstream f;
    char byte;
    int y;
    float z = 0.0f;

    BinReader(const string path) : bitCount(0) {
        f.open(path, ios::binary);
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

    char readByte() {
        f.read((char*)&byte, 1);
        return byte;
    }

    int readInt() {
        f.read((char*)&y, 4);
        return y;
    }

    float readFloat() {
        f.read((char*)&z, sizeof(z));
        return z;
    }
};

class BinWriter {
public:
    int k;
    ofstream f;
    char x;

    BinWriter(const string path) : k(0) {
        f.open(path, ios::binary);
    }

    ~BinWriter() {
        if (k > 0) writeByte(x);
        f.close();
    }

    void writeBit(bool b) {
        if (k == 8) {
            writeByte(x);
            k = 0;
        }
        x ^= (-b ^ x) & (1 << k);
        k++;
    }

    void writeByte(char x) {
        f.write((char*)&x, 1);
    }

    void writeInt(int y) {
        f.write((char*)&y, 4);
    }

    void writeFloat(float z) {
        f.write((char*)&z, 4);
    }
};

Vozlisce* verjetnostnaTabela(vector<vector<int>>& A, vector<vector<int>>& tabela) {
    for (int i = 0; i < A[1].size() - 1; i++)
    {
        for (int j = 0; j < A[1].size() - i - 1; j++) {
            if (A[1][j] < A[1][j + 1]) {
                swap(A[0][j], A[0][j + 1]);
                swap(A[1][j], A[1][j + 1]);
            }
        }
    }

    Vozlisce* koren = new Vozlisce();

    for (int i = 0; i < 256; i++) {
        if (A[1][i] > 0) {
            koren->V.push_back(A[1][i]);
            koren->znak.push_back(A[0][i]);
        }
    }
    //-----------------------------------------------------------------

    //2.korak, 3.korak in 4.korak
    Vozlisce* cur = koren;
    //int bitCount = 0;
    while (cur != nullptr) {
        if (cur->V.size() > 1 && cur->leviSin == nullptr) {
            int sum = 0;
            int i = 0;
            for (int s : cur->V) sum += s;
            cur->sum = sum;

            int l = cur->V[0];
            int d = sum - cur->V[0];
            int diff1 = l - d;
            if (diff1 < 0) diff1 *= -1;

            for (; i < cur->V.size(); i++)
            {
                l += cur->V[i + 1];
                d -= cur->V[i + 1];
                int diff2 = l - d;
                if (diff2 < 0) diff2 *= -1;

                if (diff1 > diff2) swap(diff1, diff2);
                else {
                    Vozlisce* tmpL = new Vozlisce();
                    Vozlisce* tmpD = new Vozlisce();
                    tmpL->oce = cur;
                    tmpL->sum = l - cur->V[i + 1];

                    tmpL->vrednost2 = cur->vrednost2;
                    tmpL->vrednost2.push_back(0);
                    tmpD->oce = cur;
                    tmpD->sum = d + cur->V[i + 1];

                    tmpD->vrednost2 = cur->vrednost2;
                    tmpD->vrednost2.push_back(1);
                    cur->leviSin = tmpL;
                    cur->desniSin = tmpD;
                    for (int j = 0; j <= i; j++)
                    {
                        tmpL->V.push_back(cur->V[j]);
                        tmpL->znak.push_back(cur->znak[j]);
                    }
                    for (int j = i + 1; j < cur->V.size(); j++)
                    {
                        tmpD->V.push_back(cur->V[j]);
                        tmpD->znak.push_back(cur->znak[j]);
                    }
                    cur = cur->leviSin;
                    //bitCount++;
                    break;
                }
            }
        }
        else {
            if (cur->V.size() == 1) {
                tabela[cur->znak[0]] = cur->vrednost2;
            }

            if (cur->oce != nullptr && cur->oce->desniSin != cur) {
                cur = cur->oce->desniSin;
                continue;
            }
            else if (cur->oce->desniSin == cur && cur->oce->oce != nullptr) {
                cur = cur->oce->oce->desniSin;
                //bitCount--;
            }
            else break;
        }
    }
    return koren;
}

void ShannonFanoKodiranje(std::string path) {
    //1.korak
    vector<vector<int>>A(2);
    BinReader br(path);

    vector<vector<int>> tabela(256);

    for (int i = 0; i < 256; i++)
    {
        A[0].push_back(i);
        A[1].push_back(0);
    }

    int zadnji;
    while (!br.f.eof()) {
        zadnji = br.readByte();
        A[1][zadnji + 128]++;
    }
    A[1][zadnji + 128]--;
    br.f.close();

    /*for (int i = 0; i < 256; i++){
        if (A[1][i] != 0) cout << A[0][i] - 128 << " = " << A[1][i] << endl;
    }*/

    Vozlisce* koren = verjetnostnaTabela(A, tabela);


    BinReader br2(path);
    BinWriter bw("out_c.bin");

    int bit = 0;
    int pos;

    bw.writeInt(koren->znak.size());
    bit += (4 * 8);
    for (int i = 0; i < koren->znak.size(); i++)
    {
        bw.writeByte(A[0][i]);
        bit += 8;
        bw.writeInt(A[1][i]);
        bit += (4 * 8);
    }
    while (!br2.f.eof()) {
        pos = br2.readByte();
        for (int i = 0; i < tabela[pos + 128].size(); i++) {
            bw.writeBit(tabela[pos + 128][i]);
            bit++;
        }
    }
    bw.writeByte(bw.x);
    bit += 8;
    br2.f.close();
    bw.f.close();


    cout << "Kompresijsko razmerje: " << ((float)(koren->sum * 8) / bit) << endl;
}

void ShannonFanoDekompresiranje(std::string path) {
    vector<vector<int>> tabela(256);

    BinReader br2(path);
    BinWriter bw2("out_d.bin");

    bool p;

    int st = br2.readInt();
    vector<vector<int>>tabelaVerjetnosti(2);
    for (int i = 0; i < 256; i++)
    {
        tabelaVerjetnosti[0].push_back(i);
        tabelaVerjetnosti[1].push_back(0);
    }
    for (int i = 0; i < st; i++)
    {
        int B = br2.readByte();
        tabelaVerjetnosti[1][B + 128] = br2.readInt();
    }

    br2.readByte();
    Vozlisce* koren = verjetnostnaTabela(tabelaVerjetnosti, tabela);
    Vozlisce* cur = koren;
    for (int i = 0; i < koren->sum;)
    {
        if (cur->znak.size() > 1) {
            p = br2.readBit();

            if (!p) cur = cur->leviSin;
            else cur = cur->desniSin;
        }
        else {
            //cout << (char)cur->znak[0];
            bw2.writeByte((char)cur->znak[0]);
            cur = koren;
            i++;
        }
    }

    br2.f.close();
    bw2.f.close();
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        return -1;
    }

    string s = argv[2];
    char c = argv[1][0];
    if (c == 'c') ShannonFanoKodiranje(s);
    else if (c == 'd') ShannonFanoDekompresiranje(s);
}

/*int main()
{
	ShannonFanoKodiranje("lena512.bmp");
	ShannonFanoDekompresiranje("out_c.bin");
}*/