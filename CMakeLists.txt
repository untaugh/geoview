cmake_minimum_required (VERSION 2.6)
project (geoview)

find_package (Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

FILE(GLOB SRCFILES src/*.cc)

add_executable(${PROJECT_NAME} ${SRCFILES})

include_directories("src")
include_directories("/usr/include/eigen3")
include_directories("~/git/geotree/src")
include_directories("~/git/libigl/include")

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} /home/oscu/build/geotreelib/libgeotree.a)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()