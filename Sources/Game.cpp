//
// Created by mehrdad on 7/13/18.
//
#include <cmath>
#include <math.h>
#include <iostream>
#include "../Headers/Game.h"


using std::cout;
using std::endl;

int max(int x, int y){
    if(x >= y)
        return x;
    else
        return y;
}
Game::Game() {
    for (int i = 0;i < 7; i++){
        coordinates[i] = new float[2];
        if (i == 1){
            coordinates[i][0] = table.get_line_table_x() - ball_radius;
            coordinates[i][1] = table.get_circle_of_dots_y() + table.get_circle_of_dots_r() - ball_radius;
            colors[i] = sf::Color(247,255,10);
            scores[i] = 2;
        }
        else if (i == 2){
            coordinates[i][0] = table.get_line_table_x() - ball_radius;;
            coordinates[i][1] = table.get_circle_of_dots_y() - ball_radius;
            colors[i] = sf::Color(159,88,0);
            scores[i] = 3;
        }
        else if (i == 3){
            coordinates[i][0] = table.get_line_table_x() - ball_radius;
            coordinates[i][1] = table.get_circle_of_dots_y() - table.get_circle_of_dots_r() - ball_radius;
            colors[i] = sf::Color(0,115,6);
            scores[i] = 4;
        }
        else if (i == 4){
            coordinates[i][0] = table.get_t_x() + table.get_length() / 2 - ball_radius;
            coordinates[i][1] = table.get_t_y() + table.get_width() / 2 - ball_radius;
            colors[i] = sf::Color::Blue;
            scores[i] = 5;
        }
        else if(i == 5){
            coordinates[i][0] = (x_blue + x_black) / 2;
            coordinates[i][1] = y_blue;
            colors[i] = sf::Color(253,8,195);
            scores[i] = 6;
        }
        else if(i == 6){
            coordinates[i][0] = static_cast<float > (table.get_t_x() + table.get_length() - 129.6 - ball_radius);
            coordinates[i][1] = y_blue;
            colors[i] = sf::Color::Black;
            scores[i] = 7;
        }
        else if (i == 0){
            coordinates[i][0] = 240;
            coordinates[i][1] = 340;
            colors[i] = sf::Color::White;
            scores[i] = 0;
        }
    }
    for (int i = 0;i < 7; ++i){
        balls[i] = new Ball(colors[i], coordinates[i][0], coordinates[i][1], scores[i]);
    }
//    balls[0] = new Ball(sf::Color::White,240,340,0);
//    balls[1] = new Ball(sf::Color(247,255,10), coordinates[1][0], coordinates[1][1], 2);
//    balls[2] = new Ball(sf::Color(159,88,0), x_brown, y_brown, 3);
//    balls[3] = new Ball(sf::Color(0,115,6), x_green, y_green, 4);
//    balls[4] = new Ball(sf::Color::Blue, x_blue, y_blue, 5);
//    balls[5] = new Ball(sf::Color(253,8,195), x_pink, y_pink, 6);
//    balls[6] = new Ball(sf::Color::Black, x_black, y_black, 7);
//    balls[5] = new Ball(sf::Color::Black, x_black, y_black, 7);
//    balls[6] = new Ball(sf::Color(253,8,195), x_pink, y_pink, 6);
    balls[7] = new Ball(sf::Color::Red, x_red1, y_red1, 1);
    balls[8] = new Ball(sf::Color::Red, x_red1 + 2 * ball_radius, y_red1 - ball_radius, 1);
    balls[9] = new Ball(sf::Color::Red, x_red1 + 2 * ball_radius, y_red1 + ball_radius, 1);
    balls[10] = new Ball(sf::Color::Red, x_red1 + 4 * ball_radius, y_red1 - 2 * ball_radius, 1);
    balls[11] = new Ball(sf::Color::Red, x_red1 + 4 * ball_radius, y_red1 - 0 * ball_radius, 1);
    balls[12] = new Ball(sf::Color::Red, x_red1 + 4 * ball_radius, y_red1 + 2 * ball_radius, 1);
    balls[13] = new Ball(sf::Color::Red, x_red1 + 6 * ball_radius, y_red1 - 3 * ball_radius, 1);
    balls[14] = new Ball(sf::Color::Red, x_red1 + 6 * ball_radius, y_red1 - 1 * ball_radius, 1);
    balls[15] = new Ball(sf::Color::Red, x_red1 + 6 * ball_radius, y_red1 + 1 * ball_radius, 1);
    balls[16] = new Ball(sf::Color::Red, x_red1 + 6 * ball_radius, y_red1 + 3 * ball_radius, 1);
    balls[17] = new Ball(sf::Color::Red, x_red1 + 8 * ball_radius, y_red1 - 4 * ball_radius, 1);
    balls[18] = new Ball(sf::Color::Red, x_red1 + 8 * ball_radius, y_red1 - 2 * ball_radius, 1);
    balls[19] = new Ball(sf::Color::Red, x_red1 + 8 * ball_radius, y_red1 - 0 * ball_radius, 1);
    balls[20] = new Ball(sf::Color::Red, x_red1 + 8 * ball_radius, y_red1 + 2 * ball_radius, 1);
    balls[21] = new Ball(sf::Color::Red, x_red1 + 8 * ball_radius, y_red1 + 4 * ball_radius, 1);

}

