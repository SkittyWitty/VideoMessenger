#ifndef SERVER_COMMS_H
#define SERVER_COMMS_H

#include <iostream>

using namespace std;

class ServerComms {
public:
	ServerComms();
	void connect();
	void disconnect();
	void send();
	void receive();
	void clientToServer(string address);
};

#endif
