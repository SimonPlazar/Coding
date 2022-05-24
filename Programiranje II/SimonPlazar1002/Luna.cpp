//
// Created by simon on 24/05/2022.
//

#include "Luna.h"
#include <utility>

Luna::Luna(std::string ime, unsigned int masa, unsigned int visina, unsigned int povrsina) : povrsina(povrsina),
                                                                                             Satelit(masa, visina),
                                                                                             NebesnoTelo(std::move(ime),
                                                                                                         masa) {}

std::string Luna::toString() const {
    return ime + "\n" + Satelit::toString() + " " + std::to_string(povrsina) + "M m2";
}
