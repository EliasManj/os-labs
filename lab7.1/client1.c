/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#define N_ARGS 10

typedef struct {
  char operation;
  int values[N_ARGS];
} package;

int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    int op_result;
    char ch = 'A';

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }
    if(argc > N_ARGS+2){
      perror("Too many arguments");
      exit(1);
    }
/*  We can now read/write via sockfd.  */
    package p;
    int i;
    printf("This is client\n");
    p.operation = (char)*argv[1];
    printf("Operation %c\n", p.operation);
    //Fill array with zeros or ones
    if (argc < N_ARGS+2){
      //If multiplication or div add ones
      if(p.operation == 'x'){
        for(i=argc-2; i<N_ARGS; i++){
          p.values[i] = 1;
        }
      }
      //If sum add zeros
      else if (p.operation == '+' || p.operation == '-'){
        for(i=argc-2; i<N_ARGS; i++){
          p.values[i] = 0;
        }
      }
    }
    for(i=2; i< argc; i++){
        p.values[i-2] = atoi(argv[i]);
    }
    /*
    for(i = 0; i < N_ARGS; i++){
      printf("Client value: %d\n", p.values[i]);
    }*/

    printf("\n\n\n");
    write(sockfd, &p, sizeof(p));
    read(sockfd, &op_result, 4);
    if(op_result == 0xFFFFFFFF){
      printf("client: got invalid operation\n");
    }
    printf("result from server = %d\n", op_result);
    close(sockfd);
    exit(0);
}
