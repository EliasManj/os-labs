/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    int client_id;
    char time_str[50];
    int iter = 100;
    int i;
    unsigned int time_to_sleep = 4; // sleep 10 seconds

    /*  Create a socket for the client.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

    if(argc <= 1){
        printf("Client: There are no arguments\n");
        exit(1);
    }

    client_id = atoi(argv[1]);

    printf("Client: The id is %d\n", client_id);
    /*  Now connect our socket to the server's socket.  */
    while(1){
      /*  Name the socket, as agreed with the server.  */
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      result = connect(sockfd, (struct sockaddr *)&address, len);
      if(result == -1) {
          perror("Client: oops: client3 failed\n");
          exit(1);
        }
      write(sockfd, &client_id, sizeof(int));
      read(sockfd, &time_str, sizeof(time_str));
      printf("Client: The time from server is %s\n", time_str);
      while(time_to_sleep)
      time_to_sleep = sleep(time_to_sleep);
      time_to_sleep = 4;
      close(sockfd);
    }
    /*  We can now read/write via sockfd.  */
    exit(0);
}
