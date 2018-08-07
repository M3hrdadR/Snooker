//
// Created by mehrdad on 7/23/18.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../Headers/renderer.h"
#include "../Headers/Start.h"



#include <cstring>
#include <cmath>
#include <thread>


using std::cout;
using std::endl;

bool In_target_ball(int x, int y, Game *game) {
    if(pow(x - game->get_table().get_target_ball_x() - game->get_table().get_target_ball_radius(), 2) +
       pow(y - game->get_table().get_target_ball_y() - game->get_table().get_target_ball_radius(), 2)
       <= pow(game->get_table().get_target_ball_radius(),2)){
        return true;
    }
    else
        return false;
}

bool In_table(int x, int y, Game *game) {
    if(x >= game->get_table().get_t_x() && x <= game->get_table().get_t_x() + game->get_table().get_length()
       && y >= game->get_table().get_t_y() && y <= game->get_table().get_t_y() + game->get_table().get_width()) {
        return true;
    }
    else
        return false;
}

void start_game(std::string ip, bool is_server) {
    float mouse_x, mouse_y, mouse_x2, mouse_y2, target_x, target_y;
    float power = 0;
//    bool turn_send = false;
    bool target_ball = false;
    bool my_move;
    bool end = false;
    bool text_entered = false;
    bool mouse_button = false;
    bool mouse_move = false;
    Game game;
    sf::Font font;
    if (!font.loadFromFile("/home/mehrdad/.themes/FONT/San Francisco.ttf")) {
        std::cout << "ERR " << std::endl;
    }
//    game.set_turn(1);
//    int a;
//    std::cin>> a;
    Resource* resource = new Resource(&game);
    Network* network;
    if (is_server){
        network = new Network(resource);
        network->listen();
        game.set_turn(1);
    }
    else {
        network = new Network(resource, ip);
        network->connect();
        game.set_turn(-1);
    }
    sf::RenderWindow window(sf::VideoMode(1650, 900), "Biliard");

    while (window.isOpen()) {
        my_move = false;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                mouse_x = event.mouseMove.x;
                mouse_y = event.mouseMove.y;
                game.calculate_line_angle(event.mouseMove.x, event.mouseMove.y);
                mouse_move = true;
            } else {
                mouse_move = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (In_target_ball(mouse_x, mouse_y, &game)) {
                        target_ball = true;
                    }
                    if (In_table(mouse_x, mouse_y, &game) && target_ball) {
                        mouse_x2 = mouse_x;
                        mouse_y2 = mouse_y;
                        mouse_button = true;
                        target_ball = false;
                    }

                } else {
                    mouse_button = false;
                }
            }
            if (event.type == sf::Event::TextEntered && mouse_button && game.get_turn() == 1) {
                if (event.text.unicode < 128) {
                    power = event.text.unicode - 48;
                    text_entered = true;
                    mouse_button = false;
                    game.hit_initial(mouse_x2, mouse_y2, power);
                }
            } else {
                text_entered = false;
            }
        }
        for (int i = 0; i < 22; i++) {
            if (game.get_ball(i).get_speed_x() != 0 && game.get_ball(i).get_speed_y() != 0) {
                my_move = true;
                break;
            }
        }
        game.move();

//        if (my_move)
//            turn_send = true;
//        if ( turn_send && game.get_turn() == -1){
//            for (int i = 0; i < 50; i++){
//                network->send();
//            }
//            turn_send = false;
//        }
        if (my_move){
            network->send();
        }

        if(!my_move) {
            network->receive();
        }
        for (int i = 0; i < 22;i++){
            if(game.get_ball(i).get_x() != 0 && game.get_ball(i).get_y() != 0){
                end = false;
                break;
            }
            end = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        window.clear(sf::Color::White);
        render(window, &game, mouse_move, mouse_button,text_entered, end);
        window.display();
        if (end){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            window.close();
        }
//        sf::sleep(sf::microseconds(500));
    }

}

