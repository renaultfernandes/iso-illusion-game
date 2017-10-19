cmake_minimum_required(VERSION 2.8)
project(iso-illusion-game)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set(LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

