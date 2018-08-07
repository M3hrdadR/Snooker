#include <SFML/Network.hpp>
#include <iostream>
#include <thread>


#include <thread>
#include <cstring>
#include "Headers/Button.h"
#include "Headers/Start.h"
#include <cmath>
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;



bool Check(sf::IpAddress * servers, sf::IpAddress ip, int num){
    for (int i = 0; i < num; i++){
        if(ip == servers[i])
            return false;
    }
    return true;
}
//
bool in_box(int mouse_x, int mouse_y, int box_x, int box_y, int length, int width){
    if(mouse_x >= box_x && mouse_x <= box_x + length && mouse_y >= box_y && mouse_y <= box_y + width)
        return true;
    return false;
}
void render1(sf::RenderWindow * window, Button * buttons, int number_buttons) {
    for (int i = 0; i < number_buttons; i++){
        buttons[i].rendering(window);
    }
}


void Show_menu(std::string & server_ip, bool & is_server) {
    int number_buttons = 0;
    int number_servers = 0;
    short answer = 5;
    bool level_2 = false;
    bool level_3 = false;
    bool connected = false;
    bool Is_server = false;
    bool Is_client = false;

    int count = 0;

    std::string Chosen_client_ip = "";
    std::string Chosen_server_ip = "";

    sf::IpAddress *servers_ip = new sf::IpAddress[20];
    std::string ip;
    sf::UdpSocket socket1;
    sf::UdpSocket socket2;
    sf::UdpSocket socket3;


    socket1.setBlocking(false);
    socket2.setBlocking(false);
    socket3.setBlocking(false);

    unsigned short port1 = 12345;
    unsigned short port2 = 53000;
    unsigned short port3 = 54000;

    int mouse_x = 0;
    int mouse_y = 0;
    int window_length = 800;
    int window_width = 600;
    int button_x = 325;
    sf::Color button_color = sf::Color::Green;
    int button_length = 200;
    int button_width = 50;
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "Biliard");

    while (window.isOpen()) {
        if (Is_server && level_3)
            number_buttons = 3;
        else if (Is_client && level_3)
            number_buttons = 0;
        else if (Is_server && level_2)
            number_buttons = 0;
        else if (Is_client && level_2)
            number_buttons = 0;
        else if (Is_server)
            number_buttons = 0;
        else if (Is_client)
            number_buttons = number_servers;
        else if (!Is_client && !Is_server)
            number_buttons = 2;
        Button *buttons = new Button[number_buttons];
        for (int i = 0; i < number_buttons; i++) {
            buttons[i].set_x(button_x);
            buttons[i].set_y((window_width / (number_buttons + 1)) * (i + 1));
            buttons[i].set_length(button_length);
            buttons[i].set_width(button_width);
            buttons[i].set_color(button_color);
            if (Is_server && level_3) {
                if (i == 0)
                    buttons[i].set_string(Chosen_client_ip);
                else if (i == 1)
                    buttons[i].set_string("Yes");
                else if (i == 2)
                    buttons[i].set_string("No");
            } else if (!Is_client && !Is_server) {
                if (i == 0)
                    buttons[i].set_string("Server");
                else if (i == 1)
                    buttons[i].set_string("Client");
            } else {
                buttons[i].set_string(servers_ip[i].toString());
            }
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                mouse_x = event.mouseMove.x;
                mouse_y = event.mouseMove.y;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!Is_client && !Is_server) {
                        if (buttons[0].In_button(mouse_x, mouse_y)) {
                            Is_server = true;
                            level_2 = true;
                        } else if (buttons[1].In_button(mouse_x, mouse_y)) {
                            Is_client = true;
                        }
                    }
                    else if (Is_client && !level_2) {
                        for (int i = 0; i < number_servers; ++i) {
                            if (buttons[i].In_button(mouse_x, mouse_y)) {
                                level_2 = true;
                                Chosen_server_ip = buttons[i].get_string();
                                number_buttons = 0;
                                number_servers = 0;
                                count = 0;
                            }
                        }
                    } else if (Is_server && level_3) {
                        if (buttons[1].In_button(mouse_x, mouse_y)) {
                            answer = 1;
                            number_buttons = 0;
                        } else if (buttons[2].In_button(mouse_x, mouse_y)) {
                            answer = 0;
                            number_buttons = 0;
                        }
                    }
                }
            }
        }
        if (Is_server && level_3) {
            if (answer == 1) {
                for (int i = 0; i < 1000; i++) {
                    char data[15] = "Yes";
                    ip = Chosen_client_ip;
                    if (socket3.send(data, 15, ip, port3) != sf::Socket::Done) {}
                }
                is_server = true;
                connected = true;
//                window.close();
                socket1.unbind();
                socket2.unbind();
                socket3.unbind();
//                    window.close();
//                start_game(server_ip, Is_server);
//                    break;
            } else if (answer == 0) {
                char data[15] = "No";
                ip = Chosen_client_ip;
                if (socket3.send(data, 15, ip, port3) != sf::Socket::Done) {
                    while (socket3.send(data, 15, ip, port3) != sf::Socket::Done){
                        socket3.send(data, 15, ip, port3);
                    }
                }
                level_3 = false;
                answer = 5;
            }
        } else if (Is_client && level_2) {
            char data[15] = "P";
            ip = Chosen_server_ip;
            if(count == 0) {
                if (socket2.send(data, 15, Chosen_server_ip, port2) != sf::Socket::Done) {
                cout << " error 4 " << endl;
                }
                else {
                    count += 1;
                }
            }
            socket3.bind(port3);
            std::size_t received;
            char data2[15];
            sf::IpAddress sender_ip;
            if (socket3.receive(data2, 15, received, sender_ip, port3) != sf::Socket::Done) {}
            else {
                for (int i = 0; i < 15; ++i) {
                    if (data2[i] == 'Y') {
                        server_ip = Chosen_server_ip;
                        is_server = false;
                        connected = true;
//                        window.close();
                    } else if (data2[i] == 'N') {
                        level_2 = false;

                        number_servers = 0;
                        number_buttons = 0;
                        break;
                    }
                }
            }
        } else if (Is_server && level_2) {
            char data[15] = "P";
            ip = sf::IpAddress::Broadcast.toString();
            if (socket1.send(data, 15, sf::IpAddress::Broadcast, port1) != sf::Socket::Done) {

            }
            socket2.bind(port2);
            std::size_t received;
            char data2[15];
            sf::IpAddress sender_ip;
            if (socket2.receive(data2, 15, received, sender_ip, port2) != sf::Socket::Done) {
//                cout << " error 3 " << endl;
            }
            else {
                Chosen_client_ip = sender_ip.toString();
                level_3 = true;
            }
        } else if (Is_client && !level_2) {
            socket1.bind(port1);
            std::size_t received;
            char data[15];
            sf::IpAddress sender_ip;
            if (socket1.receive(data, 15, received, sender_ip, port1) != sf::Socket::Done) {
//                cout << " error 1 " << endl;
            } else {
                if (Check(servers_ip, sender_ip, number_servers)) {
                    servers_ip[number_servers] = sender_ip;
                    number_servers += 1;
                }
            }
        }
        if(connected){
            start_game(server_ip, Is_server);
            number_buttons = 0;
            number_servers = 0;
            answer = 5;
            level_2 = false;
            level_3 = false;
            connected = false;
            Is_server = false;
            Is_client = false;
            count = 0;
        }
        window.clear(sf::Color::White);
        render1(& window, buttons, number_buttons);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
}



