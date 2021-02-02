#include "VideoMessengerClient.h"
#include "ClientCommunications/ClientComms.h"
#include <unistd.h>

using namespace std;

int main (){
	cout << "Video Messenger Client" << endl;

	string ipAddress, portNum;
	cin >> ipAddress;

	ClientComms* comms = new ClientComms(ipAddress);
	comms->connectToSocket();

	usleep(10000);

	return 0;
}
