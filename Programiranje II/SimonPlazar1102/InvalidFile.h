//
// Created by simon on 23/05/2022.
//

#ifndef SIMONPLAZAR1102_INVALIDFILE_H
#define SIMONPLAZAR1102_INVALIDFILE_H

#include <exception>
#include <string>

class InvalidFile : public std::exception{
private:
    std::string message;
public:
    const char * what() const noexcept override;

    explicit InvalidFile(const std::string& fileName);
};


#endif //SIMONPLAZAR1102_INVALIDFILE_H
