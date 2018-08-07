//
// Created by mehrdad on 7/13/18.
//

#ifndef BILIARD_BALL_H
#define BILIARD_BALL_H

#include <SFML/Graphics/Color.hpp>

class Ball {
public:
    Ball(sf::Color color, float x, float y, int score);
    float x_count = 0;
    float y_count = 0;
    void move() ;
    void hit(float speed_x, float speed_y, bool hit);
    void initial(float point_x, float point_y,  float speed);
    void set_x(float x);
    void set_y(float y);
    void set_speed_x(float x);
    void set_speed_y(float x);
    int get_score();
    void change_speed_x();
    void change_speed_y();
    int sgn(float x);
    float get_x();
    float get_y();
    float get_radius();
    float get_speed_x();
    float get_speed_y();
    float get_center_x();
    float get_center_y();
    sf::Color get_color();

private:
    bool impact = false;
    int score;
    float x;
    float y;
    const float radius = 11;
    float center_x;
    float center_y;
    float speed_x = 0;
    float speed_y = 0;
    float angle = 0;
    const float friction = 0.5;
    sf::Color color;
};
#endif //BILIARD_BALL_H
