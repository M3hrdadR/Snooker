//
// Created by mehrdad on 7/24/18.
//


#include "../Headers/Network.h"
#include <SFML/Network.hpp>
#include <iostream>
using std::cout;
using std::endl;

Network::Network(Resource * resource) {
    this->resource = resource;
    this->is_server = true;
    this->ip = "";

    this->listener = new sf::TcpListener;
    sf::Socket::Status status = listener->listen(12345);
    if(status != sf::Socket::Done){
        while (status != sf::Socket::Done){
            status = listener->listen(12345);

        }
    }
}

Network::Network(Resource * resource, std::string ip) {
    this->resource = resource;
    this->is_server = false;
    this->ip = ip;
}



void Network::listen() {
    if (this->is_server) {
        this->socket = new sf::TcpSocket;
        this->socket->setBlocking(false);
        sf::Socket::Status status = this->listener->accept(*this->socket);
        if(status != sf::Socket::Done){
            while (status != sf::Socket::Done){
                status = this->listener->accept(*this->socket);
            }
        }
    }
}

void Network::connect() {
    if (not this->is_server){
        this->socket = new sf::TcpSocket;
        this->socket->setBlocking(false);
        sf::Socket::Status status = this->socket->connect(this->ip, 12345);
        if(status != sf::Socket::Done){
            while (status != sf::Socket::Done){
                status = this->socket->connect(this->ip, 12345);

            }
        }
    }
}

void Network::send() {
    std::string message = this->resource->get();
//    std::string message = " salam ";
    char* c_message = new char[(int)message.size() + 1];

    for (int i = 0; i < message.size(); i++)
        c_message[i] = message[i];

    this->socket->send(c_message, (int)message.size());
    delete c_message;
}

void Network::receive() {
    char data[1200];
    size_t received;
    this->socket->receive(data, 1200, received);
    if (received != 0) {
        std::string message = std::string(data);
        this->resource->set(message);
    }
}


//    sf::Socket::Status status = this->socket->send(c_message, (int)message.size());
//    if(status == sf::Socket::Partial){
//        while (status != sf::Socket::Done){
//            status = this->socket->send(c_message, (int)message.size());
//            cout << "safse" << endl;
//        }
//    } else{
//        cout << "send " << endl;
//    }

