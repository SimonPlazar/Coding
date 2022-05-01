#include "Artwork.h"
#include <iostream>
#include <sstream>
#include <utility>

Artwork::Artwork() {
    title = "";
    description = "";
    price = 0;
    year = 0;
}

Artwork::Artwork(std::string newTitle, std::string newDescription, double newPrice, int newYear) {
    title = std::move(newTitle);
    description = std::move(newDescription);
    price = newPrice;
    year = newYear;
}

std::string Artwork::getTitle() const {
    return title;
}

std::string Artwork::getDescription() const {
    return description;
}

double Artwork::getPrice() const {
    return price;
}

int Artwork::getYear() const {
    return year;
}

void Artwork::setTitle(std::string x) {
    title = std::move(x);
}

void Artwork::setDescription(std::string x) {
    description = std::move(x);
}

void Artwork::setPrice(double x) {
    price = x;
}

void Artwork::setYear(int x) {
    year = x;
}

std::string Artwork::toString() const {
    std::stringstream ss;
    ss << "[" << title << ", " << description << " " << year << " " << price << "$]";
    return ss.str();
}

void Artwork::print() const{
    std::cout << toString() << std::endl;
}


bool Artwork::isExpensive(const Artwork *second) const {
    if (price > second->getPrice())
        return true;
    else
        return false;
}
