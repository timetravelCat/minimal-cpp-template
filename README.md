# minimal-cpp-template

## Features

## Getting Started
* Replace **"project-name"** in CMakeLists.txt project()
* Replace **project-nameConfig.cmake.in** in cmake/
* Replace **project-name** folder name in include/

### Prerequisites
* **CMake v3.15+**
* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*
> ***Note:*** *You also need to be able to provide ***CMake*** a supported
[generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).
* This project uses **[Catch2](!https://github.com/catchorg/Catch2)** as testing framework.

### Installation from sources
> This project follows general CMake steps, configure & generation.
```bash
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION)
cmake --build build --config Release
cmake --build build --target install --config Release
```
> System supports unix Makefile, you can use simplified commands.
```bash
make all # build with all options
# make help 
```

## License
This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

## Contact
timetravelCat - timetraveler930@gmail.com