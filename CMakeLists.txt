cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS zephyr)

project(my_app)

target_sources(app PRIVATE src/main.c)
