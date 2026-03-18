#include "json.hpp"
#include <Winsock2.h>
using json = nlohmann::json;

class RequestToServer {
	SOCKET clientSocket;
	void init();
public:
	void sender(const json& s);
	json reciver();
	RequestToServer();
};