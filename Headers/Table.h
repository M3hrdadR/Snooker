//
// Created by mehrdad on 7/13/18.
//
#include <SFML/Graphics.hpp>

#ifndef BILIARD_TABLE_H
#define BILIARD_TABLE_H
class Table{
public:
    Table();
    int get_length();
    int get_width();
    int get_t_y();
    int get_t_x();
    int get_hole_r();
    int get_line_length();
    int get_line_thickness();
    int get_target_ball_x();
    int get_target_ball_y();
    int get_target_ball_radius();
    float ** get_Holes();
    float get_line_table_x();
    float get_line_table_y();
    float get_line_table_length();
    float get_line_table_thickness();
    float get_circle_of_dots_r();
    float get_circle_of_dots_x();
    float get_circle_of_dots_y();


private:
    int width = 708;
    int length = 1424;
    int table_y = 46;
    int table_x = 43;
    int hole_radius = 16;
    int outline_thickness = 50;
    int line_length = 200;
    int line_thickness = 2;
    int target_ball_x = 1500;
    int target_ball_y = 750;
    int target_ball_radius = 75;
    float **Holes;
    float line_table_x = 294.8;
    float line_table_y = 46;
    float line_table_length = 708;
    float line_table_thickness = 2;
    float circle_of_dots_r = 116;
    float circle_of_dots_x = line_table_x;
    float circle_of_dots_y = line_table_y + line_table_length/2;
};

#endif //BILIARD_TABLE_H