//
// Created by simon on 23/05/2022.
//

#ifndef SIMONPLAZAR1101_UNPARSEABLEDATEEXCEPTION_H
#define SIMONPLAZAR1101_UNPARSEABLEDATEEXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

class UnparseableDateException : public std::exception{
private:
    std::string message;
public:
    const char * what() const noexcept override;

    explicit UnparseableDateException(const std::string& badDate);
};


#endif //SIMONPLAZAR1101_UNPARSEABLEDATEEXCEPTION_H
