CAN-ASCParser
=============
[![Actions Status](https://img.shields.io/github/workflow/status/vinitjames/CAN-ASCParser/Build%20and%20Test?style=plastic)](https://github.com/vinitjames/CAN-ASCParser/actions) &nbsp;
[![MIT License](https://img.shields.io/github/license/vinitjames/CAN-ASCParser?color=blue&style=plastic)](https://github.com/vinitjames/CAN-ASCParser/blob/master/LICENSE)

## About
CAN-ASCParser, is a C++ library for parsing CAN/CANFD .asc log files. 


## Features
* Supports Both CAN/CANFD formats
* Can Handle Remote, Error and Data Frames.
* Header Checking before Parsing 
* Exhaustive Test Suites 

## Installation
Run:
```
git clone https://github.com/vinitjames/CAN-ASCParser.git
```

Change to the new CAN-ASCParser repo directory. Its good practice to  build in a seperate build directory.
```sh
$ cd CAN-ASCParser
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ctest
```
To Install after build run:
```sh
$ sudo cmake --install .
```