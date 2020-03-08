#include "ServerComms.h"

using namespace std;

//Instantiate a Communications object to network with a server.
ServerComms::ServerComms() {
	cout << "Server Communications object instantiated ^.^" << endl;

	memset(&hints, 0, sizeof(hints));	//Empty out struct
	hints.ai_family = AF_UNSPEC;		//neutral protocol family ipv6 or ipv4 capable
	hints.ai_socktype = SOCK_STREAM;	//TCP Stream Sockets
	hints.ai_flags = AI_PASSIVE;		//Will fill in IP with hosts address

	if ((status = getaddrinfo(NULL, "9000", &hints, &results)) != 0) {
		fprintf(stderr, "gettaddr info error: %s\n", gai_strerror(status));
	}
	else {
		cout << "Able to find information reguarding host machine address" << endl;
	}

	//Initialize socket
	socketfd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

	//Bind to Socket
	bind(socketfd, results->ai_addr, results->ai_addrlen);
	listen(socketfd, BACKLOG);

	//Begin Listening
	cout << "Server is listening" << endl;

	addrSize = sizeof(inAddr);
	newclientfd = accept(socketfd, (struct sockaddr*)&inAddr, &addrSize);

	//Free the linked-list
	if (status == 0) {
		freeaddrinfo(results);
	}
}

//Client has connected
void ServerComms::connect () {
	
}

// Disconnect from server
void ServerComms::disconnect() {

}

// Send message to client
void ServerComms::send() {

}

// Receive a message for server we are connected to 
void ServerComms::receive() {

}