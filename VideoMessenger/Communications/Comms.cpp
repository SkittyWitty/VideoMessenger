#include "Comms.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

//Instantiate a Communications object to network with a server.
Comms::Comms() {
	cout << "Comms object instantiated ^.^" << endl;

	//Set up structure for connecting
	int status;
	struct addrinfo hints;
	struct addrinfo* servinfo;	//pointer to the results

	memset(&hints, 0, sizeof(hints)); //Empty out struct
	hints.ai_family = AF_UNSPEC; //neutral protocol family ipv6 or ipv4 capable
	hints.ai_socktype = SOCK_STREAM; //TCP Stream Sockets
	hints.ai_flags = AI_PASSIVE; //Will fill in IP with hosts address

	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "gettaddr info error: %s\n", gai_strerror(status));
	}


	//Do what we would like with server address info


	//Free the linked-list
	freeaddrinfo(servinfo);
}

//Connect to server
void Comms::connect() {

}

// Disconnect from server
void Comms::disconnect() {

}

// Send message to client
void Comms::send() {

}

// Receive a message for server we are connected to 
void Comms::receive() {

}

void Comms::clientToServer(string address) {
	int status;
	struct addrinfo hints;
	struct addrinfo* servinfo; //will point to results

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC; //IPv4 or IPv6 neutral
	hints.ai_socktype = SOCK_STREAM; //TCP Stream Sockets

	//get ready to connect
	status = getaddrinfo(address.c_str(), "3490", &hints, &servinfo);

	//servinfo now points to a linked list of 1 or more structs with address info


}