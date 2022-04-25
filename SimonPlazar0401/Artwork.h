#ifndef SIMONPLAZAR0401_ARTWORK_H
#define SIMONPLAZAR0401_ARTWORK_H

#include <string>
#include "Artist.h"
#include "Dimension.h"

class Artwork {
private:
    std::string title;
    std::string description;
    double price;
    int year;
    Artist* artist;
    Dimension* dimension{};
public:

    Artwork(std::string title, std::string description, double price, int year, Artist* artist, double width, double height, double depth);

    std::string getTitle() const;

    std::string getDescription() const;

    double getPrice() const;

    int getYear() const;

    Artist *getArtist() const;

    void setTitle(std::string a);

    void setDescription(std::string b);

    void setPrice(double c);

    void setYear(int d);

    void setArtist(Artist *x);

    std::string toString() const;

    void print() const;

    bool isExpensive(const Artwork *second) const;
};

#endif //SIMONPLAZAR0401_ARTWORK_H
