#include <iostream>
#include "SparseMatrix2D.h"
#include "Graph.h"

using namespace std;

int main() {
    Graph relation1(1, 2, "A");
    Element e(5, 6, relation1);
    cout << e.getValue().toString() << endl;

    SparseMatrix2D bigGraphMatrix(10, 10, relation1);

    bigGraphMatrix.set(1, 2, Graph(1, 2, "A"));
    bigGraphMatrix.set(2, 3, Graph(2, 3, "B"));
    bigGraphMatrix.set(3, 4, Graph(3, 4, "C"));
    bigGraphMatrix.set(4, 1, Graph(4, 1, "D"));

    cout << endl;

    for (int i = 0; i < bigGraphMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigGraphMatrix.getSizeY(); j++) {
            cout << bigGraphMatrix.at(i, j).getValue().getName() << (j != bigGraphMatrix.getSizeY() - 1 ? " ; " : "");
        }
        cout << endl;
    }

    cout << endl;

    SparseMatrix2D bigIntMatrix(10, 10, 2);
    bigIntMatrix.set(0, 0, 9);
    bigIntMatrix.set(1, 0, 9);
    bigIntMatrix.set(2, 3, 7);
    bigIntMatrix.set(5, 5, 8);
    bigIntMatrix.set(2, 3, 7);
    bigIntMatrix.set(2, 2, 4);
    bigIntMatrix.set(10, 12, 1); //izven
    bigIntMatrix.set(2, 8, 7);

    for (int i = 0; i < bigIntMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigIntMatrix.getSizeY(); j++) {
            cout << bigIntMatrix.at(i, j).getValue() << (j != bigIntMatrix.getSizeY() - 1 ? " ; " : "");
        }
        cout << endl;
    }

    cout << endl;
    bigIntMatrix.clearRow(2);

    for (int i = 0; i < bigIntMatrix.getSizeX(); i++) {
        for (int j = 0; j < bigIntMatrix.getSizeY(); j++) {
            cout << bigIntMatrix.at(i, j).getValue() << (j != bigIntMatrix.getSizeY() - 1 ? " ; " : "");
        }
        cout << endl;
    }

    return 0;
}