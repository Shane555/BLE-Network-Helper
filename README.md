# BLE-Network-Helper 0.1
BLE Mesh Helper APIs for packing and unpacking BLE mesh messages

## Guideline to library usage
1. Download the library 
2. Build from source, use your custom build system or Cmake(Version 3.1.6 minimum) 
  
    if using Cmake
    1. go to nework_msg_struct dir and make a 'build' directory
    2. go to build directory and run `cmake ..` for static library or `cmake .. -DBUILD_SHARED_LIBS=ON` for shared library
    3. run `make` followed by `make install`. (for windows, instead of make, it will be something like `cmake --build . --target INSTALL` as a substitute)
3. To uninstall, remove all directories found in `install_manifest.txt ` created by cmake

Details of helper functions can be found in my_crc.h and network_msg_struct.h
