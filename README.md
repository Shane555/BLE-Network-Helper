# BLE-Network-Helper 0.1
BLE Mesh Helper APIs for packing and unpacking BLE mesh messages

## Guideline to library usage
1. Download the library 
2. Build from source, use your custom build system(for embedded compiler toolchain) or use Cmake(Version 3.1.6 minimum) for Linux/Windows 
  
    if using Cmake
    1. go to BLE-Network-Helper dir and make a 'build' directory
    2. go to build directory and run `cmake ..` for static library or `cmake .. -DBUILD_SHARED_LIBS=ON` for shared library
    3. run `make` followed by `make install`. (for windows, instead of make, it will be something like `cmake --build . --target INSTALL` as a substitute)
3. To uninstall, remove all directories found in `install_manifest.txt ` created by cmake

Details of helper functions can be found [here](https://github.com/Shane555/BLE-Network-Helper/tree/main/documentation
)
