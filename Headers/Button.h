//
// Created by mehrdad on 7/21/18.
//

#ifndef BILIARD_BUTTON_H
#define BILIARD_BUTTON_H

#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button{
public:
//    Button(int x, int y, int length, int width, sf::Color color);
    void set_string(std::string);
    void rendering(sf::RenderWindow * window);
    bool In_button(int mouse_x, int mouse_y);
    void set_x(int x);
    void set_y(int y);
    void set_length(int length);
    void set_width(int width);
    void set_color(sf::Color color);
    std::string get_string();

private:
    int x;
    int y;
    int width;
    int length;
    sf::Color color;
    std::string string;
};
#endif //BILIARD_BUTTON_H
