#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>


class ClientComms {
public:
	ClientComms(string serverAddr);
};