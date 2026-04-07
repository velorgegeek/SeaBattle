#include <string>
#include "RequestToServer.h"


RequestToServer::RequestToServer(){
    init();
}
void RequestToServer::init() {
    sf::Socket::Status status = socket.connect({ 192, 168, 0, 5 }, 53000);
    if (status == sf::Socket::Status::Error) {
        return;
    }
    socket.setBlocking(false);

}

void RequestToServer::sender(sf::Packet& packet) {
    while (socket.send(packet) == sf::Socket::Status::Partial);
}
sf::Packet RequestToServer::reciver() {
    sf::Packet packet;
    return packet;
}