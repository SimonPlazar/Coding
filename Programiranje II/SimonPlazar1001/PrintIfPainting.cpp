//
// Created by simon on 15/05/2022.
//

#include <iostream>
#include "PrintIfPainting.h"
#include "Painting.h"

void PrintIfPainting::operator()(Artwork *e) {
    if(dynamic_cast<Painting*>(e))
        std::cout << e->toString()<<std::endl;
}
