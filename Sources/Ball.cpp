//
// Created by mehrdad on 7/13/18.
//

#include <cmath>
#include <iostream>
#include "../Headers/Ball.h"
using std::cout;
using std::endl;

float Ball::get_x() {
    return x;
}

float Ball::get_y() {
    return y;
}

float Ball::get_radius() {
    return radius;
}

//float Ball::get_speed() {
//    return speed;
//}

void Ball::initial(float point_x, float point_y,  float speed) {
    angle = atan2f(center_y - point_y, center_x - point_x);
    speed_x = speed * cos(angle) * 2.5 ;
    speed_y = speed * sin(angle) * 2.5;
//    x += speed_x;
//    y += speed_y;
}

void Ball::hit(float speed_x, float speed_y, bool impact) {
    this->impact = impact;
    this->speed_x = speed_x ;
    this->speed_y = speed_y ;
    this->angle = atan2f(-speed_y , speed_x);
//    cout << speed_y << "  " << speed_x << endl;
//    cout << angle * 180 / M_PI << endl;
    x_count = 0;
    y_count = 0;
}



float sum(float speed,float friction){
    if(speed > 0)
        return speed - friction;
    else if(speed == 0)
        return 0;
    else
        return speed + friction;
}

void Ball::move() {
    if (x_count > fabsl(speed_x)) {
        speed_x = sum(speed_x, fabsf(friction * cosf(angle)));
        x_count = 0;
    }
    if (y_count > fabsl(speed_y)) {
        speed_y = sum(speed_y, fabsf(friction * sinf(angle)));
        y_count = 0;
    }

    if (fabsl(speed_x) < friction && fabsl(speed_y) < friction && !impact) {
        speed_x = 0;
        speed_y = 0;
    }
    else if(fabsl(speed_x) < friction && fabsl(speed_y) < friction && impact){
        x += speed_x * 5;
        y += speed_y * 5;
        impact = false;
    }
//    if (fabsl(speed_y) < 0.5)
//        speed_y = 0;
    if (speed_x != 0 && speed_y != 0) {
        x += 20 * fabsl(cosf(angle)) * sgn(speed_x);
        x_count += fabsl(10 * cosf(angle));
        y += 20 * fabsl(sinf(angle)) * sgn(speed_y);
        y_count += fabsl(  10 * sinf(angle));
        center_x = x + radius;
        center_y = y + radius;
    }
}

int Ball::sgn(float x) {
    if(x > 0)
        return 1;
    if(x < 0)
        return -1;
    if(x == 0)
        return 0;
}

void Ball::change_speed_x() {
    speed_x = - speed_x;
}

void Ball::change_speed_y() {
    speed_y = - speed_y;
}



float Ball::get_speed_x() {
    return speed_x;
}

float Ball::get_speed_y() {
    return speed_y;
}

sf::Color Ball::get_color() {
    return color;
}

Ball::Ball(sf::Color color, float x, float y, int score) {
    this->score = score;
    this->x = x;
    this->y = y;
    this->center_x = x + radius;
    this->center_y = y + radius;
    this->color = color;
}

float Ball::get_center_x() {
    return center_x;
}

float Ball::get_center_y() {
    return center_y;
}

void Ball::set_x(float x) {
    this->x = x;
    center_x = this->x + radius;
}

void Ball::set_y(float y) {
    this->y = y;
    center_y = this->y + radius;
}

int Ball::get_score() {
    return score;
}


void Ball::set_speed_x(float x) {
    speed_x = x;
    x_count = 0;
}

void Ball::set_speed_y(float x) {
    speed_y = x;
    y_count = 0;
}





//    if (speed_x != 0) {
//        x += 1 * cos(angle);
//        x_count += fabsf(1 * cos(angle));
//    }
//    if(speed_y != 0) {
//        y += 1 * sin(angle);
//        y_count += fabsf(1 * sin(angle));
//    }




