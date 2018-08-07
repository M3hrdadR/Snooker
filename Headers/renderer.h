//
// Created by mehrdad on 7/13/18.
//

#ifndef BILIARD_RENDERER_H
#define BILIARD_RENDERER_H

//#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cmath>

void render(sf::RenderWindow & window,Game * game,bool moise_move,bool & mouse_button, bool text_entered, bool end){
    sf::Font font;
    if (!font.loadFromFile("/home/mehrdad/.themes/FONT/San Francisco.ttf")){
        std::cout << "ERR " << std::endl;
    }
    sf::Text text1;
    text1.setFont(font);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(800,450);
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(800,450);
    sf::RectangleShape table(sf::Vector2f(game->get_table().get_length(), game->get_table().get_width()));
    sf::RectangleShape line(sf::Vector2f(game->get_table().get_line_length(), game->get_table().get_line_thickness()));
    sf::RectangleShape line_table(sf::Vector2f(game->get_table().get_line_table_length(), game->get_table().get_line_table_thickness()));


    line_table.setPosition((sf::Vector2f(game->get_table().get_line_table_x(), game->get_table().get_line_table_y())));
    line_table.setFillColor(sf::Color::White);
    line_table.setRotation(90);

    line.setPosition(game->get_ball(0).get_x() + game->get_ball(0).get_radius(), game->get_ball(0).get_y() + game->get_ball(0).get_radius());
    line.setFillColor(sf::Color::Black);
    line.setRotation(180 + game->get_angle());

    table.setPosition(game->get_table().get_t_x(), game->get_table().get_t_y());
    table.setFillColor(sf::Color::Green);
    //    rectangle.setOutlineThickness(outline_thickness);
    //    rectangle.setOutlineColor(sf::Color(143,15,18));

    sf::CircleShape target_ball(game->get_table().get_target_ball_radius());
    sf::CircleShape hole(game->get_table().get_hole_r());
    sf::CircleShape ball(game->get_ball(0).get_radius());
    sf::CircleShape dot(1);



    target_ball.setPosition(game->get_table().get_target_ball_x(), game->get_table().get_target_ball_y());
    target_ball.setFillColor(sf::Color(93, 195, 226));

    for(int i = 0; i < 6;i++){
    hole.setPosition(game->get_table().get_Holes()[i][0], game->get_table().get_Holes()[i][1]);
    hole.setFillColor(sf::Color::Black);
        window.draw(hole);
    }


    window.draw(table);
    window.draw(target_ball);
    window.draw(line_table);


    dot.setFillColor(sf::Color::White);
    float y = game->get_table().get_circle_of_dots_y() - game->get_table().get_circle_of_dots_r();
    float x = game->get_table().get_circle_of_dots_x();
    float c = game->get_table().get_circle_of_dots_r() ;
    float tmp = 0;
    dot.setPosition(x,y);
    window.draw(dot);
    while(y <= game->get_table().get_circle_of_dots_y() + game->get_table().get_circle_of_dots_r()){
        c -= 0.1;
        y += 0.1;
        tmp = static_cast<float>(sqrt(pow(game->get_table().get_circle_of_dots_r(), 2) - pow(c, 2)));
        dot.setPosition(x - tmp,y);
        window.draw(dot);
    }
    for (int i = 0; i < 22; i++) {
        ball.setPosition(game->get_ball(i).get_x(),game->get_ball(i).get_y());
        ball.setFillColor(game->get_ball(i).get_color());
        window.draw(ball);
    }
    if (end){
        if (game->get_my_score() > game->get_enemy_score()) {
            text.setString("You Are Winner!");
        }
        else {
            text.setString("You Are A Looser!");
        }
        window.draw(text);
    }
    if(moise_move)
        window.draw(line);
    if(mouse_button){
        text.setString("Enter the power :(0 - 9)");
        window.draw(text);
    }
    if(text_entered) {
        text.setString("Power Entered !");
        window.draw(text);
        window.display();
        sf::sleep(sf::milliseconds(300));
    }

}
#endif //BILIARD_RENDERER_H
