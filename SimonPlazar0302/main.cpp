#include <iostream>
#include "TextUtility.h"

int main() {
    std::cout << TextUtility::capitalize(
            "lorem ipsum dolor, adipiscing magna? facil isi 2.5 morbi tempus urna id. Gravida non tellus orci! molestieac sed lectus.");

    std::cout << TextUtility::toUpperCase("asdgf fd") << std::endl;
    std::cout << TextUtility::toUpperCase('a') << std::endl;

    std::cout << TextUtility::toLowerCase("ASF ASasf ADA") << std::endl;
    std::cout << TextUtility::toLowerCase('A') << std::endl;

    std::cout << TextUtility::isNumeric("123d 12") << std::endl;
    std::cout << TextUtility::isNumeric("123") << std::endl;

    std::cout << TextUtility::contains("Lorem ipsum dolor.", "sum") << std::endl;

    std::cout << TextUtility::removeMultiSpace("Lorem   ipsum   do  lor  .   ") << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
