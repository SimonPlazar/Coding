//
// Created by simon on 24/05/2022.
//

#include "WrongDateException.h"

WrongDateException::WrongDateException(const std::string& date) : message("Wrong date: "+ date) {}

const char *WrongDateException::what() const noexcept {
    return message.c_str();
}
