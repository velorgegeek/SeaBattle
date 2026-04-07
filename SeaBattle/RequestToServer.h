#include <SFML/Network.hpp>

class RequestToServer {
	sf::TcpSocket socket;
	void init();
public:
	void sender(sf::Packet& packet);
	sf::Packet reciver();
	RequestToServer();
};