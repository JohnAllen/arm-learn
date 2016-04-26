cmake_minimum_required (VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
project (arm-learn)
SET(GCC_FLAGS "-Wl --verbose -v --wackyargument -Wall")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC__FLAGS} -std=c++11" )
SET(LINK_FLAGS "-t ")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
add_executable(arm-learn src/arm_learn.cpp)
target_link_libraries (arm-learn wiringPi wiringPiDev pthread /usr/local/lib/libraspicam.so 
    /usr/local/lib/libwiringPiPca9685.so
    libwiringPiPca9685
    ncurses )
