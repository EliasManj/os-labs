### Instructions

Create a new directory lab1.9 in your os-labs github repository and implement a matrices multiplicator with the following specs.

1. Create a new multiplier.c file
2. Your program should be able to receive one argument which will be know as NUM_BUFFERS inside the program.
3. You will read a couple of files (matA.dat, matB.dat) which contain data that will be used for the matrices multiplication. It's an array that represents all matrix's rows in an one-dimension array.
4. Below some key required functions that will be required:

* long * readMatrix(char *filename) // Reads matrix file and returns an long type array with content of matrix.
* long * getColumn(int col, long *matrix) // Returns the specified array that represents a column in the matrix array.
* long * getRow(int row, long *matrix) // Returns the specified array that represents a row in the matrix array.
* int getLock() // Search for an available buffer, if so it returns the available lock id which is the same buffer id, otherwise returns -1
* int releaseLock(int lock) // Releases a buffer and unlock the mutex. Returns 0 for successful unlock, otherwise -1.
* long dotProduct(long *vec1, long *vec2)  // Given 2 arrays of 2000 lenght, it calculates the dot product and returns it as a long type value.
* long * multiply(long *matA, long *matB) // Here's where all the magic happens. Explained in Matrix multiplication section
* int saveResultMatrix(long *result) // Saves result matrix into a new result.dat file, return 0 for a successful operation, otherwise it will return -1

#### Some key required global variables.

* NUM_BUFFERS // Number of temporal buffers for dot product operations
* long **buffers // An array of NUM_BUFFERS pointers to the available buffers that will serve as temporal rows to be stored into final result matrix. 
* pthread_mutex_t *mutexes // Mutexes that will help to know which buffer is available
    long * result // Will store the result of matA and matB multiplication

#### Matrix multiplication

* You will have a loop that is creating NxN (2000*2000) concurrent threads for calculating the row*col operations between matA and matB.
* Each thread will execute row*col operation and will use available buffers for storing the result of the dot product. 
    getLock function will be required to get a buffer to have a place where to store the dot product result, if there's no available buffer, thread will need to wait.
* releaseLock will be used to release a buffer to be used by another thread.
* At the end, you'll wait for all processes to join the main execution.
* Finally, save your result by calling the saveResultMatrix function.


### Compile and run

`gcc multiplier.c -o multiplier -lpthread`

`./multiplier`
