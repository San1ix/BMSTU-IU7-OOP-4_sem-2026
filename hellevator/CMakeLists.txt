cmake_minimum_required(VERSION 3.16)
project(hellevator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/Qt6" ${CMAKE_PREFIX_PATH})
set(Qt6_DIR "/usr/lib64/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    elevator.cpp
    controller.cpp
    cabin.cpp
    doors.cpp
    manager.cpp
)

set(HEADERS
    mainwindow.h
    elevator.h
    controller.h
    cabin.h
    doors.h
    manager.h
    defines.h
    config.h
)

set(UI_FILES
    mainwindow.ui
)

add_executable(hellevator ${SOURCES} ${HEADERS} ${UI_FILES})

target_link_libraries(hellevator 
    Qt6::Core
    Qt6::Widgets
)

target_include_directories(hellevator PRIVATE
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
)

set_target_properties(hellevator PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)