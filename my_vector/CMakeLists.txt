cmake_minimum_required(VERSION 3.16)
project(vector_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    base_vector.cpp
    base_exceptions.cpp
    vector_exceptions.cpp
    iterator_exceptions.cpp
)

add_executable(vector_lab ${SOURCES})

target_compile_options(vector_lab PRIVATE -Wall -Wextra)

# Добавляем текущую директорию в include path
target_include_directories(vector_lab PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})