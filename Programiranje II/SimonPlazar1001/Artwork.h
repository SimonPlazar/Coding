#ifndef SIMONPLAZAR0401_ARTWORK_H
#define SIMONPLAZAR0401_ARTWORK_H

#include <string>
#include "Artist.h"

class Artwork {
protected:
    std::string title;
    std::string description;
    double price;
    int year;
    Artist* artist;
public:
    Artwork();

    Artwork(std::string title, std::string description, double price, int year, Artist* artist);

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

    virtual std::string toString() const;

    virtual void print() const;

    bool isExpensive(const Artwork *second) const;
};

#endif //SIMONPLAZAR0401_ARTWORK_H
