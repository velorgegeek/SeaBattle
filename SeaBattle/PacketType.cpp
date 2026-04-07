#include "PacketType.h"

sf::Packet& operator<<(sf::Packet& packet, PacketType type) {
    return packet << (std::uint16_t)type;
}

sf::Packet& operator>>(sf::Packet& packet, PacketType& type) {
    std::uint16_t temp;
    packet >> temp;
    type = (PacketType)temp;
    return packet;
}