### Lab 5.2 - Designing a virtual memory manager

#### Instructions

This project consists of writing a program that translates logical to physical
addresses for a virtual address space of size 216 = 65,536 bytes. Your program
will read from a file containing logical addresses and, using a TLB as well as
a page table, will translate each logical address to its corresponding physical
address and output the value of the byte stored at the translated physical
address. The goal behind this project is to simulate the steps involved in
translating logical to physical addresses.

### Specifics

Your program will read a file containing several 32-bit integer numbers that
represent logical addresses. However, you need only be concerned with 16-bit
addresses, so you must mask the rightmost 16 bits of each logical address.
These 16 bits are divided into (1) an 8-bit page number and (2) 8-bit page offset.
Hence, the addresses are structured as shown in Figure 9.33.
Other specifics include the following:

* 28 entries in the page table

* Page size of 28 bytes

* 16 entries in the TLB

* Frame size of 28 bytes

* 256 frames

* Physical memory of 65,536 bytes (256 frames × 256-byte frame size)

### Handling Page Faults

The backing store is represented by the file `BACKING STORE.bin`, a binary file of size
65,536 bytes.When a page fault occurs, you will read in a 256-byte page from the
file BACKING STORE and store it in an available page frame in physical memory.
For example, if a logical address with page number 15 resulted in a page fault,
your program would read in page 15 from BACKING STORE (remember that
pages begin at 0 and are 256 bytes in size) and store it in a page frame in
physical memory. Once this frame is stored (and the page table and TLB are
updated), subsequent accesses to page 15 will be resolved by either the TLB or
the page table.


### Test File
We provide the file `addresses.txt`, which contains integer values representing logical addresses ranging from 0 − 65535 (the size of the virtual address space). Your program will open this file, read each logical address and translate
it to its corresponding physical address, and output the value of the signed byte
at the physical address

#### Run 

`python memory_manager.py`
