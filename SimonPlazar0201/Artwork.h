#ifndef VAJA0201_ARTWORK_H
#define VAJA0201_ARTWORK_H

#include <string>

class Artwork {
private:
    std::string title;
    std::string description;
    double price;
    int year;
public:
    Artwork();

    Artwork(std::string title, std::string description, double price, int year);

    std::string getTitle() const;

    std::string getDescription() const;

    double getPrice() const;

    int getYear() const;

    void setTitle(std::string x);

    void setDescription(std::string x);

    void setPrice(double x);

    void setYear(int d);

    std::string toString() const;

    void print() const;

    bool isExpensive(const Artwork *second) const;
};

#endif //VAJA0201_ARTWORK_H

