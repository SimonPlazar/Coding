
#include "TextUtility.h"

TextUtility::TextUtility() = default;

std::string TextUtility::capitalize(const std::string &str) {
    std::string output = str;

    for (int i = 0; i < str.length(); ++i) {
        if (i == 0)
            output[i] = toUpperCase(output[i]);
        if ((output[i] == '.' || output[i] == '?' || output[i] == '!') && i+2 < str.length()) {
            output[i + 2] = toUpperCase(output[i + 2]);
        }
    }
    return output;
}

std::string TextUtility::toUpperCase(const std::string &str) {
    std::string tmpStr = str;

    for (int i = 0; i < str.length(); ++i) {
        tmpStr[i] = toUpperCase(str[i]);
    }

    return tmpStr;
}

std::string TextUtility::toLowerCase(const std::string &str) {
    std::string tmpStr = str;

    for (int i = 0; i < str.length(); ++i) {
        tmpStr[i] = toLowerCase(str[i]);
    }

    return tmpStr;
}

char TextUtility::toUpperCase(char chr) {
    unsigned int asc = int(chr);
    if (64 < asc && asc < 91) {
        //already capital
        return chr;
    } else if (96 < asc && asc < 123) {
        //make capital
        asc -= 32;
        return char(asc);
    }
    return chr;
}

char TextUtility::toLowerCase(char chr) {
    unsigned int asc = int(chr);
    if (64 < asc && asc < 91) {
        //make lower case
        asc += 32;
        return char(asc);
    } else if (96 < asc && asc < 123) {
        //already lower case
        return chr;
    }
    return chr;
}

bool TextUtility::isNumeric(const std::string &str) {
    for (char i: str) {
        if (!isdigit(i))
            return false;
    }
    return true;
}

int TextUtility::contains(const std::string &str, const std::string &substr) {
    for (int i = 0; i <= str.length() - substr.length(); i++) {
        int j;

        for (j = 0; j < substr.length() && str[i + j] == substr[j]; j++) {}

        if (j == substr.length())
            return i;
    }
    return -1;
}

std::string TextUtility::removeMultiSpace(const std::string &str) {
    std::string strtmp = str;
    for (int i = strtmp.size() - 1; i > 0; i--) {
        if ((strtmp[i] == ' ' && strtmp[i] == strtmp[i - 1]) ||
            ((strtmp[i] == '.' || strtmp[i] == ',' || strtmp[i] == '?' || strtmp[i] == '!') && strtmp[i - 1] == ' ')) {
            strtmp.erase(strtmp.begin() + i - 1);
        }
    }
    return strtmp;
}
