# z++

This is a compiler written in C++ for the Z++ Programming Language. This programming language is still in development.

## Requirements
* C++23
* CMake
* [llvm](https://github.com/llvm/llvm-project) (Also on various Linux package managers)

## How to Build
* First clone this repository
```cpp
git clone https://github.com/retrooper/zpp
```
* Then create a build folder which will contain all data necessary to run the program.
```cpp
mkdir build
```
* Move to that build in the terminal (asumming you are curently in the workspace folder)
```cpp
cd build
```
* Run the build commands
```cpp
cmake ..
```
```cpp
make
```
* You can now move back to the workspace folder. The executable should now be in the build folder. Run that binary. Here is how you do it on Linux.
```cpp
./build/zpp
```
