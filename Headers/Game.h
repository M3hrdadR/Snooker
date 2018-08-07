//
// Created by mehrdad on 7/13/18.
//
#include "../Headers/Table.h"
#include "Ball.h"

#ifndef BILIARD_GAME_H
#define BILIARD_GAME_H
class Game{
public:
    Game();
    bool In_hole(float ball_x, float ball_y);
    void set_turn(int x);
    void set_my_score(int x);
    void set_enemy_score(int x);
    int get_turn();
    int get_my_score();
    int get_enemy_score();
    void move();
    void put_colorful_ball(int i);
    void hit_initial(int mouse_x, int mouse_y, int power);
    void calculate_line_angle(int x,int y);
    bool check_hit(Ball ** ball_1, Ball  ** ball_2);
    bool In_circle(float x, float y, float x_2, float y_2, float r);
    double get_angle();
    Table & get_table();
    Ball & get_ball(int x);
private:
    bool Red_in_hole = false;
    bool start_shoot = false;
    bool impact_white = false;
    int my_score = 0;
    int enemy_score = 0;
    int turn;
    const float ball_radius = 11;
    double angle = 0;
    Table table;

    float x_blue = table.get_t_x() + table.get_length() / 2 - ball_radius;
    float y_blue = table.get_t_y() + table.get_width() / 2 - ball_radius;
    float x_black = table.get_t_x() + table.get_length() - 129.6 - ball_radius;
    float y_black = y_blue;
    float x_pink = (x_blue + x_black) / 2;
    float y_pink = y_black;
    float x_red1 = x_pink + 2 * ball_radius;
    float y_red1 = y_pink;

    float **coordinates = new float *[7];
    sf::Color * colors = new sf::Color [7];
    int * scores = new int[7];
    Ball  * balls[22];

};
#endif //BILIARD_GAME_H
