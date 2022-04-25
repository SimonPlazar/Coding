#include "Gallery.h"
#include <utility>
#include <sstream>

Gallery::Gallery(std::string name) : name(std::move(name)){
}

void Gallery::addArtwork(Artwork *artwork) {
    this->artworks.push_back(artwork);
}



void Gallery::printArtworks() const{
    for (auto & artwork : artworks) {
        artwork->print();
    }
}

std::string Gallery::toString() const{
    std::stringstream ss;
    ss << this->name;
    for (auto & artwork : artworks) {
        ss<<std::endl;
        ss<<artwork->toString();
    }

    return ss.str();
}

void Gallery::removeArtwork(Artwork *artwork) {
    for (int i = 0; i < this->artworks.size(); ++i){
        if (this->artworks[i]->toString() == artwork->toString()){
            artworks.erase(artworks.begin() + i);
            break;
        }
    }
}

std::vector<Artwork *> Gallery::getArtworksBetweenYear(unsigned int startYear, unsigned int endYear) const{
    std::vector<Artwork *> between;
    for (auto artwork: artworks)
        if (startYear <= artwork->getYear() && artwork->getYear() <= endYear)
            between.push_back(artwork);

    return between;
}
