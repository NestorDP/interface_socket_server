cmake_minimum_required(VERSION 2.8.3)
project(interface_socket_server)

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(
  include
  libinterfacesocket
)


add_executable(${PROJECT_NAME} src/main.cpp libinterfacesocket/ethernet_interface.cpp)
