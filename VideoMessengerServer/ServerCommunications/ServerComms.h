#ifndef SERVER_COMMS_H
#define SERVER_COMMS_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>

using namespace std;

class ServerComms {
public:
	ServerComms();
	void startServer();
	void getServerAddressInfo();
	void process();
	void connect();
	void disconnect();

private:
	//Set up structure for connecting
	int socketfd, newclientfd;
	addrinfo hints;
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	addrinfo *servinfo;
	sockaddr_storage their_addr; // connector's address information
	socklen_t addressSize;
    struct sigaction sa;
	char clientAddressString[INET6_ADDRSTRLEN];

	void processReaper();
	void beginListening();
};

#endif
