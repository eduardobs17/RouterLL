cmake_minimum_required(VERSION 3.8)
project(RouterLegos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Client.cpp Client.h Mensaje.cpp Mensaje.h Server.cpp Server.h Tabla.cpp Tabla.h)
find_package(Threads)
add_executable(RouterLegos ${SOURCE_FILES})
target_link_libraries(RouterLegos ${CMAKE_THREAD_LIBS_INIT})