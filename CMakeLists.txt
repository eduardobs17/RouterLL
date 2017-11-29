cmake_minimum_required(VERSION 3.8)
project(_Router_Legos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Client.cpp Client.h Mensaje.cpp Mensaje.h Server.cpp Server.h Tabla.cpp Tabla.h)
find_package(Threads)
add_executable(_Router_Legos ${SOURCE_FILES})
target_link_libraries(_Router_Legos ${CMAKE_THREAD_LIBS_INIT})