#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <fstream>

using namespace std;

struct node {
    int prev = 0;
    int len = 0;
    int status = 0;
    int index = 0;
    string name;
};

class Graph {
private:
    vector<node *> vertices;
    vector<vector<int>> matrix;

    stack<node *> stack;
    queue<node *> queue;
public:
    const vector<node *> &getVertices() const {
        return vertices;
    }

    void printVertices() {
        for (auto &vertice: vertices) {
            cout << endl;
            cout << "int prev: " << vertice->prev << endl
                 << "int len: " << vertice->len << endl
                 << "int status: " << vertice->status << endl
                 << "int index: " << vertice->index << endl
                 << "string name: " << vertice->name << endl;
        }
        cout << endl;
    }

    void printPath(node *start, node *point) {
        if (point == start) cout << "Pot je: " + point->name + " ";
        else {
            if (point->prev == -1)
                cout << "Med " + start->name + " in " + point->name + " ni poti!" << endl;
            else {
                printPath(start, vertices[point->prev]);
                cout << point->name + " ";
            }
        }
    }

    void printMatrix() {
        for (auto &row: matrix) {
            for (int column: row) {
                cout << column << " ";
            }
            cout << endl;
        }
    }

    void readFromFile() {
        int point1, point2, cost, verticesCount, edgesCount;
        ifstream f("grafBig.txt");
        f >> verticesCount;
        f >> edgesCount;

        for (int i = 0; i < verticesCount; ++i) {
            matrix.emplace_back();
            for (int j = 0; j < verticesCount; ++j) {
                matrix[i].push_back(0);
            }
        }

        for (int i = 0; i < verticesCount; ++i) {
            vertices.push_back(new node);
            vertices[i]->index = i;
            vertices[i]->name = to_string(i + 1);
        }

        for (int i = 0; i < edgesCount; ++i) {
            f >> point1 >> point2 >> cost;
            matrix[point1 - 1][point2 - 1] = cost;
            matrix[point2 - 1][point1 - 1] = cost;
        }

        //izpis
        //printMatrix();
    }

    void getNeighbours(vector<node *> &neighbours, node *point) {
        for (int i = 0; i < matrix[point->index].size(); ++i)
            if (matrix[point->index][i] > 0)
                neighbours.push_back(vertices[i]);

    }

    //
    // status: 0 - ne pregledan, 1 - v obdelavi, 2 - razvito
    //

    void depthSearch(node *start, node *end) {
        for (int i = 0; i < stack.size(); ++i) {
            stack.pop();
        }

        for (auto &vertice: vertices) {
            if (vertice == start) continue;
            vertice->status = 0;
            vertice->len = INT32_MAX;
            vertice->prev = -1;
        }

        start->status = 1;
        start->len = 0;
        start->prev = -1;

        stack.push(start);

        while (!stack.empty()) {
            vector<node *> neighbours;
            node *current = stack.top();
            stack.pop();

            if (current == end) return;

            //get sosede
            getNeighbours(neighbours, current);

            for (auto &neighbour: neighbours) {
                if (neighbour->status == 0) {
                    neighbour->status = 1;
                    neighbour->len = current->len + 1;
                    neighbour->prev = current->index;
                    stack.push(neighbour);
                }
            }
            current->status = 2;
        }
    }

    void widthSearch(node *start, node *end) {
        for (int i = 0; i < queue.size(); ++i) {
            queue.pop();
        }

        for (auto &vertice: vertices) {
            if (vertice == start) continue;
            vertice->status = 0;
            vertice->len = INT32_MAX;
            vertice->prev = -1;
        }

        start->status = 1;
        start->len = 0;
        start->prev = -1;

        queue.push(start);

        while (!queue.empty()) {
            vector<node *> neighbours;
            node *current = queue.front();
            queue.pop();

            if (current == end) return;

            //get sosede
            getNeighbours(neighbours, current);

            for (auto &neighbour: neighbours) {
                if (neighbour->status == 0) {
                    neighbour->status = 1;
                    neighbour->len = current->len + 1;
                    neighbour->prev = current->index;
                    queue.push(neighbour);
                }
            }
            current->status = 2;
        }
    }

    ~Graph() {
        for (auto &vertice: vertices) {
            delete vertice;
        }
    }
};


int main() {
    int choice = 0;
    int value1 = 0;
    int value2 = 0;
    Graph graf;

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    do {
        cout << "\nIskanje v globino in sirino\n"
                "1) Preberi graf iz datoteke\n"
                "2) Pozeni iskanje v globino iz vozlisca s do d\n"
                "3) Pozeni iskanje v sirino iz vozlisca s do d\n"
                "4) Konec\n"
                "Izbira:";
        cin >> choice;

        while (cin.fail()) {
            cout << "Napacna izbira\nIzbira:";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                graf.readFromFile();
                break;
            case 2:
                cout << "Podaj ime za zacetek:";
                cin >> value1;

                while (cin.fail()) {
                    cout << "Napacna izbira\nPodaj ime za zacetek:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> value1;
                }

                cout << "Podaj ime za konec:";
                cin >> value2;

                while (cin.fail()) {
                    cout << "Napacna izbira\nPodaj ime za konec:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> value2;
                }

                start = chrono::steady_clock::now();
                graf.depthSearch(graf.getVertices()[value1 - 1], graf.getVertices()[value2 - 1]);
                end = chrono::steady_clock::now();

                graf.printVertices();

                graf.printPath(graf.getVertices()[value1 - 1], graf.getVertices()[value2 - 1]);

                cout << "\nCas: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 3:
                cout << "Podaj ime za zacetek:";
                cin >> value1;

                while (cin.fail()) {
                    cout << "Napacna izbira\nPodaj ime za zacetek:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> value1;
                }

                cout << "Podaj ime za konec:";
                cin >> value2;

                while (cin.fail()) {
                    cout << "Napacna izbira\nPodaj ime za konec:";
                    cin.clear();
                    cin.ignore(256, '\n');
                    cin >> value2;
                }

                start = std::chrono::steady_clock::now();
                graf.widthSearch(graf.getVertices()[value1 - 1], graf.getVertices()[value2 - 1]);
                end = std::chrono::steady_clock::now();

                graf.printVertices();

                graf.printPath(graf.getVertices()[value1 - 1], graf.getVertices()[value2 - 1]);

                cout << "\nCas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns"
                     << endl;
                break;
            case 4:
                cout << "Konec" << endl;
                break;
            default:
                cout << "Napacna value!" << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
