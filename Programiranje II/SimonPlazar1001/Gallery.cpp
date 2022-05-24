#include "Gallery.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <iostream>

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

void Gallery::sort(bool (*c)(Artwork *, Artwork *)) {
    for (int i = 0; i < artworks.size()-1; ++i)
        for (int j = 0; j < artworks.size()-i-1; ++j)
            if (!c(artworks[j], artworks[j+1]))
                std::swap(artworks[j], artworks[j+1]);
}

Artwork *Gallery::find(bool (*c)(Artwork *)) {
    auto it = std::find_if(artworks.begin(), artworks.end(), c);

    if(it != artworks.end() && c(*it))
        return *it;
    else
        return nullptr;
}

void Gallery::printArtworks(PrintIfPainting i) const{
    std::for_each(artworks.begin(), artworks.end(), i);
}

std::vector<Artwork *> Gallery::findAll(bool (*c)(Artwork *)) const {
    std::vector<Artwork *> output;

    for (auto artwork : artworks)
        if (c(artwork))
            output.push_back(artwork);

    return output;
}
