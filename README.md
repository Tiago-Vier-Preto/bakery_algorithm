<h1 align="center">Lamport's Bakery Algorithm</h1>

## Overview

The Lamport's Bakery Algorithm is a synchronization algorithm designed to solve the critical section problem, ensuring mutual exclusion in concurrent systems. It was proposed by computer scientist Leslie Lamport in 1974.

## Building the Library

You must build the library executable before you can run the import.

```makefile
make build 
```

## Running Tests
```makefile
# run test with lamport mutex algorithm
make lamport_test

# run test with POSIX pthreads API
make pthread_mutex_test
```

### Comparing Implementations
```makefile
# compare time executions
make compare
```

## References

- Leslie Lamport. "A New Solution of Dijkstra's Concurrent Programming Problem." *Communications of the ACM*, 1974.
- Tanenbaum, Andrew S., and Maarten Van Steen. *Distributed Systems*. Pearson, 2017.
