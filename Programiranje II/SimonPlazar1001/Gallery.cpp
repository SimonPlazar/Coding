#include "Gallery.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <iostream>

bool ascendingYear(Artwork* i, Artwork* j){
if(i->getYear() <= j->getYear()) return true;
return false;
}

bool descandingYear(Artwork* i, Artwork* j){
    if(i->getYear() >= j->getYear()) return true;
    return false;
}

bool ascendingPrice(Artwork* i, Artwork* j){
    if(i->getPrice() <= j->getPrice()) return true;
    return false;
}

bool isRenaissanceArt(Artwork* a){
    if(1400 < a->getYear() && a->getYear() < 1600 ) return true;
    return false;
}

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
        return new Artwork();
}

void Gallery::printArtworks(PrintIfPainting i) {
    std::for_each(artworks.begin(), artworks.end(), i);
}
