cmake_minimum_required(VERSION 3.21)
project(PureC-OS-IDE VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(purec-os-ide
    src/main.cpp
    src/window/include/MainWindow.h
    src/window/MainWindow.cpp
)

target_link_libraries(purec-os-ide PRIVATE Qt6::Widgets)

target_compile_options(purec-os-ide PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)
