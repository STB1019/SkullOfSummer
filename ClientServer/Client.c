/****************** CLIENT CODE ****************/
/*Ref. http://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#ifndef PARAM_BUFFER_SIZE
#define PARAM_BUFFER_SIZE 1024
#endif

#ifndef PARAM_CLIENT_ADDRESS
#define PARAM_CLIENT_ADDRESS "127.0.0.1"
#endif

#ifndef PARAM_CLIENT_PORT
#define PARAM_CLIENT_PORT 7891
#endif

int main(){
  int clientSocket;
  char buffer[PARAM_BUFFER_SIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(PARAM_CLIENT_PORT);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(PARAM_CLIENT_ADDRESS);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket, buffer, PARAM_BUFFER_SIZE, 0);

  /*---- Print the received message ----*/
  printf("Data received: %s",buffer);   

  return 0;
}
