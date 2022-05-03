#include <iostream>
#include <sstream>
#include <utility>
#include "PrintUtility.h"

class Oseba {
private:
    std::string ime;
    std::string priimek;
    std::string opis;
public:
    Oseba(std::string ime, std::string priimek, std::string opis) : ime(std::move(ime)), priimek(std::move(priimek)),
                                                                    opis(std::move(opis)) {
    }

    std::string toString() const {
        return ime + " " + priimek + " " + opis;
    }
};


template<ColorCode color = ColorCode::Green, typename T>
void printColor(std::vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        PrintUtility::print(color, vec[i]);
        std::cout << std::endl;
    }
}

template<int N, typename T>
std::vector<std::vector<T>> slice(std::vector<T> vec) {
    std::vector<std::vector<T>> output;
    std::vector<T> elementVec;
    int count = 0;
    while (count < vec.size()) {
        elementVec.clear();
        for (int i = 0; i < N && count < vec.size(); ++i) {
            elementVec.push_back(vec[count]);
            count++;
        }
        output.push_back(elementVec);
    }
    return output;
}

void switchBannedWords(std::string &string, const std::vector<std::string> &prepovedaneBesede) {
    std::string censored;
    for (const auto &i: prepovedaneBesede) {
        while (string.find(i) != std::string::npos) {
            censored = "";
            for (int j = 0; j < i.length(); ++j) {
                censored += '*';
            }
            string.replace(string.find(i), i.length(), censored);
        }
    }
}

template<typename T>
std::string toSafeString(std::vector<T> objekti, const std::vector<std::string> &prepovedaneBesede) {
    std::string string;

    for (int i = 0; i < objekti.size(); ++i) {
        string += objekti[i].toString() + "\n";
    }

    switchBannedWords(string, prepovedaneBesede);

    return string;
}

bool checkPalindrom(const std::string &string) {
    int size = (int) string.length();
    for (int i = 0; i < size / 2; ++i) {
        if (string[i] != string[size - i - 1])
            return false;
    }
    return true;
}

template<typename T>
bool isPalindrome(std::vector<T> objekti) {
    std::string string;

    for (int i = 0; i < objekti.size(); ++i) {
        string += objekti[i].toString() + "\n";
    }

    return checkPalindrom(string);
}

template<typename T>
std::vector<T> mergeVec(const std::vector<std::vector<T>> &vec) {
    std::vector<T> output;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            output.push_back(vec[i][j]);
        }
    }
    return output;
}

template<typename T>
std::vector<unsigned int> countWords(std::vector<T> objekti, std::vector<std::string> besede) {
    std::string string;
    std::vector<unsigned int> count;
    std::string beseda;

    for (int i = 0; i < besede.size(); ++i) {
        count.push_back(0);
    }

    for (int i = 0; i < objekti.size(); ++i) {
        string += objekti[i].toString() + " ";
    }

    std::istringstream ss(string);

    while (ss>>beseda){
        for (int i = 0; i < besede.size(); ++i) {
            if(besede[i] == beseda)
                count[i]++;
        }
    }

    return count;
}

int main() {
    using std::operator ""s;
    system(("chcp "s + std::to_string(65001)).c_str());

    std::vector<std::string> vec = {"abc", "def", "ghi"};

    printColor(vec);

    std::vector<std::string> vec1 = {"abc", "def", "ghi", "abc", "def", "ghi", "abc", "def", "ghi",};

    std::vector<std::vector<std::string>> vecVec = slice<2>(vec1);

    for (auto &i: vecVec) {
        for (auto &j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }


    Oseba a("danes", "je", "lep dan, abc ni lepa beseda");
    std::vector<Oseba> osebaA = {a};

    std::string str = "danes je lep dan, abc ni lepa beseda";

    std::cout << toSafeString(osebaA, vec) << std::endl;

    std::vector<std::string> vector = mergeVec(vecVec);

    for (auto &i: vector) {
        std::cout << i << std::endl;
    }

    std::cout << isPalindrome(osebaA) << std::endl;

    Oseba prva("danes", "je", "lep dan abc abc ni lepa beseda");
    Oseba druga("danes", "ni", "lep dan dan dan");

    std::vector<Oseba> osebe{prva, druga};

    std::vector<std::string> besede{"abc", "dan"};

    std::cout << std::endl;

    std::vector<unsigned int> count = countWords(osebe, besede);

    for (unsigned int i : count) {
        std::cout << i << std::endl;
    }

    return 0;
}
