#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <strings.h>

int sock = socket(AF_INET, SOCK_STREAM, 0);

int main()
{
	sockaddr_in server_addr;
	char ip[] = "127.0.0.1";
	int port = 3856;
	socklen_t len = sizeof(server_addr);
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	server_addr.sin_family = AF_INET;
	if (connect(sock, (sockaddr*) &server_addr, sizeof(server_addr)) < 0){std::cout << "Failed Connect\n";}
	write(sock, "kevin", 5);
	char buff[256];
	read(sock, buff, 255);
	printf(buff);
}
