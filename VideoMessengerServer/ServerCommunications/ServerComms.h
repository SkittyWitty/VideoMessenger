#ifndef SERVER_COMMS_H
#define SERVER_COMMS_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>

using namespace std;

const string PORT = "9000";
const int BACKLOG = 10; //Number of allowed connections

class ServerComms {
public:
	ServerComms();
	void connect();
	void disconnect();
	void send(); 
	void receive();

private:
	//Set up structure for connecting
	int status;
	int socketfd, newclientfd;
	struct addrinfo hints;
	struct addrinfo* results;	//pointer to the results
	socklen_t addrSize;
	struct socketaddr_storage inAddr;
};

#endif
