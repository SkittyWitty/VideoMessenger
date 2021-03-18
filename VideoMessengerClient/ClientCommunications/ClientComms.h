#include <iostream>
#include <sys/types.h>
#include <cstring>

//OS specific includes
#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else //UNIX
	#include <sys/socket.h>
	#include <netdb.h>
#endif



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
