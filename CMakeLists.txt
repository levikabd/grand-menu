cmake_minimum_required(VERSION 3.10)
project(grand-menu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)
if(CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

add_executable(grand-menu main.cpp)

target_link_libraries(grand-menu 
    ${CURSES_LIBRARIES}
    ncursesw
    tinfo
    menu
)

target_compile_options(grand-menu PRIVATE
    -Wall
    -Wextra
    -D_XOPEN_SOURCE=600
    -D_POSIX_C_SOURCE=200112L
    -D_DEFAULT_SOURCE
    -g # Добавляем отладочную информацию
)

target_compile_definitions(grand-menu PRIVATE
    LC_ALL=ru_RU.UTF-8
    LANG=ru_RU.UTF-8
)
