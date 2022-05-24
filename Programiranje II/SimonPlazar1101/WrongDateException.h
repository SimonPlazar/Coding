//
// Created by simon on 24/05/2022.
//

#ifndef SIMONPLAZAR1101_WRONGDATEEXCEPTION_H
#define SIMONPLAZAR1101_WRONGDATEEXCEPTION_H

#include <string>

class WrongDateException : public std::exception{
private:
    std::string message;
public:
    const char * what() const noexcept override;

    explicit WrongDateException(const std::string& date);
};


#endif //SIMONPLAZAR1101_WRONGDATEEXCEPTION_H
