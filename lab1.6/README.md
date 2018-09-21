### Instructions

This project consists of designing a C program to serve as a shell interface
that accepts user commands and then executes each command in a separate
process. This project can be completed on any Linux, UNIX, or Mac OS X system.
A shell interface gives the user a prompt, after which the next command
is entered. The example below illustrates the prompt osh> and the user’s
next command: cat prog.c. (This command displays the file prog.c on the
terminal using the UNIX cat command.)


`osh> cat prog.c`


One technique for implementing a shell interface is to have the parent process
first read what the user enters on the command line (in this case, cat
prog.c), and then create a separate child process that performs the command.
Unless otherwise specified, the parent process waits for the child to exit
before continuing. 

### Compile and run

`gcc simple-shell.c -o simple-shell`

`./simple-shell`
