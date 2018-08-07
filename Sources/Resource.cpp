//
// Created by mehrdad on 7/24/18.
//

#include "../Headers/Resource.h"
#include "../Headers/Game.h"
#include <sstream>
#include <SFML/Network.hpp>
#include <iostream>
using std::cout;
using std::endl;

Resource::Resource(Game *game) {
    this->game = game;
}

void Resource::set(std::string str) {
    std::stringstream inp(str);

    float **coordinates = new float *[22];
    for(int i = 0; i< 22; i++){
        coordinates[i] = new float[2];
    }
    std::string * string = new std::string[2];
    int turn, score;
    inp >> string[0];
    inp >> turn;
    inp >> score;
    for (int i = 0; i < 22; i++) {
        inp >> coordinates[i][0] >> coordinates[i][1];
    }
    inp >> string[1];
    if(string[0] == "|" && string[1] == "|"){
        game->set_turn(turn);
        game->set_enemy_score(score);
        for( int i = 0;i < 22; i++){
            game->get_ball(i).set_x(coordinates[i][0]);
            game->get_ball(i).set_y(coordinates[i][1]);
        }
    }
    return;
}

std::string Resource::get(){
    std::stringstream res;
    res << "|" <<  " " <<this->game->get_turn() << " " << this->game->get_my_score() << " ";
    for(int i = 0; i < 22; i++) {
        res << this->game->get_ball(i).get_x() << " " << this->game->get_ball(i).get_y() << " ";
    }
    res << "|" ;

    return res.str();
}


//sf::Uint16 x = 10;
//std::string s = "hello";
//double d = 0.6;
//
//sf::Packet packet;
//packet << x << s << d;
//
//
//
//sf::Uint16 x;
//std::string s;
//double d;
//
//packet >> x >> s >> d;
//
//if (packet >> x)
//{
//// ok
//}
//else
//{
//// error, failed to read 'x' from the packet
//}

//tcpSocket.send(packet);
//
//tcpSocket.receive(packet);

//        this->game->get_ball(2).get_x() << " " << this->game->get_ball(2).get_y() << " " <<
//        this->game->get_ball(3).get_x() << " " << this->game->get_ball(3).get_y() << " " <<
//        this->game->get_ball(4).get_x() << " " << this->game->get_ball(4).get_y() << " " <<
//        this->game->get_ball(5).get_x() << " " << this->game->get_ball(5).get_y() << " " <<
//        this->game->get_ball(6).get_x() << " " << this->game->get_ball(6).get_y() << " " <<
//        this->game->get_ball(7).get_x() << " " << this->game->get_ball(7).get_y() << " " <<
//        this->game->get_ball(8).get_x() << " " << this->game->get_ball(8).get_y() << " " <<
//        this->game->get_ball(9).get_x() << " " << this->game->get_ball(9).get_y() << " " <<
//        this->game->get_ball(10).get_x() << " " << this->game->get_ball(10).get_y() << " " <<
//        this->game->get_ball(11).get_x() << " " << this->game->get_ball(11).get_y() << " " <<
//        this->game->get_ball(12).get_x() << " " << this->game->get_ball(12).get_y() << " " <<
//        this->game->get_ball(13).get_x() << " " << this->game->get_ball(13).get_y() << " " <<
//        this->game->get_ball(14).get_x() << " " << this->game->get_ball(14).get_y() << " " <<
//        this->game->get_ball(15).get_x() << " " << this->game->get_ball(15).get_y() << " " <<
//        this->game->get_ball(16).get_x() << " " << this->game->get_ball(16).get_y() << " " <<
//        this->game->get_ball(17).get_x() << " " << this->game->get_ball(17).get_y() << " " <<
//        this->game->get_ball(18).get_x() << " " << this->game->get_ball(18).get_y() << " " <<
//        this->game->get_ball(19).get_x() << " " << this->game->get_ball(19).get_y() << " " <<
//        this->game->get_ball(20).get_x() << " " << this->game->get_ball(20).get_y() << " " <<
//        this->game->get_ball(21).get_x() << " " << this->game->get_ball(21).get_y();
