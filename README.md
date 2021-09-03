# Geometry Slash

A simple game made in c++ using the raylib graphics library

Goal: Create the longest chain you can, joining tiles of the same colour or shape. 

How to play: Click and hold on the tile you want to start the chain from and drag your mouse to make a chain. Release the mouse to finish the chain.

If you have any suggestions or bug reports, do not hesitate to create an Issue on the GitHub repository

## Planned features:

You can see a To-Do list of upcoming features in [the Projects Tab](https://github.com/Peter0x44/GeometrySlash/projects/1)

## Building (Linux/macOS)

Building the project does not require, but is easier with CMake. It's recommended you install CMake from your preferred package manager.

1. Clone the repository using `git clone https://github.com/Peter0x44/GeometrySlash`
1. cd to the GeometrySlash directory
`cd GeometrySlash`
1. install the raylib git submodule using `git submodule update --init --recursive`
1. make a build folder and cd to it with `mkdir build && cd build`
1. setup cmake `cmake .. -DCMAKE_BUILD_TYPE=Release`
1. run `make` to compile the project
1. make the binary executable `chmod +x GeometrySlash`
1. run the binary with `./GeometrySlash`

**You can also get a build from the [Releases page](https://github.com/Peter0x44/GeometrySlash/Releases), in which case just follow steps 7-8 in the directory GeometrySlash is in after you Download it.**

## Building (Windows, MinGW)

It's possible to not compile GeometrySlash with CMake, but we recommend that you do so because it simplifies a lot of things. You can get it on Windows from [here](https://cmake.org/download/). It's also possible to get it on Scoop, Winget or Chocolatey.

**You need to install MinGW. Select make and developer tools in the installer** [Download MinGW here!](https://sourceforge.net/projects/mingw/)

You should use PowerShell for these commands as it's just a bit better and that's what I'm using.

1. Clone the repository using Git. Execute this in a terminal: `git clone https://github.com/Peter0x44/GeometrySlash`
2. Cd into GeometrySlash. `cd GeometrySlash`
3. Install the Raylib git submodule by running this: `git submodule update --init --recursive`
4. Make a build folder. Your builds will go here. `mkdir build; cd build`
5. Setup CMake. **Make sure to define MinGW Makefiles if you are using MinGW!** `cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"`
6. Make sure you have mingw32-make. If you do, just run it in the build directory and it will start compiling everything. It won't take long, and once it's finished, then
7. Run GeometrySlash.exe! You have just compiled GeometrySlash for Windows using MinGW.

## Building (Windows, MSVC)

We still recommend you to use CMake to compile GeometrySlash, you can get it from [here](https://cmake.org/download/). It's also possible to get it on Scoop, Winget or Chocolatey.

Still, try to use PowerShell because it's much better than Command Prompt.

You need to have Visual Studio 2019 (other versions aren't tested, please tell us if it works for you) with C++ Development selected in the installer.

1. Clone the repository using Git. Execute this in a terminal: `git clone --recursive https://github.com/Peter0x44/GeometrySlash`
2. Cd into GeometrySlash. `cd GeometrySlash`
4. Make a build folder. Your builds will go here. `mkdir build; cd build`
6. Setup CMake. `cmake .. -DCMAKE_BUILD_TYPE=Release`
7. Let's build the project! Run `cmake --build .`
8. Go into Debug, your build of GeometrySlash is there. You have now compiled GeometrySlash for Windows using MSVC.
