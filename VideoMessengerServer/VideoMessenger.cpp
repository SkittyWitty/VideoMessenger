// VideoMessenger.cpp : Defines the entry point for the application.
//

#include "VideoMessenger.h"
#include "ServerCommunications/ServerComms.h"
#include "ImageHandling/ImagePack.h"
#include <stdio.h>


int main() {
	std::cout << "Hi-low" << std::endl;

	//ImagePack imgPack;
	ServerComms kk;
	kk.startServer();

 	return 0;
}
