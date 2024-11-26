# Producer-Consumer-Problem-Simulation
A multithreaded producer-consumer problem simulation using circular buffers, mutex locks, and condition variables in C.

## Project Description
This project simulates the classic producer-consumer problem using multithreading, mutex locks, and condition variables in C. The implementation ensures safe access to a shared circular buffer of size 100, allowing a producer thread to read integers from a file and a consumer thread to process them, demonstrating synchronization techniques.

## Key Features
- Shared **circular buffer** of size 100 for unsigned integer values.
- **Producer thread** reads integers continuously from `input-part1.txt` and adds them to the buffer.
- **Consumer thread** removes and processes items from the buffer.
- Proper synchronization using **mutex locks** and **condition variables** to handle full and empty buffer states.
- **File-based input** for integers and **file-based output** for consumed items and buffer states.

## Problem Description
The producer-consumer problem involves:

### Producer Behavior
- Reads integers from an input file `input-part1.txt` (one integer per line).
- Terminates upon encountering a `0` in the input file (always present as the last value).
- Waits if the buffer is full before adding new items.

### Consumer Behavior
- Removes integers from the buffer and logs each consumed item to `output-part1.txt`.
- Waits if the buffer is empty before consuming more items.

### Synchronization
- Uses **mutex locks** to ensure exclusive access to the buffer.
- Uses **condition variables** to signal waiting threads when the buffer state changes (full or empty).

## Implementation Details
### Circular Buffer
- A structure with a fixed size of 100.
- Supports **enqueue** and **dequeue** operations.
- Tracks `head`, `tail`, and `size` for buffer state management.

### Multithreading
- Implemented using the **pthread** library in C.
- Two threads:
  - **Producer Thread**: Reads integers from the input file and enqueues them.
  - **Consumer Thread**: Dequeues integers and writes logs to the output file.

### Synchronization
- **Mutex Locks**: Prevent simultaneous access to the shared buffer.
- **Condition Variables**: Signal threads when the buffer transitions between full and empty states.
