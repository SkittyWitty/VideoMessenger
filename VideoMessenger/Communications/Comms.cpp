#include "Comms.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

//Instantiate a Communications object to network with a server.
Comms::Comms() {

	cout << "Comms object instantiated ^.^" << endl;
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