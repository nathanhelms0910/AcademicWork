// server.c

#include <time.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>  
#define DOMAIN AF_INET
#define BUFF_SIZE 1024

int main(int argc, char const *argv[]) 
{
  if(argc < 2) {
	printf("Please provide a port number\n");
  }
  time_t t;
  time(&t);
  int PORT = atol(argv[1]);
  int sock; 
  struct sockaddr_in6 address; 

  sock = socket(DOMAIN, SOCK_STREAM, 0);
  address.sin6_family = DOMAIN; 
  address.sin6_port = htons(PORT);
  address.sin6_addr = in6addr_any; 

  int opt = 1; // True
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); 	
  bind(sock, &address, sizeof(address));
  printf("Listening on port: %d\n", PORT);
  listen(sock, 5);
  while(1) {
	int addrlen = sizeof(address);	
	int connection = accept(sock, &address, &addrlen);
	printf("Connection made successfully from %d\n\n", connection); //this is NOT printing the address	
	if(connection != -1) {
	  int rdFile;
	  while(1) {	
		char buffer[BUFF_SIZE] = {0};
		char response[BUFF_SIZE];
		char failedFile[BUFF_SIZE] = "HTTP/1.1 500 Internal Server Error\r\n";
		char unsupportedType[BUFF_SIZE] = "HTTP/1.1 501 Not Implemented\r\nContent-Length: 28\r\n";	
		int readVal = read(connection, buffer, BUFF_SIZE);	//reading the request
		int openFile;
		if(readVal <= 0) {
		  break;
		}

		char* headerFunc = strstr(buffer, " ");
		int offset = headerFunc - buffer;

		if(strncmp(buffer, "GET", offset) == 0) { //if a GET request...
		  char *path = strchr(buffer, ' ') + 1;
		  char *endpath = strchr(path, ' ') - 1;
		  char filename[endpath - path];

		  strncpy(filename, path+1, endpath - path);
		  filename[sizeof(filename)] = 0;

		  if(strcmp(filename, "..") == 0 || strcmp(filename, ".") == 0) { //if user GET requests for the .. or . directory files, redirect to index.html
			strcpy(filename, "index.html");
		  }
		  openFile = open(filename, O_RDONLY);
		  if(openFile == -1) { //if file does not exist, send protocol to user
			write(connection, failedFile, strlen(failedFile));
		  }
		  else { // if any other request...
			rdFile = read(openFile, (void*)response, BUFF_SIZE);
			write(connection, response, strlen(response));
			printf("HTTP/1.1 200 OK\r\n");
			printf("Date: %s\r\n", ctime(&t));	
			printf("Content-Length: %d\r\n", rdFile);
			printf("Content-Type: text/html\r\n");
		  }

		}
		else if(strncmp(buffer, "HEAD", offset) == 0) {
		  char *header = strstr(buffer, "\r\n"); //this was various thoughts jumbled up. Currently does not work
		  char *headLine = buffer - header;
		  printf("%s\n", headLine);

		}
		else {
		  write(connection, unsupportedType, strlen(unsupportedType));
		  printf("%s\n", unsupportedType);

		}




		//int openFile = open(buffer, O_RDONLY);


		//rdFile = read(openFile, (void*)response, BUFF_SIZE);
		//char* host = "gandalf.cs.longwood.edu";
		//printf("%s\n", response);
		//snprintf(request, BUFF_SIZE-1, "GET %s HTTP/1.1\r\n"
		//	"Host: %s\r\n"
		//	"Content-type: text/html\r\n"
		//	"Content-length: %d\r\n\r\n"

		//	"%s\r\n", file, host, strlen(response), response);	   


		//write(connection, response, strlen(response));

		//printf("%s\n", buffer );
		//printf("%s\n", request );

		close(openFile);
	  }
	  close(connection);
	  close(rdFile);


	}
	printf("Connection terminated\n");
  }
  return 0; 
}
