#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CLIENTS 5

#define CLIENT_SUM 0
#define STR_SUM "SUM"
#define CLIENT_DIF 1
#define STR_DIF "DIF"
#define CLIENT_PRO 2
#define STR_PRO "PRO"
#define CLIENT_DIV 3
#define STR_DIV "DIV"
#define CLIENT_USE 4
#define STR_USE "USE"

#define SERVER_ADDRESS "127.0.0.1"
//#define SERVER_ADDRESS "192.168.43.106"
#define SERVER_PORT 7891


int create_socket(char *, int );
void close_socket(int);
int close_client(int , int , int *, int *, int *);
int assign_socket(int ,int , int , int *, int *, int *);

int main()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  //Connected clients
  int connected = 0;

  int sockets[MAX_CLIENTS];
  int sockets_s[MAX_CLIENTS];

  int map_sockets[MAX_CLIENTS];

  int current_sock = 0;

  //Reading Buffer
  unsigned char buffer[512];

  //Socket Main
  int descriptor_sock;

  //Number of received bytes
  int len_rx;

  //Socket reset
  for (current_sock = 0; current_sock < MAX_CLIENTS; current_sock++)
  {
    sockets_s[current_sock] = 0;
    map_sockets[current_sock] = -1;
  }

  //Socket main creator
  descriptor_sock = create_socket(SERVER_ADDRESS,SERVER_PORT);

  //printf("address %s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  printf("Server: Waiting for clients...\n");
  printf("Server: Clients connected:%d\n", connected);

  while (1)
  {

    //Delay
    usleep(100);

    for (current_sock = 0; current_sock < MAX_CLIENTS; current_sock++)
    {

      if (sockets_s[current_sock] == 0)
      {

        //Wait for sockets
        if ((sockets[current_sock] = accept(descriptor_sock, 0, 0)) != -1)
        {
          connected++;
          int errore;
          sockets_s[current_sock] = 1;
          errore = fcntl(sockets[current_sock], F_SETFL, O_NONBLOCK);

          printf("Server: New client connected with id:%d\n", current_sock);
          printf("Server: Clients connected:%d\n", connected);
        }
      }
      else
      {
        //The client is not connected anymore
        if ((len_rx = read(sockets[current_sock], buffer, sizeof(buffer))) == 0)
        {
          connected = close_client(connected, current_sock, sockets, sockets_s, map_sockets);

        }
        else if (len_rx > 0)
        {
          buffer[len_rx] = 0;
          puts(buffer);
          if (strcmp(buffer, STR_SUM) == 0)
          {
            connected = assign_socket(CLIENT_SUM, connected, current_sock, sockets, sockets_s, map_sockets);
           // write(sockets[current_sock], "1+2+3+4+5+6+7+a", sizeof("1+2+3+4+5+6+7+a")-1);
          }
          else if (strcmp(buffer, STR_DIF) == 0)
          {
            connected = assign_socket(CLIENT_DIF, connected, current_sock, sockets, sockets_s, map_sockets);
          }
          else if (strcmp(buffer, STR_PRO) == 0)
          {
            connected = assign_socket(CLIENT_PRO, connected, current_sock, sockets, sockets_s, map_sockets);
          }
          else if (strcmp(buffer, STR_DIV) == 0)
          {
            connected = assign_socket(CLIENT_DIV, connected, current_sock, sockets, sockets_s, map_sockets);
          }
          else if (strcmp(buffer, STR_USE) == 0)
          {
            connected = assign_socket(CLIENT_USE, connected, current_sock, sockets, sockets_s, map_sockets);
          }
          else {
            //dat
            //res
            char temp[4];
            int i = 0;
            while(i<3) {
              temp[i] = buffer[i];
              i++;
            }
            temp[i] = '\0';
            if(strcmp(temp,"res\0") == 0 || strcmp(temp,"RES\0") == 0) {
              printf("%s\n",buffer);
              write(sockets[map_sockets[CLIENT_USE]] ,buffer+3,strlen(buffer)-2);
            } else if(strcmp(temp,"dat\0") == 0 || strcmp(temp,"DAT\0") == 0) {
              printf("%s\n",buffer);
              write(sockets[map_sockets[CLIENT_SUM]] ,buffer+3,strlen(buffer)-3);
            } else {
              puts("Permission denied.");
              write(sockets[current_sock], "CLOSE", 5);
              usleep(100);
              connected = close_client(connected, current_sock, sockets, sockets_s, map_sockets );
            }
          }
        }
      }
    }
  }

  //Server Close
  close_socket(descriptor_sock);
  printf("Server: Closed.\n");

  return 0;
}

int create_socket(char * address, int port )
{
  int sock, errore;
  struct sockaddr_in temp_sock;

  //Socket creation
  sock = socket(AF_INET, SOCK_STREAM, 0);
  temp_sock.sin_family = AF_INET;
  temp_sock.sin_addr.s_addr = inet_addr(address);
  temp_sock.sin_port = htons(port);

  printf("server address %s\n",inet_ntoa(temp_sock.sin_addr));

  //No blocking socket
  errore = fcntl(sock, F_SETFL, O_NONBLOCK);

  //Bind socket
  errore = bind(sock, (struct sockaddr *)&temp_sock, sizeof(temp_sock));

  //Number of client allowed
  errore = listen(sock, MAX_CLIENTS);

  return sock;
}

void close_socket(int sock)
{
  close(sock);
  return;
}

int close_client(int connected, int current_sock, int *sockets, int *sockets_s, int *map_sockets )
{
  int found = 0;
  int i = 0;
  for (i = 0; i < MAX_CLIENTS; i++)
  {
    if(map_sockets[i] == current_sock) found = 1;
    if(found) break;
  }
  if(found==1) map_sockets[i] = -1;
  
  printf("Client id:%d disconnected\n", current_sock);
  close_socket(sockets[current_sock]);
  sockets_s[current_sock] = 0;
  connected--;
  printf("Server: Clients connected:%d\n", connected);
  return connected;
}

int assign_socket(int c_type, int connected, int current_sock, int *sockets, int *sockets_s, int *map_sockets)
{
  if (map_sockets[c_type] == -1)
  {
    map_sockets[c_type] = current_sock;
  }
  else
  {
    puts("Client already exists.");
    write(sockets[current_sock], "CLOSE", 5);
    usleep(100);
    connected = close_client(connected, current_sock, sockets, sockets_s, map_sockets);
  }
  return connected;
}
