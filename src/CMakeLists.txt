cmake_minimum_required (VERSION 3.8)

# set( CMAKE_CXX_COMPILER "D:\\MinGW\\bin\\g++.exe" )
# set( CMAKE_C_COMPILER "D:\\MinGW\\bin\\gcc.exe" )

project(wordlist)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

aux_source_directory(include HEAD_LIST)
aux_source_directory(core SRC_LIST)

add_executable(wordlist main.cpp ${HEAD_LIST} ${SRC_LIST})

