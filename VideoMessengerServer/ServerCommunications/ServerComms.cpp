#include "ServerComms.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

//Instantiate a Communications object to network with a server.
ServerComms::ServerComms() {
	cout << "Server Communications object instantiated ^.^" << endl;

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


	//Bind to Socket
	int s;
	//s = socket(res->);


	//Free the linked-list
	freeaddrinfo(servinfo);
}

//Client has connected
void ServerComms::connect() {
	
	//Create socket
	 

	//Bind to Socket
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

void ServerComms::clientToServer(string address) {
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