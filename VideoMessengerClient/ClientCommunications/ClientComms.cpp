#include "ClientComms.h"

using namespace std;

ClientComms::ClientComms(string serverAddr) {
	cout << "Starting client-side communication" << endl;

	struct addrinfo hints, *serverInfo;
	int sockfd;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	const char* sa = serverAddr.c_str();
	getaddrinfo(sa, "9000", &hints, &serverInfo);

	//Initialize socket
	sockfd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	//Connect
	connect(sockfd, serverInfo->ai_addr, serverInfo->ai_addrlen);
}

