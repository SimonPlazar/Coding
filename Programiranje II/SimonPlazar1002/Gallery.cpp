#include "Gallery.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <iostream>

bool ascendingYear(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j) {
    if (i->getYear() <= j->getYear()) return true;
    return false;
}

bool descandingYear(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j) {
    if (i->getYear() >= j->getYear()) return true;
    return false;
}

bool ascendingPrice(std::shared_ptr<Artwork> i, std::shared_ptr<Artwork> j) {
    if (i->getPrice() <= j->getPrice()) return true;
    return false;
}

bool isRenaissanceArt(std::shared_ptr<Artwork> a) {
    if (1400 < a->getYear() && a->getYear() < 1600) return true;
    return false;
}

Gallery::Gallery(std::string name) : name(std::move(name)) {
}

void Gallery::addArtwork(const std::shared_ptr<Artwork>& artwork) {
    this->artworks.push_back(artwork);
}


void Gallery::printArtworks() const {
    for (auto &artwork: artworks) {
        artwork->print();
    }
}

std::string Gallery::toString() const {
    std::stringstream ss;
    ss << this->name;
    for (auto &artwork: artworks) {
        ss << std::endl;
        ss << artwork->toString();
    }

    return ss.str();
}

void Gallery::removeArtwork(const std::shared_ptr<Artwork>& artwork) {
    for (int i = 0; i < this->artworks.size(); ++i) {
        if (this->artworks[i]->toString() == artwork->toString()) {
            artworks.erase(artworks.begin() + i);
            break;
        }
    }
}

std::vector<std::shared_ptr<Artwork>> Gallery::getArtworksBetweenYear(unsigned int startYear, unsigned int endYear) const {
    std::vector<std::shared_ptr<Artwork>> between;
    for (const auto& artwork: artworks)
        if (startYear <= artwork->getYear() && artwork->getYear() <= endYear)
            between.push_back(artwork);

    return between;
}

void Gallery::sort(bool (*c)(std::shared_ptr<Artwork>, std::shared_ptr<Artwork>)) {
    for (int i = 0; i < artworks.size() - 1; ++i)
        for (int j = 0; j < artworks.size() - i - 1; ++j)
            if (!c(artworks[j], artworks[j + 1]))
                std::swap(artworks[j], artworks[j + 1]);
}

std::shared_ptr<Artwork> Gallery::find(std::function<bool(std::shared_ptr<Artwork>)> c) const{
    auto it = std::find_if(artworks.begin(), artworks.end(), isRenaissanceArt);

    if (it != artworks.end() && isRenaissanceArt(*it))
        return *it;
    else
        return  std::make_shared<Artwork>();
}

void Gallery::printArtworks(PrintIfPainting i) const{
    std::for_each(artworks.begin(), artworks.end(), i);
}

void Gallery::filterOut(std::function<bool(std::shared_ptr<Artwork>)> c) {
    for (int i = 0; i < artworks.size(); ++i) {
        if (c(artworks[i])) {
            artworks.erase(artworks.begin() + i);
            i--;
        }
    }
}
