#ifndef SIMONPLAZAR0401_GALLERY_H
#define SIMONPLAZAR0401_GALLERY_H

#include <vector>
#include <string>
#include "Artwork.h"

class Gallery {
private:
    std::string name;
    std::vector<Artwork *> artworks;
public:
    explicit Gallery(std::string name);

    void addArtwork(Artwork *artwork);

    void removeArtwork(Artwork *artwork);

    std::vector<Artwork *> getArtworksBetweenYear(unsigned int startYear, unsigned int endYear) const;

    void printArtworks() const;

    std::string toString() const;

    std::vector<Artist *> getAllArtists() const;
};


#endif //SIMONPLAZAR0401_GALLERY_H