bool Game::In_circle(float x, float y, float x_2, float y_2, float r) {
    if(pow(x - x_2, 2) + pow(y - y_2, 2) < pow(r, 2)){
        return true;
    }
    else
        return false;
}

void Game::calculate_line_angle(int x, int y) {
    angle = (atan2f(y - balls[0]->get_y(),x - balls[0]->get_x())) *180 / M_PI;
}

void Game::hit_initial(int mouse_x, int mouse_y, int power) {
    start_shoot = true;
    impact_white = false;
    balls[0]->initial(mouse_x, mouse_y, power);
}

bool  Game::check_hit(Ball ** ball_1, Ball  ** ball_2){
    if ((*ball_1)->get_x() != 0 && (*ball_1)->get_y() != 0) {
        if (In_circle(((*ball_1)->get_center_x() + (*ball_2)->get_center_x()) / 2,
                      ((*ball_1)->get_center_y() + (*ball_2)->get_center_y()) / 2,
                      (*ball_1)->get_center_x(), (*ball_1)->get_center_y(), (*ball_1)->get_radius())
            && (*ball_1)->get_speed_x() == 0 && (*ball_1)->get_speed_y() == 0 && (*ball_2)->get_speed_x() == 0 &&
            (*ball_2)->get_speed_y() == 0) {
            (*ball_1)->set_speed_x(2);
            (*ball_1)->set_speed_y(2);
        } else if (In_circle(((*ball_1)->get_center_x() + (*ball_2)->get_center_x()) / 2,
                             ((*ball_1)->get_center_y() + (*ball_2)->get_center_y()) / 2,
                             (*ball_1)->get_center_x(), (*ball_1)->get_center_y(), (*ball_1)->get_radius())) {
//            if((*ball_1)->get_color() == sf::Color::White && (*ball_2)->get_color())
            float v1_x = (*ball_1)->get_speed_x();
            float v1_y = (*ball_1)->get_speed_y();

            float v2_x = (*ball_2)->get_speed_x();
            float v2_y = (*ball_2)->get_speed_y();

            float r1_x = (*ball_1)->get_center_x();
            float r1_y = (*ball_1)->get_center_y();

            float r2_x = (*ball_2)->get_center_x();
            float r2_y = (*ball_2)->get_center_y();
            float delta_x = r1_x - r2_x;
            float r = (float) sqrt(pow(r1_x - r2_x, 2) + pow(r1_y - r2_y, 2));

            float speed1_x = v1_x - ((v1_x - v2_x) * (r1_x - r2_x)) / (r * r) * (r1_x - r2_x);
            float speed1_y = v1_y - ((v1_x - v2_x) * (r1_x - r2_x)) / (r * r) * (r1_y - r2_y);
            float speed2_x = v2_x - ((v2_x - v1_x) * (r2_x - r1_x)) / (r * r) * (r2_x - r1_x);
            float speed2_y = v2_y - ((v2_x - v1_x) * (r2_x - r1_x)) / (r * r) * (r2_y - r1_y);
            if (v1_x > 0 && v1_y > 0) {
                if (delta_x >= 0) {
                    speed2_x = -speed2_x;
                    speed2_y = -speed2_y;
                }
            } else if (v1_x < 0 && v1_y > 0) {
                if (delta_x < 0) {
                    speed2_y = -speed2_y;
                    speed2_x = -speed2_x;
                }
            } else if (v1_x > 0 && v1_y < 0) {
                if (delta_x > 0) {
                    speed2_x = -speed2_x;
                    speed2_y = -speed2_y;
                }
            } else if (v1_x < 0 && v1_y < 0) {
                if (delta_x < 0) {
                    speed2_y = -speed2_y;
                    speed2_x = -speed2_x;
                }
            }
            (*ball_2)->hit(speed2_x, speed2_y, true);
            (*ball_1)->hit(speed1_x, speed1_y, true);
        }
    }
}

