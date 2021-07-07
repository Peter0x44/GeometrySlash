# Geometry Slash

A simple game made in c++ using the raylib graphics library

Goal: Create the longest chain you can, joining tiles of the same colour or shape.

If you have any suggestions or bug reports, do not hesitate to create an Issue on the GitHub repository

## Planned features:

- [ ] Background Music
- [ ] Better Contrast of background and tiles
- [ ] Scoring system
- [ ] In-Game How to play instructions
- [ ] Limit minimum size to 800x600

## Building (Linux/macOS)

Building the project does not require, but is easier with CMake. It's recommended you install CMake from your preferred package manager.

1. Clone the repository using `git clone https://github.com/Peter0x44/GeometrySlash`
1. cd to the GeometrySlash directory and create a build folder, then cd into that
` cd GeometrySlash && mkdir build && cd build`
1. setup cmake `cmake .. -DCMAKE_BUILD_TYPE=Release`
1. run `make` to compile the project
1. make the binary executable `chmod +x GeometrySlash`
1. run the binary with `./GeometrySlash`

**You can also get a build from the [Releases page](https://github.com/Peter0x44/GeometrySlash/Releases), in which case just follow steps 5-6 in the directory GeometrySlash is in after you Download it.**
