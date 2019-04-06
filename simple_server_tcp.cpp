#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <csignal>
#include <strings.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

int sock = socket(AF_INET, SOCK_STREAM, 0), finish = 0;

void Stop(int signal)
{
	::finish = 1;
	try{
		close(::sock);
	}catch(...)
	{

	}
	exit(0);
}

int main()
{
	int port = 3856;
	sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(port);
	if (bind(sock, (sockaddr *) &serv, sizeof(serv))<0){std::cout << "FAILED BIND\n";}
	listen(sock, 5);
	
	signal(SIGINT, ::Stop);
	sockaddr_in cl_addr;

	socklen_t len = sizeof(cl_addr);
	while (!(::finish))
	{
		int client = accept(sock, (sockaddr *) &cl_addr, &len);
		char ip[15];
		std::cout << inet_ntoa(cl_addr.sin_addr) << " " << ntohs(cl_addr.sin_port) << "\n";
		char buffer[256];
		read(client, buffer, 255);
		printf("%s\n", buffer);
		write(client, "kevin", 5);
	}
}
