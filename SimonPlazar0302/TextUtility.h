#ifndef SIMONPLAZAR0302_TEXTUTILITY_H
#define SIMONPLAZAR0302_TEXTUTILITY_H

#include <string>

class TextUtility {
private:
    TextUtility();

public:
    static std::string capitalize(const std::string &str);

    static std::string toUpperCase(const std::string &str);

    static bool isNumeric(const std::string &str);

    static int contains(const std::string &str, const std::string &substr);

    static char toUpperCase(char chr);

    static char toLowerCase(char chr);

    static std::string toLowerCase(const std::string &str);

    static std::string removeMultiSpace(const std::string &str);
};

#endif //SIMONPLAZAR0302_TEXTUTILITY_H
