cmake_minimum_required(VERSION 2.8)

project(Assignment_1)
add_executable(Assignment1.out Assignment1.cpp)
add_executable(CreateModel.out CreateModel.cpp)



find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( Assignment1.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( CreateModel.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

