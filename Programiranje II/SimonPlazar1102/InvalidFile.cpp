//
// Created by simon on 23/05/2022.
//

#include "InvalidFile.h"

const char *InvalidFile::what() const noexcept {
    return message.c_str();
}

InvalidFile::InvalidFile(const std::string& fileName) : message("Could not reach " + fileName + ".") {}
