# CPP System Monitor

System Monitor project it's in Linux system is a command line utility that allows the user to interactively monitor the system’s vital resources or server’s processes, Memory and CPU utilization and another features in real time for each change in system.

## Public View and Example From program

![Example](
https://github.com/Mostafa-ashraf19/CPP_System_Monitor/blob/master/images/System%20Monitor%20Example.png
)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine  for development and testing purposes. See deployment for notes on how to deploy the project on a live system.


## Prerequisites

``` 
1. Make & Cmake
2. ncurses is a library that facilitates text-based graphical output in the terminal.
3. git clone: https://github.com/Mostafa-ashraf19/CPP_System_Monitor.git 
 
``` 

## installation and building process on ubuntu:
1. install ncurses ```sudo apt install libncurses5-dev libncursesw5-dev```

2. Build the project: ```make build``` 

3. Run the resulting executable: ```./build/monitor```

![Example](
https://github.com/Mostafa-ashraf19/CPP_System_Monitor/blob/master/images/System%20Monitor%20Example.png
)


## Make instructions

This project uses ``Make`` The Makefile has four targets:
  - ```build``` compiles the source code and generates an executable
  - format applies ```ClangFormat``` to style the source code
  - ```debug``` compiles the source code and generates an executable, including debugging symbols
  - ```clean``` deletes the build/ directory, including all of the build artifacts



