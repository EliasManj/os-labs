### Lab 7.2 - Sockets - Simple Time Server

#### Instructions

##### Modify server3.c to support:

Every time a new client connects, server will provide the current time
    
When a new client is connected, the server prints the client id and then sends the time
    
Multiple clients can connect to a single server
    
Server time information can be obtained from time.h

##### Modify client3.c to support:

Add command line support for the client ID. Example: "./client3 <id>"
    
Client should send ID to the server
    
Once a client is started, it will keep sending time request to the server every second.
    
Test multiple client3 at the same time
    
#### Compile and Run

`gcc client3.c -o client3`
  
`gcc server3.c -o server3`
 
`./server3 &`

`./client3 ID`
