#ifndef COMMS_H
#define COMMS_H

class Comms {
public:
	Comms();
	void connect();
	void disconnect();
	void send();
	void receive();
};

#endif
