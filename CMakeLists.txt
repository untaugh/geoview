cmake_minimum_required (VERSION 2.6)
project (geoview)

set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wpedantic")

FILE(GLOB SRCFILES src/*.c)

add_executable(${PROJECT_NAME} ${SRCFILES})

include_directories("src")
include_directories("/home/oscu/local/include")

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} m)

#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    include_directories(${GLEW_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
#endif()
