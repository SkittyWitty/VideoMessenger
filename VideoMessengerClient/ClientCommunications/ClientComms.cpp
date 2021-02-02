#include "ClientComms.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

const char* PORT = "9000"; // the port client will be connecting to 
const int GET_ADDRESS_ERROR = 0;
const int MAX_DATA_SIZE = 100; // max number of bytes we can get at once 

using namespace std;

ClientComms::ClientComms(string serverAddress) {
	this->serverAddress = serverAddress;
}

void ClientComms::connectToSocket() {
	std::cout << "Starting client-side communication" << std::endl;

	struct addrinfo hints;
	int status;

	memset(&hints, 0, sizeof(hints)); //Ensure structure is clear
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	const char* sa = serverAddress.c_str();
	this->serverAddress = serverAddress;
	status = getaddrinfo(sa, PORT, &hints, &results);

	if (status != 0) {
		cout << "Oh no looks like there were some issues >.<" << endl;
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}
	else {
		cout << "Hi looks like we didn't get any errors" << endl;
		printServerAddressInfo();
	}

	//Initialize socket
	sockfd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

	if (sockfd == -1) {
		perror("client: socket");
		return;
	}

	//Connect
	int connectionStatus = connect(sockfd, results->ai_addr, results->ai_addrlen);

	if (connectionStatus == -1) {
		cout << "There was an error with connecting: " << gai_strerror(errno) << endl;
		close(sockfd);
		return;
	}
	else {
		cout << "Connection successful!" << endl;
		char buf[MAX_DATA_SIZE];
		if (recv(sockfd, buf, MAX_DATA_SIZE, 0) > 0) {
			buf[MAX_DATA_SIZE] = '\0';

			printf("client: received '%s'\n", buf);
		}
		else {
			perror("recv");
		}
	}

	if (results == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return;
	}
}

void ClientComms::printServerAddressInfo() {
	string serverInfoString;
	
	sockaddr_in* ipv4 = (sockaddr_in*)results->ai_addr;
	void* addr = &(ipv4->sin_addr);
	serverInfoString += "IPv4: ";
	char serverInfoArr[INET_ADDRSTRLEN];

	inet_ntop(results->ai_family, addr, serverInfoArr, sizeof(serverInfoArr));
	serverInfoString += serverInfoArr;
	cout << "okay I print now" << endl;
	cout << serverInfoString << endl;
}

void ClientComms::recvData() {
	int numbytes;
	char buf[MAX_DATA_SIZE];

	if ((numbytes = recv(sockfd, buf, MAX_DATA_SIZE - 1, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	buf[numbytes] = '\0';

	printf("client: received '%s'\n", buf);

	close(sockfd);
}	
