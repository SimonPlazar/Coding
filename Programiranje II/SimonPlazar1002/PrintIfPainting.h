//
// Created by simon on 15/05/2022.
//

#ifndef SIMONPLAZAR1001_PRINTIFPAINTING_H
#define SIMONPLAZAR1001_PRINTIFPAINTING_H

#include "Artwork.h"

class PrintIfPainting {
public:
    void operator()(const std::shared_ptr<Artwork>& e);
};


#endif //SIMONPLAZAR1001_PRINTIFPAINTING_H
