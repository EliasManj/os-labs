### Lab 7.1 - Sockets - Calculator

#### Instructions

##### Modify client1.c to support:

Command line arguments with the following format: "./client1 <operation> [list of numbers separated by space]" (Example: ./client1 + 3 2 4)
  
The supported operations will be: 

* Addition (+) of n numbers
* Subtraction (-) of n numbers
* Multiplication (*) of n numbers
        
Client sends operation and list of numbers and receives the result after the operation has been calculated in the server.

##### Modify server1.c to support:

Add support to receive <operation> and list of numbers (max 10 numbers) to apply the desired operation
  
Supported operations will be: addition (+), subtraction (-) and multiplication (*). In case that an unknown operation was requested, server should return -99999. Client should print "unsupported operation".


#### Compile and Run

  `gcc client1.c -o client1`
  
  `gcc server1.c -o server1`
  
  `./server1 &`
  
  * Sum
  `./client1 + 1 3 5 7 23`
  * Mult
  `./client1 x 1 3 5 7`
  * Sub
  `./client1 - 100 3 5 7 23`
