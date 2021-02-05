cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME "contank")
project(${PROJECT_NAME} VERSION 0.1.0)

file(GLOB SOURCES "src/*.cpp")


set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${SOURCES})


if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    add_compile_options("-MDd")
endif()



target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
