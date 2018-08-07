//
// Created by mehrdad on 7/24/18.
//

#ifndef BILIARD_NETWORK_H
#define BILIARD_NETWORK_H

#include "Resource.h"
#include <SFML/Network.hpp>


class Network {
public:
    Network(Resource * resource);
    Network(Resource * resource, std::string ip);

    void send();
    void receive();
    void listen();
    void connect();
private:
    Resource* resource;
    bool is_server;
    std::string ip;
    sf::TcpListener* listener;
    sf::TcpSocket* socket;
};

#endif //BILIARD_NETWORK_H
