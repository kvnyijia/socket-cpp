# CMakeLists.txt

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Set the project name and version
project(MyProject VERSION 1.0)

# Add the executable target
add_executable(server server.cpp)
add_executable(client client.cpp)