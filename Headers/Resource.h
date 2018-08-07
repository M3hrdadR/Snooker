//
// Created by mehrdad on 7/24/18.
//
// Created by mehrdad on 7/24/18.
//

#ifndef BILIARD_RESOURCE_H
#define BILIARD_RESOURCE_H
#include "Game.h"
#include <string>

class Resource {
public:
    Resource(Game* game);

    void set(std::string);
    std::string get();
private:
    Game* game;
};


#endif //BILIARD_RESOURCE_H
