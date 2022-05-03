#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {
    LinkedList<int> list;

    std::cout << "List " << (list.isEmpty() ? "IS" : "IS NOT") << " empty." << std::endl << std::endl;

    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    std::cout << "List " << (list.isEmpty() ? "IS" : "IS NOT") << " empty." << std::endl << std::endl;

    list.print();

    std::cout << std::endl;

    std::cout << list.getSize() << std::endl;

    std::cout << list.at(3) << std::endl;

    for(int i=0; i<list.getSize(); i++)
        std::cout << list.at(i) << " ";

    list.removeAt(3);

    std::cout << std::endl;

    list.print();

    list.removeAt(1);

    std::cout << std::endl;

    list.print();

    return 0;
}
