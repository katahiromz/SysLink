# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008"
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles"
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and language
project(SysLink C CXX RC)

# set output directory (build/)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

##############################################################################

# SysLink.dll
add_library(SysLink SHARED syslink.c dllmain.c)
target_compile_definitions(SysLink PRIVATE -DWONVER=0x0500) # 2k
target_include_directories(SysLink PRIVATE wine)
set_target_properties(SysLink PROPERTIES PREFIX "")

##############################################################################

subdirs(tests)

##############################################################################