bool Game::In_hole(float ball_x, float ball_y) {
    float ** holes = table.get_Holes();
    float radius = table.get_hole_r();
    for(int i = 0; i < 6; i++){
        if (In_circle(ball_x, ball_y, holes[i][0], holes[i][1], radius)){
            return true;
        }
    }
    return false;
}

void Game::put_colorful_ball(int i) {
    balls[i]->set_x(coordinates[i][0]);
    balls[i]->set_y(coordinates[i][1]);
    balls[i]->set_speed_x(0);
    balls[i]->set_speed_y(0);
    for (int j = 0; j < 22; j++) {
        if (i != j) {
            if (sqrt(pow(balls[i]->get_center_x() - balls[j]->get_center_x(), 2) +
                     pow(balls[i]->get_center_y() - balls[j]->get_center_y(), 2) <
                     2 * balls[i]->get_radius())) {
                for (int k = 6; k >= 1; k--) {
                    balls[i]->set_x(coordinates[k][0]);
                    balls[i]->set_y(coordinates[k][1]);
                    for (int l = 0; l < 22; l++) {
                        if (i != l) {
                            if (sqrt(pow(balls[i]->get_center_x() - balls[l]->get_center_x(), 2) +
                                     pow(balls[i]->get_center_y() - balls[l]->get_center_y(), 2)
                                     >= 2 * balls[i]->get_radius())) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


void Game::move() {
    bool hit = false;
    bool Is_any_red = true;
    for (int i = 0; i < 22; i++) {
        for (int j = i + 1; j < 22; j++) {
            hit = check_hit(&balls[i], &balls[j]);
            if (i == 0) {
                if (hit && start_shoot) {
                    if (j >= 1 && j <= 6 && !Red_in_hole) {
                        impact_white = true;
                        start_shoot = false;
                        my_score -= max(4, balls[j]->get_score());
                        turn = -1;
                    }
//                    else{
//                        impact_white = true;
//                        start_shoot = false;
//                        turn = 1;
//                    }
                }
            }
        }
        if (i == 0 && !impact_white && start_shoot && balls[0]->get_speed_x() == 0 && balls[0]->get_speed_y() == 0){
            start_shoot = false;
            my_score -= 4;
            turn = -1;
        }
    }
    for (int i = 0; i < 22; i++) {
        if (balls[i]->get_center_x() <= table.get_t_x() ||
            balls[i]->get_center_x() >= table.get_t_x() + table.get_length())
            balls[i]->change_speed_x();
        else if (balls[i]->get_center_y() <= table.get_t_y() ||
                 balls[i]->get_center_y() >= table.get_t_y() + table.get_width())
            balls[i]->change_speed_y();
        if ( turn == 1){
            if (In_hole(balls[i]->get_x(), balls[i]->get_y())) {
                if (balls[i]->get_color() == sf::Color::Red) {
                    my_score += balls[i]->get_score();
                    balls[i]->set_x(0);
                    balls[i]->set_y(0);
                    balls[i]->set_speed_x(0);
                    balls[i]->set_speed_y(0);
                    Red_in_hole = true;
                } else if (balls[i]->get_color() != sf::Color::White) {
                    for (int j = 7; j < 22; j++) {
                        if (balls[j]->get_x() != 0 && balls[j]->get_y() != 0) {
                            Is_any_red = true;
                            break;
                        }
                        Is_any_red = false;
                    }

                    if (Is_any_red && Red_in_hole) {
                        my_score += balls[i]->get_score();
                        turn = 1;
                        Red_in_hole = false;
                        put_colorful_ball(i);
                    } else if (Is_any_red && !Red_in_hole) {
                        Red_in_hole = false;
                        my_score -= max(4, balls[i]->get_score());
                        turn = -1;
                        put_colorful_ball(i);

                    } else if (!Is_any_red && Red_in_hole) {
                        my_score += balls[i]->get_score();
                        turn = 1;
                        Red_in_hole = false;
                        put_colorful_ball(i);
                    } else if (!Is_any_red) {
                        for (int j = i - 1; j >= 1; j--) {
                            if (balls[i]->get_x() != 0 && balls[i]->get_y() != 0) {
                                my_score -= max(4, balls[i]->get_score());
                                turn = -1;
                                put_colorful_ball(i);
                            }
                        }
                        if (turn == 1) {
                            my_score += balls[i]->get_score();
                            turn = 1;
                            balls[i]->set_x(0);
                            balls[i]->set_y(0);
                            balls[i]->set_speed_x(0);
                            balls[i]->set_speed_y(0);

                        }
                    }
                } else if (balls[i]->get_color() == sf::Color::White) {
                    my_score -= 4;
                    turn = -1;
                    balls[i]->set_x(coordinates[0][0]);
                    balls[i]->set_y(coordinates[0][1]);
                    balls[i]->set_speed_x(0);
                    balls[i]->set_speed_y(0);
                }
            }
        }
        balls[i]->move();

    }
}

void Game::set_turn(int x) {
    turn = x;
}

int Game::get_turn() {
    return turn;
}

void Game::set_my_score(int x) {
    my_score = x;
}

void Game::set_enemy_score(int x) {
    enemy_score = x;
}

int Game::get_my_score() {
    return my_score;
}

int Game::get_enemy_score() {
    return enemy_score;
}


double Game::get_angle() {
    return angle;
}

Table & Game::get_table() {
    return table;
}

Ball & Game::get_ball(int x) {
    return  *balls[x];
}







//        float r1 , r2, t1, t2;
//        float r_x1 = sqrt(pow((*ball_1)->get_center_x(),2) + pow((*ball_1)->get_center_y(),2));
//        float r_x2 = sqrt(pow((*ball_2)->get_center_x(),2));
//        float r_v1 = sqrt(pow((*ball_1)->get_speed_x(),2) + pow((*ball_1)->get_speed_y(),2));
//        float r_v2 = sqrt(pow((*ball_2)->get_speed_x(),2) + pow((*ball_2)->get_speed_y(),2));
//        float t_v1 = atan2f((*ball_1)->get_speed_y(), (*ball_1)->get_speed_x());
//        float t_v2 = atan2f((*ball_2)->get_speed_y(), (*ball_2)->get_speed_x());
//        float t_x1 = atan2f((*ball_1)->get_center_y(), (*ball_1)->get_center_x());
//        float t_x2 = atan2f(0, (*ball_2)->get_center_x());
//        float num1 = ( ( (*ball_1)->get_speed_x() - (*ball_2)->get_speed_x() ) * ( (*ball_1)->get_x() - (*ball_2)->get_x() ) )
//                    / pow( (*ball_1)->get_x(), 2) + pow( (*ball_2)->get_x() , 2);
//        float num2 = ( ( (*ball_2)->get_speed_x() - (*ball_1)->get_speed_x() ) * ( (*ball_2)->get_x() - (*ball_1)->get_x() ) )
//                     / pow( (*ball_1)->get_x(), 2) + pow( (*ball_2)->get_x() , 2);
//        float tmp1_t = t_x1 + atan2f(r_x2*sin(t_x2 - t_x1), r_x1 - r_x2 * cos(t_x2 - t_x1));
//        float tmp2_t = t_x2 + atan2f(r_x1*sin(t_x1 - t_x2), r_x2 - r_x1 * cos(t_x1 - t_x2));
//        float tmp1_r = sqrt(r_x1*r_x1 + r_x2*r_x2 - 2*r_x1*r_x2*cos(t_x2 - t_x1));
//        float tmp2_r = sqrt(r_x1*r_x1 + r_x2*r_x2 - 2*r_x1*r_x2*cos(t_x1 - t_x2));
//        r1 = sqrt(r_v1 * r_v1 + num1 * num1 * tmp1_r * tmp1_r - 2 * num1 * r_v1 * tmp1_r * cos(tmp1_t - t_v1));
//        r2 = sqrt(r_v2 * r_v2 + num2 * num2 * tmp2_r * tmp2_r - 2 * num2 * r_v2 * tmp2_r * cos(tmp2_t - t_v2));
//        t1 = t_v1 + atan2f(num1 * tmp1_r * sin(tmp1_t - t_v1), r_v1 - num1 * tmp1_r * cos(tmp1_t - t_v1));
//        t2 = t_v2 + atan2f(num2 * tmp2_r * sin(tmp2_t - t_v2), r_v2 - num2 * tmp2_r * cos(tmp2_t - t_v2));
//        cout << r2 * cos(t2) << " " << r2 * sin(t2) << endl;
//        (*ball_2)->initial(t2, r2);

//        (*ball_2)->hit( (M_PI -
//                (M_PI/2 + atan2f( ( (*ball_2)->get_center_y() - (*ball_1)->get_center_y() + (*ball_2)->get_center_y() ) / 2 ,
//                        (*ball_2)->get_center_x() - ( (*ball_1)->get_center_x() + (*ball_2)->get_center_x() ) / 2) ) ) / 2
//                , 1 );
//        angle = atan2f(center_y - point_y, center_x - point_x);

//        (*ball_2)->initial( ( (*ball_1)->get_center_x() + (*ball_2)->get_center_x() ) / 2 ,
//                            ( (*ball_1)->get_center_y() + (*ball_2)->get_center_y() ) / 2 , 1);