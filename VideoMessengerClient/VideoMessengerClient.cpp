#include "VideoMessengerClient.h"
#include "ClientCommunications/ClientComms.h"

using namespace std;

int main (){
	cout << "Video Messenger Client" << endl;

	string ipAddress, portNum;
	cin >> ipAddress;

	ClientComms* comms = new ClientComms(ipAddress);

	return 0;
}