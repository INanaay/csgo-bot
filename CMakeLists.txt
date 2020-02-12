cmake_minimum_required(VERSION 3.13)
project(csgo_wrapper)

set(CMAKE_CXX_STANDARD 20)

find_package (Threads)


set(BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_PATH ${BASE_PATH}/src)
set(INC_PATH ${BASE_PATH}/inc)
set(EXECUTABLE_OUTPUT_PATH "../dist")

message(STATUS ${BASE_PATH})

file(GLOB_RECURSE HDR_FILES ${BASE_PATH}/inc/*.hpp)
file(GLOB_RECURSE SRC_FILES ${BASE_PATH}/src/*.cpp)

include_directories( ./inc )




add_executable(csgo_wrapper main.cpp ${HDR_FILES} ${SRC_FILES})
target_link_libraries (csgo_wrapper ${CMAKE_THREAD_LIBS_INIT})
