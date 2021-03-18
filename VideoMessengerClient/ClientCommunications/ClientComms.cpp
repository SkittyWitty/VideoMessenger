#include "ClientComms.h"

//Standard library includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//Unix based OS specific includes
#ifdef unix
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#endif

const char* PORT = "9000"; // the port client will be connecting to 
const int GET_ADDRESS_ERROR = 0;
const int MAX_DATA_SIZE = 100; // max number of bytes we can get at once 

using namespace std;

ClientComms::ClientComms(string serverAddress) {
	this->serverAddress = serverAddress;
}

void ClientComms::connectToSocket() {
	std::cout << "Starting client-side communication" << std::endl;

#ifdef _WIN32
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}
#endif

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

#ifdef _WIN32
	if (sockfd == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(results);
		WSACleanup();
		return;
	}
#else
	if (sockfd == -1) {
		perror("client: socket");
		return;
	}
#endif

	//Connect
	int connectionStatus = connect(sockfd, results->ai_addr, results->ai_addrlen);
#ifdef _WIN32
	if (connectionStatus == SOCKET_ERROR) {
		closesocket(sockfd);
		sockfd = INVALID_SOCKET;
		printf("Unable to connect to server!\n");
		freeaddrinfo(results);
		WSACleanup();
		return;
	}
#else
	if (connectionStatus == -1) {
		cout << "There was an error with connecting: " << gai_strerror(errno) << endl;
		close(sockfd);
		return;
	}
#endif
	else {
		cout << "Connection successful!" << endl;
		char buf[MAX_DATA_SIZE];
		if (recv(sockfd, buf, MAX_DATA_SIZE, 0) > 0) {
			buf[MAX_DATA_SIZE-1] = '\0';

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
#ifdef _WIN32
	WSACleanup();
#else
	close(sockfd);
#endif
}	
