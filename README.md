# Producer-Consumer-Problem-Simulation
A multithreaded producer-consumer problem simulation using circular buffers, mutex locks, and condition variables in C.

##Project Description

This project simulates the classic producer-consumer problem using multithreading, mutex locks, and condition variables in C. The implementation ensures safe access to a shared circular buffer of size 100, allowing a producer thread to read integers from a file and a consumer thread to process them, demonstrating synchronization techniques.

##Key Features:

Shared circular buffer of size 100 for unsigned integer values.

Producer thread reads integers continuously from input-part1.txt and adds them to the buffer.

Consumer thread removes and processes items from the buffer.

Proper synchronization using mutex locks and condition variables to handle full and empty buffer states.

File-based input for integers and file-based output for consumed items and buffer states.
