cmake_minimum_required (VERSION 2.6)
project (geoview)

set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wpedantic")

FILE(GLOB SRCFILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRCFILES})

include_directories("src")

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_library(GEOTREE_LIB geotree)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} ${GEOTREE_LIB})
