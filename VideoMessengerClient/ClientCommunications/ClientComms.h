#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>


class ClientComms {
public:
	ClientComms(std::string serverAddr);
	void connectToSocket();

private:
	void printServerAddressInfo();
	std::string serverAddress;
	addrinfo* results;
	int sockfd;
	void recvData();
};
