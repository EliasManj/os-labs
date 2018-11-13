/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#define N_ARGS 10

int operation(int values[], char operation);

typedef struct {
  char operation;
  int values[N_ARGS];
} package;

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;
        int i;
        package p;

        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
            (struct sockaddr *)&client_address, &client_len);

/*  We can now read/write to client on client_sockfd.  */

        read(client_sockfd, &p, sizeof(p));
        printf("Server 1 recived from client the following  package\n");
        printf("Operation: %c\n", p.operation);
        printf("Values: \n");
        for(i = 0; i < N_ARGS; i++){
          printf("%d -> %d\n", i, p.values[i]);
        }
/*Make the operation*/
        int result;
        if (p.operation != '-' && p.operation != 'x' && p.operation != '+'){
          printf("Server: Invalid operation\n");
          result = 0xFFFFFFFF;
          write(client_sockfd, &result, 4);
        } else {
          result = operation(p.values, p.operation);
          printf("Result: %d\n", result);
          write(client_sockfd, &result, 4);
        }
        close(client_sockfd);
    }
}

int operation(int values[], char operation){
  int i;
  int result = 0;
  result = values[0];
  if(operation == '+'){
    for(i = 1; i < N_ARGS; i++){
      result += values[i];
    }
  } else if (operation == '-'){
    for(i = 1; i < N_ARGS; i++){
      result -= values[i];
    }
  } else if (operation == 'x'){
    for(i = 1; i < N_ARGS; i++){
      result *= values[i];
    }
  }
  return result;
}
