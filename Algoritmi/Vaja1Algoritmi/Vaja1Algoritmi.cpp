#include <fstream>
#include <vector>

using namespace std;

int findMin(const vector<int> &vec) {
    int min = 0;
    for (int i: vec) {
        if (i < min) {
            min = i;
        }
    }
    return min;
}

int findMax(const vector<int> &vec) {
    int max = 0;
    for (int i: vec) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

bool Branje_Stevil(vector<int> &vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(int *polje, unsigned int velikost) {
    ofstream output("out.txt");

    for (int i = 0; i < velikost; i++)
        output << polje[i] << ' ';
}

vector<int> countingSort(vector<int> vecA) {
    int min = findMin(vecA);

    //postavimo v interval [0,max-min]
    for (int &i: vecA) {
        i -= min;
    }

    //nov vektor c velikosti max+1
    int max = findMax(vecA);
    vector<int> vecC(max + 1);
    fill(vecC.begin(), vecC.end(), 0);

    //inkrementiramo index vrednosti vecA[i] v polju c

    for (int i: vecA) {
        vecC[i]++;
    }

    //sestejemo trenutno in prejsno vrednost v vektorju c
    for (auto i = 1; i != vecC.size(); i++) {
        vecC[i] += vecC[i - 1];
    }

    //izhodni vektor b
    vector<int> vecB(vecA.size());

    for (int i = vecA.size() - 1; i >= 0; i--) {
        vecB[vecC[vecA[i]] - 1] = vecA[i];
        vecC[vecA[i]]--;
    }

    //postavimo v prvoten interval
    for (int &i: vecB) {
        i += min;
    }

    return vecB;
}

vector<int> romanSort(vector<int> vecA) {
    int min = findMin(vecA);

    //postavimo v interval [0,max-min]
    for (int &i: vecA) {
        i -= min;
    }

    //nov vektor c velikosti max+1
    int max = findMax(vecA);
    vector<int> vecC(max + 1);
    fill(vecC.begin(), vecC.end(), 0);

    //inkrementiramo index vrednosti vecA[i] v polju c
    for (int i: vecA) {
        vecC[i]++;
    }

    //izhodni vektor b
    auto size = vecA.size();
    vector<int> vecB(size);

    //zapisovanje ix v B
    int counter = 0;
    for (auto i = 0; i != vecC.size(); i++) {
        if (vecC[i] != 0) {
            for (int j = 0; j < vecC[i]; j++) {
                vecB[counter] = i;
                counter++;
            }
        }
    }

    //postavimo v prvoten interval
    for (int &i: vecB) {
        i += min;
    }

    return vecB;
}

int main(int argc, const char *argv[]) {
    vector<int> A;

    if (argc < 3) return 0;
    if (!Branje_Stevil(A, argv[2])) return 0;

    if (argv[1][0] == '0') {
        //counting sort
        A = countingSort(A);
    } else {
        //Roman sort
        A = romanSort(A);
    }

    Izpis_Stevil(&A[0], A.size());

    return 0;
}
