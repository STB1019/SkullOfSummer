/****************** SERVER CODE ****************/
 /*Ref. http://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/*/

 #include <stdio.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <string.h>

 #ifndef PARAM_BUFFER_SIZE
 #define PARAM_BUFFER_SIZE 1024
 #endif

 #ifndef PARAM_MESSAGE
 #define PARAM_MESSAGE "Hello World\n"
 #endif

 #ifndef PARAM_SERVER_ADDRESS
 #define PARAM_SERVER_ADDRESS "127.0.0.1"
 #endif

 #ifndef PARAM_SERVER_PORT
 #define PARAM_SERVER_PORT 7891
 #endif

 #ifndef PARAM_SOCKET_LIMIT
 #define PARAM_SOCKET_LIMIT 5
 #endif


int main()
{
  typedef struct{
    int index;
    char label[10];
  }list_element;

 int welcomeSocket, newSocket;
 char  buffer[PARAM_BUFFER_SIZE];
 struct sockaddr_in serverAddr;
 struct sockaddr_storage serverStorage;
 socklen_t addr_size;

   /*---- Create the socket. The three arguments are: ----*/
 welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

   /*---- Configure settings of the server address struct ----*/
 serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(PARAM_SERVER_PORT);
serverAddr.sin_addr.s_addr = inet_addr(PARAM_SERVER_ADDRESS);
memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

   /*---- Bind the address struct to the socket ----*/
 bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

   /*---- Listen on the socket, with 5 max connection requests queued ----*/
 if(listen(welcomeSocket,PARAM_SOCKET_LIMIT)==0)
   printf("Listening\n%s:%d\n",PARAM_SERVER_ADDRESS,PARAM_SERVER_PORT);
 else
   printf("Error\n");

   /*---- Accept call creates a new socket for the incoming connection ----*/
 addr_size = sizeof serverStorage;
 newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

   /*---- Send message to the socket of the incoming connection ----*/
list_element element;
element.index = 10;
strcpy(element.label, "ciao");

strcpy(buffer, element.label);
 send(newSocket, buffer,strlen(PARAM_MESSAGE),0);

 return 0;
}
