#include "ServerComms.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

//constants 
const char* LISTENING_PORT = "9000";
const int BACKLOG = 10; //Number of allowed connections
const int YES = 1;


//Instantiate a Communications object to network with a server.
ServerComms::ServerComms() {
	cout << "Server Communications object instantiated ^.^" << endl;

	memset(&hints, 0, sizeof(hints));	//Empty out struct
	hints.ai_family = AF_UNSPEC;		//neutral protocol family ipv6 or ipv4 capable
	hints.ai_socktype = SOCK_STREAM;	//TCP Stream Sockets
	hints.ai_flags = AI_PASSIVE;		//Will fill in IP with hosts address
}

void ServerComms::startServer() {
	getServerAddressInfo();
	beginListening();
	processReaper();
	process();
}

//Client has connected
void ServerComms::connect () {
}

// Disconnect from server
void ServerComms::disconnect() {}

void sigchld_handler(int s)
{
	(void)s; // quiet unused variable warning

	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	while (waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void* getAddress(sockaddr* sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((sockaddr_in*)sa)->sin_addr);
	}
	else {
		return &(((sockaddr_in6*)sa)->sin6_addr);
	}
}


void ServerComms::getServerAddressInfo() {
	int status;
	if ((status = getaddrinfo(NULL, LISTENING_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "gettaddr info error: %s\n", gai_strerror(status));
		cout << servinfo->ai_addr << endl;
	}
	else {
		cout << "Able to find information reguarding host machine address" << endl;
	}
}

void ServerComms::beginListening() {
	addrinfo* p;

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
			perror("server: socket");\
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &YES, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
}

void ServerComms::processReaper() {
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}

void ServerComms::process() {
	std::string str = "Hello yesh dis is Min-slice.";
	const char* message = str.c_str();
	printf("Size of string: %d\n", str.length());

	printf("server: waiting for connections...\n");
	int new_fd;

	while (1) {  // main accept() loop
		addressSize = sizeof(their_addr);
		new_fd = accept(sockfd, (sockaddr*)&their_addr, &addressSize);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			getAddress((struct sockaddr*)&their_addr),
			clientAddressString, sizeof(clientAddressString));
		printf("server: got connection from %s\n", clientAddressString);

		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener
			if (send(new_fd, message, str.length(), 0) == -1) {
				perror("send");
			}
			close(new_fd);
			exit(0);
		}
		close(new_fd);  // parent doesn't need this
	}
}
