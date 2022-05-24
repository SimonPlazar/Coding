#ifndef SIMONPLAZAR0401_GALLERY_H
#define SIMONPLAZAR0401_GALLERY_H

#include <vector>
#include <string>
#include <functional>
#include "Artwork.h"
#include "PrintIfPainting.h"

class Gallery {
private:
    std::string name;
    std::vector<std::shared_ptr<Artwork>> artworks;
public:
    explicit Gallery(std::string name);

    void addArtwork(const std::shared_ptr<Artwork>& artwork);

    void removeArtwork(const std::shared_ptr<Artwork>& artwork);

    std::vector<std::shared_ptr<Artwork>> getArtworksBetweenYear(unsigned int startYear, unsigned int endYear) const;

    void printArtworks() const;

    std::string toString() const;

    void sort(bool (*c)(std::shared_ptr<Artwork>, std::shared_ptr<Artwork>));

    std::shared_ptr<Artwork> find(std::function<bool(std::shared_ptr<Artwork>)> c) const;

    void printArtworks(PrintIfPainting i) const;

    void filterOut(std::function<bool(std::shared_ptr<Artwork>)> c);
};

bool ascendingYear(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j);
bool descandingYear(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j);
bool ascendingPrice(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j);

bool isRenaissanceArt(std::shared_ptr<Artwork> a);


#endif //SIMONPLAZAR0401_GALLERY_H
