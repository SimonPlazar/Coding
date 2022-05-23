//
// Created by simon on 23/05/2022.
//

#include "UnparseableDateException.h"

const char * UnparseableDateException::what() const noexcept {
    return message.c_str();
}

UnparseableDateException::UnparseableDateException(const std::string& badDate) : message("Unparseable date: " + badDate + ".") {}
