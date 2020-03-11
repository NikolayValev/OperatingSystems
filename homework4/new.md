Homework 5
For this assignment we will complete our dealing with Fibonacci numbers by implementing our own “thread safe” queue.

This is a C++ program.
The programming of this assignment is to be done exclusively on POSIX.
You may not use C++ synchronization objects, you must use the POSIX implementations.
You may, however, use C++ x11 threads instead of pthreads if you wish - that’s up to you.
You may implement your queue in any reasonable way (linked list, array, etc) - although you may not use any STL or other library implementations of queues (i.e. no vector, no queue - do it on your own).

As your first task, implement a class called SafeQueue in C++ that serves as a FIFO queue with the following functions:

        class SafeQueue {

        public:

                // return false if the queue contains

                // data, true if empty. Should return immediately.

bool isEmpty()

// Puts the double at the “front” of the queue into “value”

// If the queue is currently empty (see discussion below),

// this function should BLOCK.

void read(double & value)

// Puts “value” at the back of the queue.

// Returns false if anything goes wrong (full queue?)

// Returns true if all goes smoothly.

int write(double value) ;

private: …

};

Your class should be a monitor, so two threads may read and write to the queue w/o race conditions. To do this, you need to include a private mutex variable and acquire the lock (enter the critical section) within the read and write methods/functions. Be careful – race conditions and synchronization errors may not always cause visible inconsistencies – this does not mean that the possibility for error does not exist.

Your read function should block if the queue is empty. This will require you to utilize a semaphore (in addition to the mutex) to keep count of the number of items in your queue. Thus, the read function may efficiently wait (block) until the semaphore is signaled (S>0) before it attempts to enter its critical section and read the first value on the queue. Similarly, your write function will need to increment the Semaphore

Your read method should follow this general structure:

        Wait until Semaphore is > 0

        Decrement Semaphore

        Enter Critical Section

        Read value and remove from queue

        Leave Critical Section

Your write Function should do the following:

        Enter Critical Section

        Add value to back of queue

        Increment Semaphore

        Leave Critical Section

Tip: Check out your textbook - particularly 2.3.5 on “Solving the Producer Consumer Problem”

Main Program
Implement problem #1 from Homework #2, this time with threads instead of processes and your SafeQueue class instead of pipes.

Your main thread should ask the user for an “n” value. It will need to create a SafeQueue and then create the calculation and printing thread. The calculation thread will compute the first “n” Fibonacci numbers, sending each one individually to the printing thread via the SafeQueue. The printing thread will read each number from the queue and write them to fib-n.txt. The following pseudo code outlines the calculation and printing threads:

Calculation Thread:

        for ( each Fibonacci number up to “n” numbers)

                safeQueue->write (fibonnaci number);

Printing Thread:

        Open File

        For ( each Fibonnaci number up to “n” numbers)

                safeQueue->read(num);

                write num to file

        Close file
