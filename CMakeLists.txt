cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

project(Temineur)

include_directories(./src)

file(GLOB_RECURSE INCLUDE ./src/myLibHeaders/*.hpp)
file(GLOB_RECURSE SRC ./src/myLib/*.cpp)

set(Temineur_Dir ${CMAKE_CURRENT_LIST_DIR})
find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)

add_executable(Temineur ${INCLUDE} ${SRC} main.cpp)

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/img $<TARGET_FILE_DIR:${PROJECT_NAME}>/src/img
            COMMENT "Copying assets directory to output directory"
)

target_link_libraries(Temineur PRIVATE sfml-window sfml-graphics sfml-system)
