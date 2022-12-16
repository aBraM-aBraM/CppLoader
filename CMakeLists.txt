cmake_minimum_required(VERSION 3.16)
project(cpploader)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wl, -v)

add_executable(cpploader main.cpp)

add_custom_command(TARGET cpploader
                   COMMAND ${CMAKE_SOURCE_DIR}/venv/bin/python ${CMAKE_SOURCE_DIR}/encrypt_section.py ./cpploader)