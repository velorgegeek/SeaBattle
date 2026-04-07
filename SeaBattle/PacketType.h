#pragma once
#include <SFML/Network.hpp>
enum class PacketType{
	Shoot,
	ChangePrepare,
	CreateRoom,
	JoinRoom,
	LeaveRoom,

	ResponseShoot,
	EnemySurrender,
	GameStart,
	GameOver,
	OpponentPrepare,
	PlayerJoined
};
sf::Packet& operator>>(sf::Packet& packet, PacketType& type);

sf::Packet& operator<<(sf::Packet& packet, PacketType type);
