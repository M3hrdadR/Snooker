//
// Created by mehrdad on 7/13/18.
//
#include "../Headers/Table.h"

Table::Table() {
    Holes = new float*[6];
    for(int i = 0; i < 6;i++){
        Holes[i] = new float[2];
    }
    Holes[0][0] = Holes[3][0] = table_x - hole_radius;
    Holes[1][0] = Holes[4][0] = length/2 + table_x - hole_radius;
    Holes[2][0] = Holes[5][0] = length + table_x - hole_radius;
    Holes[0][1] = Holes[1][1] = Holes[2][1] = table_y - hole_radius;
    Holes[3][1] = Holes[4][1] = Holes[5][1] = width + table_y - hole_radius;
}

int Table::get_length() {
    return length;
}

int Table::get_width() {
    return width;
}

int Table::get_t_y() {
    return table_y;
}

int Table::get_t_x() {
    return table_x;
}

int Table::get_hole_r() {
    return hole_radius;
}

float **Table::get_Holes() {
    return Holes;
}

int Table::get_line_length() {
    return line_length;
}

int Table::get_line_thickness() {
    return line_thickness;
}

int Table::get_target_ball_x() {
    return target_ball_x;
}

int Table::get_target_ball_y() {
    return target_ball_y;
}

int Table::get_target_ball_radius() {
    return target_ball_radius;
}

float Table::get_line_table_x() {
    return line_table_x;
}

float Table::get_line_table_y() {
    return line_table_y;
}

float Table::get_line_table_length() {
    return line_table_length;
}

float Table::get_line_table_thickness() {
    return line_table_thickness;
}

float Table::get_circle_of_dots_r() {
    return circle_of_dots_r;
}

float Table::get_circle_of_dots_x() {
    return circle_of_dots_x;
}

float Table::get_circle_of_dots_y() {
    return circle_of_dots_y;
}

//sf::RectangleShape rectangle(sf::Vector2f(length,width));
//rectangle.setPosition(table_x,table_y);
//rectangle.setFillColor(sf::Color::Green);
////    rectangle.setOutlineThickness(outline_thickness);
////    rectangle.setOutlineColor(sf::Color(143,15,18));
//sf::CircleShape circle(hole_radius);
//for(int i = 0; i < 6;i++){
//circle.setPosition(Holes[i][0], Holes[i][1]);
//circle.setFillColor(sf::Color::Black);
//window.draw(circle);
//}
//window.draw(rectangle);