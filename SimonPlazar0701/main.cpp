#include "VectorUtil.h"
#include "Computer.h"

int main() {
    srand(time(nullptr));

    std::vector<Computer> computers;
    fillDefault<5>(computers);
    print(computers);

    std::vector<Speakers> speakers;
    fillDefault<7>(speakers);
    print(speakers);

    std::vector<Speakers> speakersReverse;
    speakersReverse = reverse(speakers);
    print(speakersReverse);

    std::vector<std::string> strs = {"abc", "def", "ghi"};

    std::string str = mergeLists(strs);

    std::cout<<str;

    return 0;
}
