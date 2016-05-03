cmake_minimum_required (VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
project (arm-learn)
SET(GCC_FLAGS "-Wl --verbose -v --wackyargument -Wall")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC__FLAGS} -std=c++11" )
SET(LINK_FLAGS "-t ")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
find_package(Boost COMPONENTS system filesystem REQUIRED)
add_executable(command_arm src/learn.cpp src/command_arm.cpp src/servo.cpp src/utils.cpp)
target_link_libraries (command_arm wiringPi wiringPiDev pthread /usr/local/lib/libraspicam.so 
    /usr/local/lib/libwiringPi.so
    /usr/local/lib/libwiringPiPca9685.so
    ncurses
    ${Boost_LIBRARIES}
)
add_executable(train_arm src/learn.cpp src/command_arm.cpp src/servo.cpp src/utils.cpp)
target_link_libraries (train_arm wiringPi wiringPiDev pthread /usr/local/lib/libraspicam.so
    /usr/local/lib/libwiringPi.so
    /usr/local/lib/libwiringPiPca9685.so
    ncurses
    ${Boost_LIBRARIES}
)
add_executable(target src/target.cpp src/servo.cpp src/utils.cpp)
target_link_libraries (target wiringPi wiringPiDev pthread /usr/local/lib/libraspicam.so
    /usr/local/lib/libwiringPi.so
    /usr/local/lib/libwiringPiPca9685.so
    ncurses
    ${Boost_LIBRARIES}
)
add_executable(test src/test.cpp src/servo.cpp src/utils.cpp)
target_link_libraries (test wiringPi wiringPiDev pthread /usr/local/lib/libraspicam.so
    /usr/local/lib/libwiringPi.so
    /usr/local/lib/libwiringPiPca9685.so
    ncurses
    ${Boost_LIBRARIES}
)

