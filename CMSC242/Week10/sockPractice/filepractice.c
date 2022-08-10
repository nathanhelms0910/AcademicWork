#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024

int main(int argc, char const *argv[]) {
  
  char *ip = "0.0.0.0";
  int port = argv[1];
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[BUFF_SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));

  e = listen(sockfd, 10);
  if(e == 0) {
	printf("Listening...\n");
  }
  else {
	printf("Listening failed");
  }

  addr.size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*) &new_addr, &addr_size);

}
