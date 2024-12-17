# Define the minimum CMake version and the Zephyr directory
cmake_minimum_required(VERSION 3.20.0)

# Set the Zephyr directory
find_package(Zephyr REQUIRED HINTS zephyr)

# Define the application
project(my_app)

# Add the application source files
target_sources(app PRIVATE src/main.c)
