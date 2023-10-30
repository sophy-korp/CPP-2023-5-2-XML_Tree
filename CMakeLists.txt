cmake_minimum_required (VERSION 3.8)
project ("XML_Tree_CMake")

set(CMAKE_CXX_STANDARD 17)

add_executable(XML_Tree_CMake main.cpp XMLResource.cpp XMLResource.h XML_Node.cpp XML_Node.h)
