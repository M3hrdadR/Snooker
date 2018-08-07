//
// Created by mehrdad on 7/23/18.
//

#ifndef BILIARD_START_H
#define BILIARD_START_H

#include "Game.h"
#include "../Headers/Resource.h"
#include "../Headers/Network.h"

bool In_target_ball(int x, int y, Game * game);

bool In_table(int x,int y, Game * game);

void start_game(std::string ip, bool is_server);

#endif //BILIARD_START_H
