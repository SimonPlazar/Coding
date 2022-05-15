//
// Created by simon on 15/05/2022.
//

#include <iostream>
#include "PrintIfPainting.h"
#include "Painting.h"

void PrintIfPainting::operator()(const std::shared_ptr<Artwork>& e) {
    if(std::dynamic_pointer_cast<Painting>(e))
        std::cout << e->toString()<<std::endl;
}
