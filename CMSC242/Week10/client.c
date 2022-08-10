// client.c 

#include <sys/socket.h> 
#include <arpa/inet.h> 
#define PORT 8080 
#define DOMAIN AF_INET6

int main(int argc, char const *argv[]) 
{
 	//if(argc < 3) {
	// printf("Not enough arguments");
	//}
   		
	int sock;
	struct sockaddr_in6 address; 
	
	sock = socket(DOMAIN, SOCK_STREAM, 0);

	address.sin6_family = DOMAIN; 
	address.sin6_port = htons(PORT); // "In practice, only the port field needs to be formatted with htons()"
	inet_pton(DOMAIN, "::1", &address.sin6_addr); // "::1" is IPv6 "loopback" address

	connect(sock, &address, sizeof(address));
	printf("Connection made to server port: %d\n", PORT);
	
	write(sock, argv[2], strlen(argv[2]));
	printf("String sent to server\n");
	
	return 0; 
} 
