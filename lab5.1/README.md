### Lab 5.1 - Memory Management in Linux

#### Memory1 - Simple Memory Allocation

You allocate memory using the `malloc` call in the standard C library.
This program uses malloc to ask for a pointer to a megabyte of memory, it checks to ensure that malloc was successful and use some oth the memory for a print function 

#### Memory 2 - Asking for All Physical Memory

In this program it tries to access every byte of physical memory on the machine, the memory is managed by the Linux kernel
When the program asks for memory or tries to read/write to allocated memory, the Linux kernel handles the request. Initially the kernel is giving physical memory freely, but once the physical memory is full, it starts using swap memory. 

Each time the program asks for
memory or tries to read or write to memory that it has allocated, the Linux kernel takes charge and
decides how to handle the request. 
Initially, the kernel was simply able to use free physical memory to satisfy the application’s request for
memory, but once physical memory was full, it started using what’s called swap space. The kernel moves data between physical memory and the swap space so that each
time you read or write memory, the data always appears to have been in physical memory.

#### Memory 3 - Available Memory

In this example, the program tries to allocate and access more memory than the machine physically at the time of writing. The system protects itself from this rather aggressive program and kills it. On some systems it will simply exit when malloc fails.

#### Memory 4 - Abusing Your Memory

In this example, the program tries to access a memory adress that has not been allocated. The Linux memory management system has protected the rest of the system from this abuse of memory. To ensure that one program can’t damage any other programs, Linux terminates it.

#### Memory 5 - Accessing a Null Pointer

This program attempts to write to a NULL pointer, then the Linux kernel terminates it. Reading from location zero is not permitted, in the GNU C library reading from a NULL pointer will return null string

#### Memory 6 -  Freeing Memory

Programs that use memory on a dynamic basis should always release unused memory back to the
malloc memory manager using the `free` call .A call to free should be made only with a pointer to memory allocated by a call to malloc, calloc, or
realloc.
