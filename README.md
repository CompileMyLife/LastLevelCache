# LastLevelCache
A last level cache (LLC) simulator for a new processor that can be used with up
to three other processors in a shared memory configuration.

## Features and Details 
This cache has a total capacity of 16MB, uses 64 byte lines, and is 8 way set
associative. It employs a write allocate policy and uses the MESI protocol to
ensure cache coherence. The replacement policy is implemented with a psuedo LRU
algorithm.


## System and Software Requirements
The source code was built and tested on `Ubuntu 20.04.6 LTS` with the following tools:
* gcc 9.4.0
* GNU Make 4.2.1
* glibc 2.31

## Build and Test
```console
$ make
$ ./llc -f <path/to/file>
```
**NOTE**: Can apply `-s` flag for Silent mode. `llc` program runs by default in
Normal mode

## More Information
Visit the [Wiki](https://github.com/CompileMyLife/LastLevelCache/wiki) to understand more on the LLC!