int main() {
    bool Is_server;
    std::string server_ip = "";
    Show_menu(server_ip, Is_server);
//    start_game(server_ip, Is_server);



//    std::this_thread::sleep_for(std::chrono::seconds(2));


    return 0;
}







//    int a;
//    std::string ip;
//    std::cin >> a;
//    sf::UdpSocket socket;
//    unsigned short port = 12345;
//    while (true) {
//        if (a == 0) {
//            char data[] = "Salam";
//            ip = sf::IpAddress::Broadcast.toString();
//            if (socket.send(data, 10, sf::IpAddress::Broadcast, port) != sf::Socket::Done) {
//                cout << " error 2 " << endl;
//            }
//        }
//        else {
//            socket.bind(port);
//            std::size_t received;
//            char data[] = "GFGH";
//            sf::IpAddress sender;
//
//            if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done) {
//                cout << " error 3 " << endl;
//            }
//            cout << sender.toString() << endl;
//            cout << data << endl;
//        }
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }





//sf::Font font;
//if (!font.loadFromFile("/home/mehrdad/.themes/FONT/San Francisco.ttf")){
//std::cout << "ERR " << std::endl;
//}
//sf::Text text;
//text.setFont(font);
//text.setFillColor(sf::Color::Black);
//text.setString("Hello world");
//text.setPosition(120,220);
//window.draw(text);
