#include <sstream>
#include <utility>
#include "Artist.h"

Artist::Artist() : dateOfBirth(Date()) {
}

Artist::Artist(std::string name, std::string biography, Date dateOfBirth) : name(std::move(name)),
                                                                            biography(std::move(biography)),
                                                                            dateOfBirth(dateOfBirth) {
}

std::string Artist::toString() const {
    std::stringstream ss;
    ss << name << std::endl << biography << std::endl << dateOfBirth.toString();
    return ss.str();
}

const std::string &Artist::getName() const {
    return name;
}

const std::string &Artist::getBiography() const {
    return biography;
}

Date Artist::getDateOfBirth() const {
    return dateOfBirth;
}

void Artist::setName(const std::string &x) {
    Artist::name = x;
}

void Artist::setBiography(const std::string &x) {
    Artist::biography = x;
}

void Artist::setDateOfBirth(Date x) {
    Artist::dateOfBirth = x;
}


