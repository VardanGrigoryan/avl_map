# avl_map
## Container like dictionary implementation using AVL tree data structure
This is a lightweight library that implements a container-like dictionary via AVL tree data structure. It contains the basic functionality to find, insert and remove elements. 
It also allows to iterate over the container using three types of iterators ```inorder_iterator```, ```preorder_iterator```, ```postorder_iterator``` and this is the main option of this library.
The project also contains randomized stress tests that are intended to check the correctness of algorithms.

## Prerequisites
To be able to test the updates one should be able to build and run the tests using the following tools:

For Linux:
```
1. CMake
2. Gnu Make
2. Valgrind
```

For Windows:
```
1. CMake
2. Visual Studio Community (min version 2015)
3. Dr. Memory
```

## Installing
### CMake install:
For Linux use below given commands:
```
sudo apt-get update

sudo apt-get upgrade

sudo apt-get install cmake3
```

For Windows, it could be downloaded from [official site](https://cmake.org/download/) either x86 or x64 version is suitable in regards to the target platform, also ```3.14.0-rc1``` is pretty stable version.
For installation, it is required to just follow those steps which suggest the package install manager.

### Memory leak detector install:
For Linux just install Valgrind:
```
sudo apt-get install Valgrind
```

For Windows, Dr. Memory could be downloaded from [official site](https://drmemory.org/) and installed just like in the case of CMake.

## Building
For Linux:
1. Go to the project root directory where it is downloaded or cloned
2. run build.sh using argument list which is specific for your platform

Below is given the usage of build.sh script:
```
Usage: ./build.sh -a <arch> -o <os> -t <type> -l <limit>
       
       Example: ./build.sh -a x64 -o unix -t debug -l 100 -c y
       Where:
                 -a - Architecture [64/x86].
                 -o - Operating system [unix/win].
                 -t - Build type [debug/release].
                 -l - Number of iterations [any integer number].
                 -c - Whether to clean the project [y/n].

```

For Windows:
```
1. open Windows command prompt or git bash
2. cd <project root directory>
3. ./build.bat -l <Number of iterations>
```
After build completion, the *.sln file should be opened and compiled via Visual Studio.

## Running the tests
Once the build completes successfully it creates an executable file and puts in into <project root directory>/test/bin area.
The executable name is ```stress_test```. To run this file just call it like:
```
$ <project root directory>/test/bin/stress_test
```
## Contributing
This library is free software; you can redistribute it and/or modify it as it published by the author.

## Authors
* Vardan Grigoryan
