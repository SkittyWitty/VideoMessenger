#include "VideoMessengerClient.h"
#include "ClientCommunications/ClientComms.h"

//Used for OS neutral timing mechanisms
#include <chrono>
#include <thread>


using namespace std;

int main (){
	cout << "Video Messenger Client" << endl;

	string ipAddress, portNum;
	cin >> ipAddress;

	ClientComms* comms = new ClientComms(ipAddress);
	comms->connectToSocket();

	chrono::milliseconds timespan(10000); 
	this_thread::sleep_for(timespan);

	return 0;
}
