# PagingSimulation
###### A C++ program that simulates a paging system using the aging algorithm. The program reads a sequence of reference requests from a file and loads and evicts pages as necessary. 
##### Page Table Entry 
###### Each page table entry is a uint32_t and has the following format: the most significant bit , R, is the referenced bit. The next bit, M, is the modified bit. after that is P is the present/absent bit. The appropriate number of least significant bits is used to store the frame number ( determined by the number of page frames ). 
##### Counter 
###### Represented by an 8 - bit integer, and is aged every two clock cycles. 
##### Process 
###### Consists of the number of pages , frames , and a set of counters. 
##### Input 
###### The first line of the input file contains three integers: the number of virtual pages, the number of physical page frames, and the size of a page. The second line is the number of processes that will be running for the simulation. The remaining lines contain a virtual memory reference that we will simulate. The first number is the number of the process requesting the reference. The second field, either “r” or “w”, indicates if the reference is a read or a write. The last number is the virtual memory location being requested.
