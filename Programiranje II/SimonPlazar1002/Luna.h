//
// Created by simon on 24/05/2022.
//

#ifndef SIMONPLAZAR1002_LUNA_H
#define SIMONPLAZAR1002_LUNA_H


#include "NebesnoTelo.h"
#include "Satelit.h"

class Luna : public NebesnoTelo, public Satelit{
private:
    unsigned int povrsina;

public:
    Luna(std::string ime, unsigned int masa, unsigned int visina, unsigned int povrsina);

    std::string toString() const override;
};


#endif //SIMONPLAZAR1002_LUNA_H
