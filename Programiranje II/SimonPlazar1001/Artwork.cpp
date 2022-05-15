#include "Artwork.h"
#include <iostream>
#include <sstream>
#include <utility>



Artwork::Artwork(std::string title, std::string description, double price, int year, Artist* artist) : title(std::move(title)), description(std::move(description)), price(price), year(year), artist(artist){
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

Artist *Artwork::getArtist() const {
    return artist;
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

void Artwork::setArtist(Artist *x) {
    Artwork::artist = x;
}

std::string Artwork::toString() const {
    std::stringstream ss;
    ss << title << ", " << description << ", " << year << ", " << price << "$" << std::endl << artist->toString();
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

Artwork::Artwork() : title(""), description(""), price(0), year(0), artist(new Artist()) {}
