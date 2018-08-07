//
// Created by mehrdad on 7/21/18.
//

#include <SFML/Graphics.hpp>
#include "../Headers/Button.h"

//Button::Button(int x, int y, int length, int width, sf::Color color) {
//    this->x = x;
//    this->y = y;
//    this->length = length;
//    this->width = width;
//    this->color = color;
//}

void Button::set_string(std::string string) {
    this->string = string;
}

void Button::rendering(sf::RenderWindow *window) {
    sf::Font font;
    if (!font.loadFromFile("/home/mehrdad/.themes/FONT/San Francisco.ttf")){
        std::cout << "ERR " << std::endl;
    }
    sf::RectangleShape rectangle(sf::Vector2f(length, width));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);
    text.setString(string);
    window->draw(rectangle);
    window->draw(text);
}

bool Button::In_button(int mouse_x, int mouse_y) {
    if(mouse_x >= x && mouse_x <= x + length && mouse_y >= y && mouse_y <= y + width)
        return true;
    return false;
}

void Button::set_x(int x) {
    this->x = x;
}

void Button::set_y(int y) {
    this->y = y;
}

void Button::set_length(int length) {
    this->length = length;

}

void Button::set_width(int width) {
    this->width = width;
}

void Button::set_color(sf::Color color) {
    this->color = color;
}

std::string Button::get_string() {
    return string;
}
