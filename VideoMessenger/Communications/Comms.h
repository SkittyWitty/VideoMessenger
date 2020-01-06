#ifndef COMMS_H
#define COMMS_H

#include <iostream>

using namespace std;

class Comms {
public:
	Comms();
	void connect();
	void disconnect();
	void send();
	void receive();
	void clientToServer(string address);
};

#endif
