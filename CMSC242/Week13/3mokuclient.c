#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

bool myTurn(char turn[2], uint8_t myPiece) {
  if(strcmp(turn, "X") == 0 && myPiece == 16) {
	return true;
  }
  if(strcmp(turn, "O") == 0 && myPiece == 17) {
	return true;
  }
  else {
	return false;
  }
}

int main(int argc, char *argv[])
{
  uint16_t gameID;
  if(argc < 2) { //if a port num is not included
	printf("Error: Please enter a port number and server\n");
	exit(1);
  }
  if(argc == 4) {
	gameID = htons(atoi(argv[3]));
  }
  else {
	gameID = htons(00);
  }


  int sock;
  char* host = argv[1];
  struct sockaddr_in client; //struct definitions
  struct addrinfo* addr = NULL;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(argv[1], argv[2], &hints, &addr); //get info on turing

  sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol); //set socket
  if(sock == -1) {
	printf("Error: Socket initialization problem\n");
  }

  if(connect(sock, addr->ai_addr, addr->ai_addrlen) < 0) //try to connect
  {
	printf("Error: Connection failed\n");
	return 1;
  }

  printf("Connected\n");



  //Client <-> Network Byte Transferring
  uint16_t byteParse;
  char board[7][7] = {" 12345", "1.....", "2.....", "3.....", "4.....", "5....."};
  int rd = read(sock, &byteParse, sizeof(byteParse)); //read PlayerID from server
  printf("Player ID: %d\n", ntohs(byteParse));

  int wr = write(sock, &gameID, sizeof(gameID)); //write chosen gameID to server

  char response[5];
  int okrd = read(sock, &response, sizeof(response)); //read OKv3 bytes from server
  printf("%s\n", response);

  int byterd;
  uint16_t bytes[4];

  for(int i = 0; i < 3; ++i) { //Loop read the bytes sent from the server indicating the found opponent, as well as the gameID
	byterd = read(sock, &byteParse, sizeof(byteParse));
	bytes[i] = ntohs(byteParse);
  }
  printf("GameID: %d\n", bytes[0]); //print all loop read values from array
  printf("Player 1 (you): %d\n", bytes[1]);
  printf("Player 2: %d\n", bytes[2]);
  for(int i = 0; i < 6; ++i) {
	printf("%s\n", board[i]);
  }
  uint8_t readBytes;
  char whoTurn[2];
  byterd = read(sock, &readBytes, sizeof(readBytes));
  if(readBytes == 16) {
	printf("You are 'X'. Send first move\n");
	strcpy(whoTurn, "X");
  }
  else if(readBytes == 17) {
	printf("You are 'O' Await opponent's move\n");
	strcpy(whoTurn, "X");
  }
  else {
	printf("Byte Parsing Error\n");
  }

  char command[25];
  int movesMade = 0;
  int rowentry;
  int colentry;
  uint8_t row;
  uint8_t col;
  while(1) {
	if(myTurn(whoTurn, readBytes)) {
	  scanf("%s", command);

	  if(strcmp(command, "whose") == 0){
		printf("It is %s's turn\n", whoTurn);
	  }
	  else if(strcmp(command, "stats") == 0) {
		printf("Player 1 (you): %d\n", bytes[1]);
		printf("Player 2: %d\n", bytes[2]);
		printf("Moves Made: %d\n", movesMade);
	  }
	  else if(strcmp(command, "board") ==  0) {
		for(int i = 0; i < 6; ++i) {
		  printf("%s\n", board[i]);
		}
	  }
	  else if(strcmp(command, "place") == 0) {
		if(myTurn(whoTurn, readBytes)) {
		  scanf("%d", &rowentry);
		  scanf("%d", &colentry);
		  row = rowentry;
		  col = colentry;
		  write(sock, &row, sizeof(row));
		  write(sock, &col, sizeof(col));
		  uint8_t stuff;
		  byterd = read(sock, &stuff, sizeof(stuff));
		  switch(stuff) {
			case 0:
			  printf("Invalid move, try again\n");
			  break;
			case 33:
			  printf("Move ok, await opponent's next move\n");
			  if(strcmp(whoTurn, "X") == 0) {
				strcpy(whoTurn, "O");
			  }
			  else {
				strcpy(whoTurn, "X");
			  }
			  //if(strcmp(whoTurn, "O") == 0) {
			  //strcpy(board[row][col], "O");
			  //strcpy(whoTurn, "X");
			  //}
			  //else {
			  //strcpy(board[row][col], "X");
			  //strcpy(whoTurn, "O");
			  //}
			  movesMade++;
			  break;
			case 34:
			  printf("Game over\n");
			  uint8_t winner;
			  byterd = read(sock, &winner, sizeof(winner));
			  switch(winner) {
				case 16:
				  printf("X Won\n");
				  exit(1);
				case 17:
				  printf("O Won\n");
				  exit(1);
				case 18:
				  printf("Game ended in a draw\n");
				  exit(1);
			  }
			  break;
			case 35:
			  printf("Opponent has terminated the game\n");
			  break;

		  }
		}
		else {
		  printf("It is not your turn\n");

		}
	  }
	  else {
		printf("Not a valid command\n");
	  }
	}
	else {
	  uint8_t oppRead;
	  uint8_t recvRow;
	  uint8_t recvCol;
	  byterd = read(sock, &recvRow, sizeof(recvRow));
	  byterd = read(sock, &recvCol, sizeof(recvCol));
	  printf("Opponent sends a move: Row: %d Col: %d\n", recvRow, recvCol);
	  byterd = read(sock, &oppRead, sizeof(oppRead));
	  switch(oppRead) {
		case 32:
		  printf("Send next move\n");
		  if(strcmp(whoTurn, "X") == 0) {
			strcpy(whoTurn, "O");
		  }
		  else {
			strcpy(whoTurn, "X");
		  }
		  movesMade++;
		  break;
		case 34:
		  printf("Game over\n");
		  uint8_t winner;
		  byterd = read(sock, &winner, sizeof(winner));
		  switch(winner) {
			case 16:
			  printf("X Won\n");
			  exit(1);
			case 17:
			  printf("O Won\n");
			  exit(1);
			case 18:
			  printf("Game ended in a draw\n");
			  exit(1);
		  }
		  break;
		case 35:
		  printf("Opponent has terminated the game\n");
		  exit(1);

	  }
	}
  }
}

