#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    std::string input, output;

    unsigned int x;
    std::stringstream ss;


    std::cout << "Vnesite stevilo za kodiranje (BIN):";
    std::getline(std::cin, input);

    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    x = stoi(input, nullptr, 2);
    if (x < 128) {
        output = "0";
        for (int i = 6; i >= 0; i--) {
            output += to_string((x >> i) & 1);
        }
    } else if ((x == 254) || (x == 255)) {
        output = "Error: Ni dovoljena koda!";
    } else if (x < 2048) {
        output = "110";
        for (int i = 10; i >= 6; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 5; i >= 0; i--) {
            output += to_string((x >> i) & 1);
        }
    } else if (x < 65536) {
        output = "1110";
        for (int i = 15; i >= 12; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 11; i >= 6; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 5; i >= 0; i--) {
            output += to_string((x >> i) & 1);
        }
    } else if (x < 2097152) {
        output = "11110";
        for (int i = 20; i >= 18; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 17; i >= 12; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 11; i >= 6; i--) {
            output += to_string((x >> i) & 1);
        }
        output += " 10";
        for (int i = 5; i >= 0; i--) {
            output += to_string((x >> i) & 1);
        }
    } else {
        cout << "error";
    }

    cout << "Rezultat kodiranja UTF-8 je (BIN):" << output << endl;

    input = "";
    std::cout << "Vnesite kod UTF-8 za dekodiranje (BIN):";
    std::getline(std::cin, input);

    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    int count = 0;

    for (int i = 0; (i < input.size()) && (input[i] != '0'); ++i) {
        count++;
    }

    switch (count) {
        case 0:
            output = input;
            break;
        case 1:
            output = "00000000 Error: Premalo stevilo!";
            break;
        case 2:
            if (input.size() < 16) {
                output = "00000000 Error: Premalo stevilo!";
                break;
            }
            output = "00000";
            output += input.substr(3, 3) + " ";
            output += input.substr(6, 2) + input.substr(10, 6);
            break;
        case 3:
            if (input.size() < 24) {
                output = "00000000 Error: Premalo stevilo!";
                break;
            }
            output = input.substr(4, 4) + input.substr(10, 4) + " ";
            output += input.substr(14, 2) + input.substr(18, 6);
            break;
        case 4:
            if (input.size() < 32) {
                output = "00000000 Error: Premalo stevilo!";
                break;
            }
            output = "000";
            output += input.substr(5, 3) + input.substr(10, 2) + " ";
            output += input.substr(12, 4) + input.substr(18, 4) + " ";
            output += input.substr(22, 2) + input.substr(26, 6);
            break;
        default:
            output = "Error";
            break;
    }

    if ((input == "1100001110111111") || (input == "1100001110111110")) {
        output = "Error: Ni dovoljena koda!";
    }

    cout << "Rezultat dekodiranja UTF-8 je (BIN):" << output;

    return 0;
}
